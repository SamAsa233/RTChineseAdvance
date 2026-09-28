"""Convert the supplied keyed JSON translations to TSV and import safe entries.

Examples:
  python tools/text/pipeline.py extract
  python tools/text/pipeline.py check
  python tools/text/pipeline.py import
"""

import argparse
from collections import defaultdict
import csv
import difflib
from functools import lru_cache
import json
import os
from pathlib import Path
import re
import subprocess
import unicodedata

ROOT = Path(__file__).resolve().parents[2]
ARCHIVE = ROOT / "text/zh_hans/source/utf8"
TABLE = ROOT / "text/zh_hans/translations.tsv"
REPORT = ROOT / "build/text_report"
LITERAL = re.compile(r'"(?:\\.|[^"\\])*"', re.S)
CONTROL = re.compile(r'\\(?:[0-7]{1,3}|x[0-9a-fA-F]+)|[.:][0-9a-fA-F]')
CONTROL_TOKEN = re.compile(r'\\(?:004|4)[0-9]+\.|\\(?:00[1235]|[1235])[0-9A-Za-z\[\]]|[.:][0-9a-fA-F]')
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
            # Keep a placeholder for the conditional rhythm-sense line;
            # otherwise following array indices slide onto the wrong text.
            if group or base == 'cafe_dialogue_rhythm_sense':
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


@lru_cache(maxsize=1)
def debug_menu_mapping():
    path = 'src/scenes/debug_menu_table.c'
    result = subprocess.run(['git', 'show', 'text_utf8:' + path], cwd=ROOT,
                            capture_output=True, text=True, encoding='utf-8', check=True)
    original = result.stdout
    archive_rows = json.loads((ARCHIVE / 'src/debug_menu_table.json').read_text(encoding='utf-8'))
    source_names = [unicodedata.normalize('NFKC', row['original']) for row in archive_rows]
    target_names = [unicodedata.normalize('NFKC', match.group(1)[1:-1]) for match in re.finditer(r'/\*\s*Label\s*\*/\s*("(?:\\.|[^"\\])*")', original)]
    mapping = {}
    source_start = target_start = 0
    for match in difflib.SequenceMatcher(None, source_names, target_names, autojunk=False).get_matching_blocks():
        if match.a - source_start == match.b - target_start:
            for offset in range(match.a - source_start):
                mapping[source_start + offset] = target_start + offset
        for offset in range(match.size):
            mapping[match.a + offset] = match.b + offset
        source_start, target_start = match.a + match.size, match.b + match.size
    return mapping


