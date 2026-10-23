"""十月新要求验收：直接核对三份归档与源码，覆盖未进入 TSV 的资料室分支。"""
import csv
import json
import re
from pathlib import Path
import pipeline as p
from import_reviewed_update import MEMBERS

STORIES = {'reading_night_walk_story', 'reading_horse_machine_story', 'reading_radio_story',
           'reading_final_story', 'reading_manzai_story', 'reading_praise_story'}
BODIES = {'reading_formula_content', 'reading_diagnosis', 'reading_poem'}


def audit():
    with p.TABLE.open(encoding='utf-8', newline='') as f:
        all_rows = list(csv.DictReader(f, delimiter='\t'))
        table = {r['key']: r for r in all_rows if r['file'] == 'data/scenes/data_room/reading_material.inc.c'}
        by_id = {r['id']: r for r in all_rows}
    total = 0
    for member in MEMBERS:
        path = p.ROOT / ('data/scenes/data_room/reading_material.inc.c' if member.startswith('data/')
                         else member.replace('.json', '.c'))
        text = path.read_text(encoding='utf-8')
        rows = json.loads((p.ARCHIVE / member).read_text(encoding='utf-8'))
        for row in rows:
            key, target = row['key'], row['translation']
            if row['stage'] != 5:
                # 未校对歌词不能被中文定稿替换；保留上游英文更新及可搜索标记。
                assert 'TODO 未校对' in text and key in text
                assert key in (p.ROOT / 'text/zh_hans/TODO_未校对.md').read_text(encoding='utf-8')
                assert key not in table or table[key]['status'] == 'draft'
                assert json.dumps(target, ensure_ascii=False)[1:-1] not in text
                total += 1
                continue
            if key in STORIES:
                assert p.reading_story_installed(text, key, target), key
            elif key.startswith('reading_haiku_') and key[-1].isdigit():
                assert p.reading_haiku_installed(text, key, target), key
            elif key in BODIES:
                # 用归档中文校验可见正文和控制码；不能只比较旧 TSV 中的完整 BODY。
                assert p.reading_body_installed(text, key, table[key]['source'], target), key
            else:
                # 每种地区路径分别展开后定位；不能把两个分支拼在一起误判为正确。
                for side in (1, 2):
                    selected = re.sub(r'#ifdef\s+(?:PARADISE|BRIT)(.*?)#else(.*?)#endif',
                                      lambda m: m[side], text, flags=re.S)
                    groups = p.locate(selected, path, key)
                    assert groups and len(groups) == 1 and groups[0], key
                    current = groups[0][2]
                    expected = json.dumps(target, ensure_ascii=False)[1:-1]
                    if member.startswith('games/'):
                        # 归档是日文可见文本；颜色码沿用导入前记录的 C 原文。
                        original = by_id[path.relative_to(p.ROOT).as_posix() + ':' + key]['source']
                        expected = p.bon_reviewed_target(key, original, target)
                    assert current == expected, f'{key}: text or newline mismatch'
            total += 1
    return total


if __name__ == '__main__':
    print(f'{audit()} archive entries verified against current source in both region paths')
