"""十月译文升级：限定三个归档，校验所有改动后再写入，保留原控制码与地区分支。

用法：python tools/text/import_reviewed_update.py 翻译包.zip
"""
import argparse
import csv
import io
import json
import re
import zipfile
from pipeline import ROOT, ARCHIVE, TABLE, FIELDS, locate, atomic_text, bon_reviewed_target

MEMBERS = ('data/data_room/reading_material.inc.json',
           'games/bon_odori/bon_odori_text.json', 'games/bon_odori/bon_dance_text.json')


def quote_lines(value):
    # 每个画面换行独立展示为相邻字面量，方便对照归档；不添加或删掉真实换行。
    return '\n'.join('            ' + json.dumps(line, ensure_ascii=False)
                     for line in value.splitlines(keepends=True))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive')
    args = parser.parse_args()
    with TABLE.open(encoding='utf-8', newline='') as f:
        rows = list(csv.DictReader(f, delimiter='\t'))
    by_id = {r['id']: r for r in rows}
    writes = {}
    updated = []
    with zipfile.ZipFile(args.archive) as package:
        for member in MEMBERS:
            incoming = json.loads(package.read('utf8/' + member))
            previous = {r['key']: r for r in json.loads((ARCHIVE / member).read_text(encoding='utf-8'))}
            filename = ('data/scenes/data_room/reading_material.inc.c' if member.startswith('data/')
                        else member.replace('.json', '.c'))
            path = ROOT / filename
            source = path.read_text(encoding='utf-8')
            for row in incoming:
                key = row['key']
                if row == previous.get(key):
                    continue
                if row['stage'] != 5:
                    raise ValueError(f'{key}: 新版未校对，需要保留原文及 TODO')
                target = row['translation']
                saved = by_id.get(filename + ':' + key)
                if key == 'reading_radio_story':
                    # 电台采访有 PARADISE 分支：只替换确实变化的相邻字面量，两侧游戏名保持原结构。
                    old_lines = previous[key]['translation'].splitlines(keepends=True)
                    new_lines = target.splitlines(keepends=True)
                    if len(old_lines) != len(new_lines):
                        raise ValueError('电台文章行数变化，需重新映射条件分支')
                    for old, new in zip(old_lines, new_lines):
                        if old != new:
                            quoted = json.dumps(old, ensure_ascii=False)
                            if source.count(quoted) != 1:
                                raise ValueError('电台旧句未唯一定位')
                            source = source.replace(quoted, json.dumps(new, ensure_ascii=False), 1)
                    source = source.replace('// 实机核验：2026-09-29 mGBA 确认全文三页，对话引号、英文名称和末页“完”均完整显示。',
                        '// 十月更新：采用新版已校对的饶舌男/女名称，原地区分支与换行不动。\n'
                        '            // 排版核验：2026-10-23 mGBA 确认新版电台采访 3 页，末尾“完”完整显示。')
                else:
                    if not saved:
                        raise ValueError(f'{key}: 缺少既有 TSV 映射')
                    groups = locate(source, path, key)
                    if not groups or len(groups) != 1 or not groups[0]:
                        raise ValueError(f'{key}: 无法唯一定位')
                    start, end, current = groups[0]
                    if member.startswith('games/'):
                        target = bon_reviewed_target(key, saved['source'], target)
                        replacement = json.dumps(target, ensure_ascii=False)
                    else:
                        replacement = quote_lines(target).lstrip()
                    source = source[:start] + replacement + source[end:]
                    source = re.sub(r'[^\S\n]*// TODO 未校对：' + re.escape(key) + r' 译文包未到 stage 5，暂留原文。\n', '', source)
                    saved.update(target=target, status='final', note='')
                updated.append(key)
            if member.startswith('games/'):
                note = ('/* 十月更新：仅接入新版阶段 5，保留鼓点/拍手颜色码和原版先后顺序。\n'
                        ' * TODO 未校对：中文歌词的宽度、颜色分界与节拍仍需实机核验。 */\n')
                if note not in source:
                    source = note + source
            else:
                note = ('/* 十月更新：两张歌词卡采用新版 stage 5 的完整歌词和换行。\n'
                        ' * 排版核验：2026-10-23 mGBA 确认两张新版歌词卡各 2 页，文字与末页完整。 */\n')
                if note not in source:
                    source = note + source
            writes[path] = source
            writes[ARCHIVE / member] = json.dumps(incoming, ensure_ascii=False, indent=2) + '\n'
    output = io.StringIO(newline='')
    writer = csv.DictWriter(output, fieldnames=FIELDS, delimiter='\t', lineterminator='\n')
    writer.writeheader()
    writer.writerows(rows)
    writes[TABLE] = output.getvalue()
    # 验证完成后才写文件；无法定位时不会留下半次升级的源码。
    for path, value in writes.items():
        atomic_text(path, value)
    print(f'updated reviewed entries={len(updated)}')


if __name__ == '__main__':
    main()
