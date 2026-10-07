"""Restore C string layout and the café dialogue's framing blank lines.

The imported Chinese may need different *internal* line breaks to fit the
screen. The café's leading/trailing blanks, however, place text vertically;
they must follow the original port. Physical C string lines are only source
formatting and do not introduce extra in-game line breaks.

汉化改动：中文句长与英文不同，句子内部可以重新安排画面换行；咖啡馆首尾的空行负责垂直定位，必须按原版恢复。
这个脚本还会保留 C 源码中相邻字符串的排版，因为源码物理换行本身不会在游戏画面中产生换行。
"""

from collections import defaultdict
import csv
from io import StringIO
import json
import re
import subprocess

from pipeline import LITERAL, ROOT, TABLE, FIELDS, atomic_text, locate, remove_comments

# This longer Chinese sentence needs two content lines. Reducing one empty
# line after it preserves all words within the café dialogue box.
SHORTER_BOTTOM_MARGIN = {'cafe_dialogue_adhd[0]'}


def edge_count(value, at_start):
    """Count consecutive displayed newlines at one edge of a C literal."""
    pattern = r'^(?:\\n)*' if at_start else r'(?:\\n)*$'
    return len(re.search(pattern, value).group()) // 2


def target_edge_count(value, at_start):
    return len(value) - len(value.lstrip('\n')) if at_start else len(value) - len(value.rstrip('\n'))


def index_for(row, rows, groups):
    siblings = sorted(rows, key=lambda item: int(m.group(1)) if (m := re.search(r'\[(\d+)\]$', item['key'])) else -1)
    if len(groups) == len(siblings):
        return siblings.index(row)
    indexes = [re.search(r'\[(\d+)\]$', item['key']) for item in siblings]
    if all(indexes) and max(int(match.group(1)) for match in indexes) < len(groups):
        return int(re.search(r'\[(\d+)\]$', row['key']).group(1))
    return None


def render(value, baseline, start, end):
    original = baseline[start:end]
    literals = list(LITERAL.finditer(remove_comments(original)))
    # Non-string tokens such as CHAR_A_BUTTON_UTF8 must stay between literals.
    if len(literals) < 2 or LITERAL.sub('', remove_comments(original)).strip():
        return json.dumps(value, ensure_ascii=False)
    second = start + literals[1].start()
    line_start = baseline.rfind('\n', 0, second) + 1
    indent = re.match(r'\s*', baseline[line_start:second]).group()
    parts = value.splitlines(keepends=True)
    return ('\n' + indent).join(json.dumps(part, ensure_ascii=False) for part in parts)


def main():
    with TABLE.open(encoding='utf-8', newline='') as stream:
        rows = list(csv.DictReader(stream, delimiter='\t'))
    old_targets = {row['id']: row['target'] for row in rows}
    committed = subprocess.run(['git', 'show', 'HEAD:text/zh_hans/translations.tsv'],
                               cwd=ROOT, capture_output=True, text=True,
                               encoding='utf-8', check=True).stdout
    committed_targets = {row['id']: row['target'] for row in csv.DictReader(StringIO(committed), delimiter='\t')}
    cafe_fixed = 0
    for row in rows:
        if row['file'] != 'data/scenes/cafe/dialogue.c' or row['status'] != 'final' or row['note']:
            continue
        # A blank top/bottom line is a layout frame, unlike the sentence
        # breaks that the translated text may legitimately reposition.
        for at_start in (True, False):
            expected = edge_count(row['source'], at_start)
            if not at_start and row['key'] in SHORTER_BOTTOM_MARGIN:
                expected -= 1
            existing = target_edge_count(row['target'], at_start)
            extra = '\n' * max(0, expected - existing)
            row['target'] = extra + row['target'] if at_start else row['target'] + extra
        cafe_fixed += row['target'] != old_targets[row['id']]
    if cafe_fixed:
        out = StringIO(newline='')
        writer = csv.DictWriter(out, fieldnames=FIELDS, delimiter='\t', lineterminator='\n')
        writer.writeheader()
        writer.writerows(rows)
        atomic_text(TABLE, out.getvalue())

    by_file = defaultdict(list)
    all_by_file = defaultdict(lambda: defaultdict(list))
    for row in rows:
        all_by_file[row['file']][row['key'].split('[', 1)[0]].append(row)
        if row['status'] == 'final' and not row['note'] and row['file'].endswith('.c'):
            by_file[row['file']].append(row)
    files_fixed = entries_fixed = 0
    for name, members in by_file.items():
        path = ROOT / name
        current = path.read_text(encoding='utf-8')
        baseline = subprocess.run(['git', 'show', 'text_utf8:' + name], cwd=ROOT,
                                  capture_output=True, text=True, encoding='utf-8', check=True).stdout
        groups_by_base = all_by_file[name]
        edits = []
        for row in members:
            base = row['key'].split('[', 1)[0]
            old_groups, new_groups = locate(baseline, path, row['key']), locate(current, path, row['key'])
            if not old_groups or not new_groups:
                continue
            old_index = index_for(row, groups_by_base[base], old_groups)
            new_index = index_for(row, groups_by_base[base], new_groups)
            if old_index is None or new_index is None:
                continue
            if old_groups[old_index] is None or new_groups[new_index] is None:
                continue  # Keep #ifdef alternatives for manual inspection.
            start, end, source = new_groups[new_index]
            old_start, old_end, _ = old_groups[old_index]
            old_value = json.dumps(old_targets[row['id']], ensure_ascii=False)[1:-1]
            committed_value = json.dumps(committed_targets.get(row['id'], ''), ensure_ascii=False)[1:-1]
            new_value = json.dumps(row['target'], ensure_ascii=False)[1:-1]
            if source not in (old_value, new_value, committed_value):
                continue  # Do not touch source that another person edited.
            replacement = render(row['target'], baseline, old_start, old_end)
            if current[start:end] != replacement:
                edits.append((start, end, replacement))
        if edits:
            for start, end, value in sorted(edits, reverse=True):
                current = current[:start] + value + current[end:]
            atomic_text(path, current)
            files_fixed += 1
            entries_fixed += len(edits)
    print(f'cafe edges={cafe_fixed}, C entries={entries_fixed}, files={files_fixed}')


if __name__ == '__main__':
    main()