def ordinal_slot(text, path, key):
    name = path.relative_to(ROOT).as_posix()
    if name == 'src/scenes/studio_drums.c':
        rows = json.loads((ARCHIVE / 'src/studio_drums.json').read_text(encoding='utf-8'))
        keys = [row['key'] for row in rows]
        if key in keys:
            groups = (c_initializer(text, 'studio_drum_kit_names') or []) + (c_initializer(text, 'studio_mem_warnings_text') or [])
            return [groups[keys.index(key)]] if len(groups) == len(keys) else None
    if name == 'src/scenes/studio_options.c':
        rows = json.loads((ARCHIVE / 'src/studio_options.json').read_text(encoding='utf-8'))
        keys = [row['key'] for row in rows]
        if key in keys[:8]:
            groups = (c_initializer(text, 'studio_options_no_replay') or []) + (c_initializer(text, 'studio_options_is_replay') or [])
            return [groups[keys.index(key)]] if len(groups) == 8 else None
        if key in keys[8:]:
            groups = []
            for marker in re.finditer(re.escape('studio_warning_create('), text):
                following = text.find('studio_option_list_warning_', marker.end())
                end = text.rfind(',', marker.end(), following)
                if end > marker.end():
                    group = literal_group(text, marker.end(), end)
                    if group:
                        groups.append(group)
            return [groups[keys.index(key) - 8]] if len(groups) == 3 else None
    specs = {
        'src/scenes/debug_menu_table.c': ('src/debug_menu_table.json', r'/\*\s*Label\s*\*/', None),
        'data/scenes/medal_corner/lessons_menu.inc.c': ('data/medal_corner/lessons_menu.inc.json', r'/\*\s*Title\s*\*/', None),
        'data/scenes/studio/songs.inc.c': ('data/studio/songs.inc.json', r'/\*\s*(?:Full|Short) Title\s*\*/', None),
        'data/scenes/data_room/reading_material.inc.c': ('data/data_room/reading_material.inc.json', r'/\*\s*(?:TITLE|BODY)\s*-+\s*\*/', r'/\*\s*STYLE\s*-+\s*\*/'),
    }
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
        if name.endswith('reading_material.inc.c'):
            groups.append(group)  # Preserve marker positions when a #if body is unsafe.
        elif group:
            groups.append(group)
    if name.endswith('reading_material.inc.c'):
        selected = keys.index(key)
        # The archive's first 39 entries match TITLE/BODY markers in order.
        # Its five haiku entries share one BODY; the two final credit markers
        # have no supplied translation. Handle the haiku explicitly later.
        return [groups[selected]] if selected < 39 and selected < len(groups) and groups[selected] else None
    if name.endswith('songs.inc.c') and len(groups) == len(keys) + 1:
        selected = keys.index(key)
        # Two region-specific Cafe Counselling literals occupy one song entry.
        # Defer that entry until both conditional branches can be updated.
        if key == 'song_cafe_counsel':
            return None
        selected += selected > keys.index('song_cafe_counsel')
        return [groups[selected]] if selected < len(groups) else None
    if len(groups) == len(keys):
        return [groups[keys.index(key)]]
    if name.endswith('debug_menu_table.c'):
        selected = debug_menu_mapping().get(keys.index(key))
        return [groups[selected]] if selected is not None and selected < len(groups) else None
    return None


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
        if stem.name.endswith('_more_text'):
            # Some reviewed dialogue JSON files split their source under the
            # shared parent .bs script (for example tanuki_and_monkey.bs).
            stem = stem.with_name(stem.name[:-10])
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
        # These reviewed fragments are composed at runtime in perfect_scene_start;
        # they intentionally have no standalone source literal to replace.
        if json_path.relative_to(ARCHIVE).as_posix() == 'src/perfect.json':
            continue
        # Cafe Counselling has two spelling branches in the source; both are
        # updated manually to one reviewed Chinese title.
        if (json_path.relative_to(ARCHIVE).as_posix() == 'data/studio/songs.inc.json'
                and base == 'song_cafe_counsel'):
            unresolved = [item for item in unresolved
                          if not item.startswith(f'{json_path.relative_to(ARCHIVE)}:{base}:')]
            continue
        # The karate opening line has two source spelling branches but one
        # reviewed Chinese sentence; both branches are updated manually.
        if (json_path.relative_to(ARCHIVE).as_posix() == 'games/karate_man/karate_man_text.json'
                and base == 'D_0805ad80'):
            unresolved = [item for item in unresolved
                          if not item.startswith(f'{json_path.relative_to(ARCHIVE)}:{base}:')]
            continue
        # The opening drum demo title is one shared string with a regional
        # name branch in the source; the reviewed Chinese text is manual.
        if (json_path.relative_to(ARCHIVE).as_posix() == 'games/drum_intro/drum_samurai_cutscene_text.json'
                and base == 'D_0805df4c'):
            unresolved = [item for item in unresolved
                          if not item.startswith(f'{json_path.relative_to(ARCHIVE)}:{base}:')]
            continue
        if base == 'perfect_gift_directive_text' and len(members) == 1:
            # The source JSON contains three reward-type messages in one row,
            # while the English port stores them in three array entries.
            original = members[0][1]
            parts = original['translation'].splitlines(keepends=True)
            if len(parts) == 3:
                members = [(f'perfect_gift_directive_text[{index}]',
                            {**original, 'translation': part}) for index, part in enumerate(parts)]
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
            if groups[index] is None:
                unresolved.append(f"{json_path.relative_to(ARCHIVE)}:{key}: conditional branches need review")
                old = previous.get(f"{path.relative_to(ROOT).as_posix()}:{key}")
                if old:
                    output.append(old)
                continue
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
            reviewed = row['stage'] == 5
            # Only stage 5 in the supplied package is proof of review. Keep
            # unfinished translations searchable without importing them.
            if not reviewed:
                note = '; '.join(filter(None, ('TODO 未校对', note)))
            record = dict(id=f"{relative}:{key}", file=relative, key=key, source=source, target=target, status='final' if reviewed else 'draft', note=note)
            saved = previous.get(record['id'], record)
            if not reviewed:
                saved['status'] = 'draft'
                # Normalize repeated rerun markers so Ctrl+F shows one clear TODO.
                old_notes = [part.strip() for part in saved['note'].split(';')
                             if part.strip() and part.strip() != 'TODO 未校对']
                saved['note'] = '; '.join(['TODO 未校对'] + old_notes)
            output.append(record if base == 'perfect_gift_directive_text' else saved)
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
    # Track every unfinished key in version control so Ctrl+F finds it even
    # when conditional C code has no safe location for an inline comment.
    todo = ['# TODO 未校对', '',
            '阶段 5 以外的译文尚未导入源码；未定位及控制码待复核的条目也在此列出。',
            '', '## 已定位但未校对']
    todo.extend(f"- TODO 未校对 {row['id']}" for row in output if row['status'] != 'final')
    # Stage 5 proves wording was reviewed, not that printer control bytes or
    # alternate compile-time branches can be moved safely. Keep these searchable
    # until their source layout is checked in game and the import note is cleared.
    todo.extend(['', '## 已校对译文仍待控制码或分支复核', ''])
    todo.extend(f"- TODO 未校对 {row['id']}: {row['note']}"
                for row in output if row['status'] == 'final' and row['note'])
    todo.extend(['', '## 尚未安全定位', ''])
    todo.extend(f'- TODO 未校对 {entry}' for entry in unresolved)
    atomic_text(ROOT / 'text/zh_hans/TODO_未校对.md', '\n'.join(todo) + '\n')
    # Include unresolved translations so the font is ready when their mappings land.
    chars = sorted({ch for path in ARCHIVE.rglob('*.json')
                    for row in json.loads(path.read_text(encoding='utf-8'))
                    for ch in row['translation'] if 0x4E00 <= ord(ch) <= 0x9FFF})
    atomic_text(REPORT / 'charset.txt', ''.join(chars) + '\n')
    bitmap_rows = [row for row in output if row['file'].endswith('.bs') or 'results/data.inc.c' in row['file']]
    atomic_text(REPORT / 'bitmap_font_strings.txt', '\n'.join(row['id'] + '\t' + row['target'] for row in bitmap_rows) + '\n')
    print(f"mapped={len(output)}, unresolved={len(unresolved)}, final={sum(row['status']=='final' for row in output)}")


