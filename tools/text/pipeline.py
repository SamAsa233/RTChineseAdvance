"""Convert the supplied keyed JSON translations to TSV and import safe entries.

Examples:
  python tools/text/pipeline.py extract
  python tools/text/pipeline.py check
  python tools/text/pipeline.py import
"""

import argparse
from collections import defaultdict
import csv
import json
import os
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
ARCHIVE = ROOT / "text/zh_hans/source/utf8"
TABLE = ROOT / "text/zh_hans/translations.tsv"
REPORT = ROOT / "build/text_report"
LITERAL = re.compile(r'"(?:\\.|[^"\\])*"', re.S)
CONTROL = re.compile(r'\\(?:[0-7]{1,3}|x[0-9a-fA-F]+)|[.:][0-9a-fA-F]')
FIELDS = ("id", "file", "key", "source", "target", "status", "note")


def atomic_text(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + ".tmp")
    temp.write_text(data, encoding="utf-8", newline="")
    os.replace(temp, path)


def remove_comments(text):
    def blank(match):
        return re.sub(r'[^\r\n]', ' ', match.group())
    return re.sub(r'/\*.*?\*/|//[^\r\n]*', blank, text, flags=re.S)


def mask_literals(text):
    return LITERAL.sub(lambda match: ' ' * len(match.group()), text)


def literal_group(text, start, end):
    matches = list(LITERAL.finditer(remove_comments(text[start:end])))
    if not matches:
        return None
    if re.search(r'(?m)^\s*#\s*(?:if|ifdef|ifndef|else|elif|endif)\b', text[start + matches[0].start():start + matches[-1].end()]):
        return None
    return (start + matches[0].start(), start + matches[-1].end(), ''.join(match.group()[1:-1] for match in matches))


def c_initializer(text, base):
    clean = remove_comments(text)
    match = re.search(r'\b' + re.escape(base) + r'\s*(?:\[[^\]]*\])?\s*=\s*', clean)
    if not match:
        return None
    start = match.end()
    if clean[start] != '{':
        end = clean.find(';', start)
        group = literal_group(text, start, end)
        return [group] if group else None
    structural = mask_literals(clean)
    depth = 1
    section = start + 1
    groups = []
    for pos in range(section, len(structural)):
        char = structural[pos]
        if char == '{':
            depth += 1
        elif char == '}':
            depth -= 1
            if depth == 0:
                group = literal_group(text, section, pos)
                if group:
                    groups.append(group)
                return groups
        elif char == ',' and depth == 1:
            group = literal_group(text, section, pos)
            if group:
                groups.append(group)
            section = pos + 1
    return None


def bs_initializer(text, base):
    match = re.search(r'(?m)^text\s+' + re.escape(base) + r'\s*$', text)
    if not match:
        return None
    end = re.search(r'(?m)^endtext\s*$', text[match.end():])
    if not end:
        return None
    section_end = match.end() + end.start()
    section = text[match.end():section_end]
    literals = list(LITERAL.finditer(section))
    if not literals:
        return None
    raw = ''.join(m.group()[1:-1] for m in literals)
    first_line = section.rfind('\n', 0, literals[0].start()) + 1
    return [(match.end() + first_line, match.end() + literals[-1].end(), raw)]


def level_slot(text, key):
    source = ARCHIVE / 'data/game_select'
    groups = []
    for name in ('levels.inc.json', 'levels.inc_add.json'):
        for row in json.loads((source / name).read_text(encoding='utf-8')):
            current = row['key']
            if current.endswith('_desc') or re.search(r'_result_[123]$', current):
                if groups:
                    groups[-1].append(current)
            else:
                groups.append([current])
    positions = {item: (i, j) for i, group in enumerate(groups) for j, item in enumerate(group)}
    if key not in positions:
        return None
    entry, field = positions[key]
    markers = list(re.finditer(r'/\* ([A-Z][A-Z0-9_]+) \*/ \{', text))
    if entry >= len(markers):
        return None
    start = markers[entry].end()
    end = markers[entry + 1].start() if entry + 1 < len(markers) else len(text)
    section = text[start:end]
    names = ('Level Name', 'Level Desc.', 'TRY_AGAIN', 'OK', 'SUPERB')
    if field >= len(names):
        return None
    current = re.search(r'/\*\s*' + re.escape(names[field]) + r'\s*\*/', section)
    if not current:
        return None
    following = [m.start() for name in names[field + 1:] if (m := re.search(r'/\*\s*' + re.escape(name) + r'\s*\*/', section))]
    if field == 1:
        icon = re.search(r'/\*\s*Level Icon\s*\*/', section)
        if icon:
            following.append(icon.start())
    if field == 4:
        close = section.find('}', current.end())
        if close != -1:
            following.append(close)
    field_end = min(following) if following else len(section)
    if re.search(r'(?m)^\s*#\s*(?:if|ifdef|ifndef|else|elif|endif)\b', section[current.end():field_end]):
        return None
    group = literal_group(section, current.end(), field_end)
    if not group:
        return None
    if field != 1 and len(LITERAL.findall(remove_comments(section[current.end():field_end]))) != 1:
        return None  # Avoid replacing both sides of conditional compilation.
    return [(start + group[0], start + group[1], group[2])]


def ordinal_slot(text, path, key):
    specs = {
        'src/scenes/debug_menu_table.c': ('src/debug_menu_table.json', r'/\*\s*Label\s*\*/', None),
        'data/scenes/medal_corner/lessons_menu.inc.c': ('data/medal_corner/lessons_menu.inc.json', r'/\*\s*Title\s*\*/', None),
        'data/scenes/studio/songs.inc.c': ('data/studio/songs.inc.json', r'/\*\s*(?:Full|Short) Title\s*\*/', None),
        'data/scenes/data_room/reading_material.inc.c': ('data/data_room/reading_material.inc.json', r'/\*\s*(?:TITLE|BODY)\s*-+\s*\*/', r'/\*\s*STYLE\s*-+\s*\*/'),
    }
    name = path.relative_to(ROOT).as_posix()
    if name not in specs:
        return None
    source, pattern, end_pattern = specs[name]
    rows = json.loads((ARCHIVE / source).read_text(encoding='utf-8'))
    keys = [row['key'] for row in rows]
    if key not in keys:
        return None
    markers = list(re.finditer(pattern, text))
    groups = []
    for i, marker in enumerate(markers):
        end = markers[i + 1].start() if i + 1 < len(markers) else len(text)
        if end_pattern:
            style = re.search(end_pattern, text[marker.end():end])
            if style:
                end = marker.end() + style.start()
        if name.endswith('songs.inc.c') or name.endswith('lessons_menu.inc.c') or name.endswith('debug_menu_table.c'):
            comma = mask_literals(remove_comments(text[marker.end():end])).find(',')
            if comma >= 0:
                end = marker.end() + comma
        group = literal_group(text, marker.end(), end)
        if group:
            groups.append(group)
    if len(groups) != len(keys):
        return None
    return [groups[keys.index(key)]]


def locate(text, path, key):
    if path.as_posix().endswith('data/scenes/game_select/levels.inc.c') and key.startswith('level_'):
        return level_slot(text, key)
    ordinal = ordinal_slot(text, path, key)
    if ordinal:
        return ordinal
    base = key.split('[', 1)[0]
    return bs_initializer(text, base) if path.suffix == '.bs' else c_initializer(text, base)


def source_path(json_path):
    relative = json_path.relative_to(ARCHIVE)
    parts = relative.parts
    if parts[0] == 'games':
        stem = relative.with_suffix('')
        if stem.name.endswith('_add'):
            stem = stem.with_name(stem.name[:-4])
        candidates = [ROOT / (str(stem) + '.c'), ROOT / (str(stem) + '.bs')]
        if stem.name.endswith('_lyrics'):
            candidates.append(ROOT / (str(stem.with_name(stem.name[:-7])) + '.bs'))
        if stem.name.endswith('_unused_lyrics'):
            candidates.append(ROOT / (str(stem.with_name(stem.name[:-7])) + '.bs'))
        candidates.extend([ROOT / 'games' / parts[1] / (parts[1] + '.bs'), ROOT / 'src/engines' / (parts[1] + '.c')])
    elif parts[0] == 'data':
        stem = Path('data/scenes').joinpath(*parts[1:]).with_suffix('')
        if stem.name.endswith('_add'):
            stem = stem.with_name(stem.name[:-4])
        candidates = [ROOT / (str(stem) + '.c')]
    else:
        stem = relative.with_suffix('')
        if stem.name.endswith('_add'):
            stem = stem.with_name(stem.name[:-4])
        candidates = [ROOT / 'src/scenes' / (stem.name + '.c'), ROOT / 'src/engines' / (stem.name + '.c')]
    return next((path for path in candidates if path.exists()), None)


def grouped_archive():
    grouped = defaultdict(list)
    for json_path in sorted(ARCHIVE.rglob('*.json')):
        destination = source_path(json_path)
        for row in json.loads(json_path.read_text(encoding='utf-8')):
            key = row['key'].removeprefix('text ')
            prefix = json_path.stem + '_'
            if key.startswith(prefix) and re.match(r'D_[0-9a-fA-F]+$', key[len(prefix):]):
                key = key[len(prefix):]
            base = key.split('[', 1)[0]
            grouped[(json_path, destination, base)].append((key, row))
    return grouped