def preserve_edge_controls(source, target):
    """Keep complete printer/bitmap control tokens enclosing translated text."""
    tokens = list(CONTROL_TOKEN.finditer(source))
    raw = list(CONTROL.finditer(source))
    if not tokens or len(tokens) != len(raw) or any(a.start() != b.start() for a, b in zip(tokens, raw)):
        return None
    if CONTROL.search(target):
        return None
    prefix_end = 0
    while match := CONTROL_TOKEN.match(source, prefix_end):
        prefix_end = match.end()
    suffix_start = len(source)
    for token in reversed(tokens):
        if token.end() == suffix_start:
            suffix_start = token.start()
        else:
            break
    if prefix_end >= suffix_start or any(prefix_end < token.start() < suffix_start for token in tokens):
        return None
    return source[:prefix_end] + target + source[suffix_start:]


def resolve_edge_controls():
    with TABLE.open(encoding='utf-8', newline='') as stream:
        rows = list(csv.DictReader(stream, delimiter='\t'))
    count = 0
    for row in rows:
        if row['note'] != 'control codes need review':
            continue
        target = preserve_edge_controls(row['source'], row['target'])
        if target is not None:
            row['target'], row['note'] = target, ''
            count += 1
    from io import StringIO
    stream = StringIO(newline='')
    writer = csv.DictWriter(stream, fieldnames=FIELDS, delimiter='\t', lineterminator='\n')
    writer.writeheader()
    writer.writerows(rows)
    atomic_text(TABLE, stream.getvalue())
    print(f'edge controls preserved={count}')


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
            if groups[index] is None:
                problems.append(row['id'] + ': conditional branches need review')
                continue
            start, end, current = groups[index]
            quoted = json.dumps(row['target'], ensure_ascii=False)
            target = ('    .asciz ' + quoted) if path.suffix == '.bs' else quoted
            # Adjacent C string literals are one string at runtime. Accept
            # their combined value so import never flattens hand-laid lines.
            if text[start:end] == target or current == quoted[1:-1]:
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
    parser.add_argument('action', choices=('extract', 'check', 'import', 'resolve-controls'))
    parser.add_argument('--include-draft', action='store_true')
    args = parser.parse_args()
    if args.action == 'extract':
        extract()
    elif args.action == 'resolve-controls':
        resolve_edge_controls()
    else:
        raise SystemExit(import_text(args.action == 'check', not args.include_draft))


if __name__ == '__main__':
    main()