def extract():
    output, unresolved = [], []
    previous = {}
    if TABLE.exists():
        with TABLE.open(encoding='utf-8', newline='') as stream:
            previous = {row['id']: row for row in csv.DictReader(stream, delimiter='\t')}
    for (json_path, path, base), members in grouped_archive().items():
        if path is None:
            unresolved.extend(f"{json_path.relative_to(ARCHIVE)}:{key}: no source file" for key, _ in members)
            continue
        text = path.read_text(encoding='utf-8')
        groups = locate(text, path, members[0][0])
        if not groups:
            unresolved.extend(f"{json_path.relative_to(ARCHIVE)}:{key}: key not found" for key, _ in members)
            continue
        indexed = [re.search(r'\[(\d+)\]$', key) for key, _ in members]
        if len(groups) == len(members):
            assigned = list(range(len(members)))
        elif all(indexed) and max(int(m.group(1)) for m in indexed) < len(groups):
            assigned = [int(m.group(1)) for m in indexed]
        else:
            unresolved.extend(f"{json_path.relative_to(ARCHIVE)}:{key}: {len(groups)} source entries vs {len(members)} translations" for key, _ in members)
            continue
        for (key, row), index in zip(members, assigned):
            source = groups[index][2]
            target = row['translation']
            controls = CONTROL.findall(source)
            bitmap = any(token.startswith('.') or token.startswith(':') for token in controls)
            note = ''
            if controls:
                prefix = re.match(r'^(?:(?:[.:][0-9a-fA-F])+)', source)
                suffix = re.search(r'(?:(?:[.:][0-9a-fA-F])+)$', source)
                covered = (prefix.group() if prefix else '') + (suffix.group() if suffix else '')
                if bitmap and covered and sorted(CONTROL.findall(covered)) == sorted(controls):
                    target = (prefix.group() if prefix else '') + target + (suffix.group() if suffix else '')
                elif source != target:
                    note = 'control codes need review'
            relative = path.relative_to(ROOT).as_posix()
            record = dict(id=f"{relative}:{key}", file=relative, key=key, source=source, target=target, status='final' if row['stage'] == 5 else 'draft', note=note)
            output.append(previous.get(record['id'], record))
    # Supplemental *_add.json entries override the same key from the base file.
    output = list({row['id']: row for row in output}.values())
    output.sort(key=lambda row: row['id'])
    from io import StringIO
    stream = StringIO(newline='')
    writer = csv.DictWriter(stream, fieldnames=FIELDS, delimiter='\t', lineterminator='\n')
    writer.writeheader()
    writer.writerows(output)
    atomic_text(TABLE, stream.getvalue())
    REPORT.mkdir(parents=True, exist_ok=True)
    atomic_text(REPORT / 'unresolved.txt', '\n'.join(unresolved) + '\n')
    chars = sorted({ch for row in output for ch in row['target'] if 0x4E00 <= ord(ch) <= 0x9FFF})
    atomic_text(REPORT / 'charset.txt', ''.join(chars) + '\n')
    bitmap_rows = [row for row in output if row['file'].endswith('.bs') or 'results/data.inc.c' in row['file']]
    atomic_text(REPORT / 'bitmap_font_strings.txt', '\n'.join(row['id'] + '\t' + row['target'] for row in bitmap_rows) + '\n')
    print(f"mapped={len(output)}, unresolved={len(unresolved)}, final={sum(row['status']=='final' for row in output)}")


def import_text(check, only_final):
    with TABLE.open(encoding='utf-8', newline='') as stream:
        rows = list(csv.DictReader(stream, delimiter='\t'))
    all_members = defaultdict(list)
    for row in rows:
        all_members[(row['file'], row['key'].split('[', 1)[0])].append(row)
    files = defaultdict(list)
    for row in rows:
        if only_final and row['status'] != 'final':
            continue
        files[row['file']].append(row)
    changed, problems, skipped = 0, [], 0
    for filename, members in files.items():
        path = ROOT / filename
        text = path.read_text(encoding='utf-8')
        edits = []
        for row in members:
            if row['note']:
                skipped += 1
                continue
            key = row['key']
            base = key.split('[', 1)[0]
            groups = locate(text, path, key)
            siblings = all_members[(filename, base)]
            siblings.sort(key=lambda item: int(re.search(r'\[(\d+)\]$', item['key']).group(1)) if re.search(r'\[(\d+)\]$', item['key']) else -1)
            if not groups:
                problems.append(row['id'] + ': initializer not found')
                continue
            indexed = [re.search(r'\[(\d+)\]$', item['key']) for item in siblings]
            if len(groups) == len(siblings):
                index = siblings.index(row)
            elif all(indexed) and max(int(m.group(1)) for m in indexed) < len(groups):
                index = int(re.search(r'\[(\d+)\]$', key).group(1))
            else:
                problems.append(row['id'] + ': array changed')
                continue
            start, end, current = groups[index]
            quoted = json.dumps(row['target'], ensure_ascii=False)
            target = ('    .asciz ' + quoted) if path.suffix == '.bs' else quoted
            if text[start:end] == target:
                continue
            if current != row['source'] and current != quoted[1:-1]:
                problems.append(row['id'] + ': source changed')
                continue
            edits.append((start, end, target))
        if edits and not check:
            for start, end, replacement in sorted(edits, reverse=True):
                text = text[:start] + replacement + text[end:]
            atomic_text(path, text)
        changed += len(edits)
    atomic_text(REPORT / 'import_problems.txt', '\n'.join(problems) + '\n')
    print(f"{'would import' if check else 'imported'}={changed}, control-review={skipped}, problems={len(problems)}")
    return bool(problems)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('action', choices=('extract', 'check', 'import'))
    parser.add_argument('--include-draft', action='store_true')
    args = parser.parse_args()
    if args.action == 'extract':
        extract()
    else:
        raise SystemExit(import_text(args.action == 'check', not args.include_draft))


if __name__ == '__main__':
    main()
