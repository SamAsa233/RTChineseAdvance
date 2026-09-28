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
    if name == 'src/scenes/results.c':
        # 结算页译文分散在分数格式串、两组评语和运行时前缀中。
        # 按使用位置逐项核对已校对译文，避免同一句话出现在别处时误判。
        rows = json.loads((ARCHIVE / 'src/results.json').read_text(encoding='utf-8'))
        translations = {row['key']: row for row in rows}
        if key not in translations or translations[key]['stage'] != 5:
            return None
        wanted = json.dumps(translations[key]['translation'], ensure_ascii=False)
        if key == 'results_scoring':
            match = re.search(r'"\.5:1"\s*("(?:\\.|[^"\\])*")\s*"\.6:0"', text)
            return [(match.start(1), match.end(1), wanted[1:-1])] if match and match.group(1) == wanted else None
        if key in ('results_also', 'results_more'):
            groups = c_initializer(text, 'results_try_again_comment_pool')
            index = 1 if key == 'results_also' else 2
            return [groups[index]] if groups and len(groups) == 3 and groups[index][2] == wanted[1:-1] else None
        if key in ('results_but', 'results_moreover', 'results_further'):
            # 第一个前缀用于“先差后好”，后两个按通过项目的数量选用。
            pattern = r'snprintf\(commentsText,\s*0x100,\s*"%s%s",\s*("(?:\\.|[^"\\])*")\s*,\s*modifiedComment\)'
            matches = list(re.finditer(pattern, text))
            index = ('results_but', 'results_moreover', 'results_further').index(key)
            if len(matches) != 3 or matches[index].group(1) != wanted:
                return None
            match = matches[index]
            return [(match.start(1), match.end(1), wanted[1:-1])]
        if key in ('results_acceptable', 'results_for_now', 'results_so_so'):
            groups = c_initializer(text, 'results_ok_comment_pool')
            index = ('results_acceptable', 'results_for_now', 'results_so_so').index(key)
            return [groups[index]] if groups and len(groups) == 3 and groups[index][2] == wanted[1:-1] else None
        if key == 'results_well':
            # 最后一句位于两个地区分支；必须两侧都已翻译才算完成。
            anchor = 'const char *results_ok_comment_pool[] = {'
            start = text.find(anchor)
            end = text.find('};', start)
            if start < 0 or end < 0:
                return None
            matches = list(LITERAL.finditer(remove_comments(text[start:end])))
            if len(matches) != 5 or matches[3].group() != wanted or matches[4].group() != wanted:
                return None
            match = matches[3]
            return [(start + match.start(), start + match.end(), wanted[1:-1])]
        return None
    if name == 'src/scenes/data_check.c':
        # 统计页译文是同一个函数里依次 strcat 的片段，不是同名数组。
        # 按调用顺序定位，并核对阶段 5 译文；顺序变了就留在 TODO。
        rows = json.loads((ARCHIVE / 'src/data_check.json').read_text(encoding='utf-8'))
        translated = {row['key']: row for row in rows}
        if key not in translated or translated[key]['stage'] != 5:
            return None
        if key == 'data_check_title':
            title = re.search(r'data_check_print_line\(0,\s*1,\s*("(?:\\.|[^"\\])*")', text)
            group = title
            offset = 0
        else:
            positions = {
                'data_check_avg_score': 2, 'data_check_avg_score_suffix': 3,
                'data_check_play_count': 4, 'data_check_play_count_suffix': 5,
                'data_check_first_pass': 6, 'data_check_not_yet_1': 7,
                'data_check_count_1': 8, 'data_check_first_great_pass': 9,
                'data_check_not_yet_2': 10, 'data_check_count_2': 11,
            }
            start = text.find('void data_check_print_page(s32 id) {')
            end = text.find('// Scene Stop', start)
            if key not in positions or start < 0 or end < 0:
                return None
            literals = list(re.finditer(
                r'strcat\(string,\s*("(?:\\.|[^"\\])*")\s*\)', text[start:end]))
            index = positions[key]
            if index >= len(literals):
                return None
            group = literals[index]
            offset = start
        if group is None:
            return None
        quoted = group.group(1)
        if quoted != json.dumps(translated[key]['translation'], ensure_ascii=False):
            return None
        return [(offset + group.start(1), offset + group.end(1), quoted[1:-1])]
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


def cafe_translation_installed(text, key, translation):
    """逐个检查咖啡馆译文所在剧情分支，避免只凭搜索到中文就删除 TODO。

    归档键不是 C 变量名；中文断行可不同于英文，但可见文字、两个地区
    分支和控制码必须与已校对译文及原版显示逻辑相符。
    """
    event_cases = {
        'cafe_line_1': ('CAFE_EV_INIT_DIALOGUE', 0),
        'cafe_line_2': ('CAFE_EV_INIT_DIALOGUE', 3),
        'cafe_line_3': ('CAFE_EV_INIT_DIALOGUE', 4),
        'cafe_line_4': ('CAFE_EV_INIT_DIALOGUE', 5),
        'cafe_line_5': ('CAFE_EV_INIT_DIALOGUE', 5),
        'cafe_line_12': ('CAFE_EV_CAMPAIGN_CLEAR_01', 0),
        'cafe_line_13': ('CAFE_EV_OFFER_CLEAR_00', 0),
        'cafe_line_14': ('CAFE_EV_OFFER_CLEAR_01', 0),
        'cafe_line_15': ('CAFE_EV_OFFER_CLEAR_01', 1),
        'cafe_line_16': ('CAFE_EV_OFFER_CLEAR_02_Y', 0),
        'cafe_line_17': ('CAFE_EV_OFFER_CLEAR_02_N', 0),
        'cafe_line_19': ('CAFE_EV_UPCOMING_CAMPAIGN_00', 0),
        'cafe_line_20': ('CAFE_EV_ALL_CAMPAIGNS_CLEAR_00', 0),
        'cafe_line_21': ('CAFE_EV_ALL_CAMPAIGNS_CLEAR_01', 0),
        'cafe_line_extra_1': ('CAFE_EV_EXTRA_CAMPAIGNS_CLEAR_00', 0),
        'cafe_line_extra_2': ('CAFE_EV_ALL_CAMPAIGNS_BIG_CLEAR_00', 0),
        'cafe_line_extra_3': ('CAFE_EV_ALL_CAMPAIGNS_BIG_CLEAR_01', 0),
    }
    topic_cases = {
        'cafe_line_6': 'CAFE_TOPIC_CAMPAIGN_CLEAR',
        'cafe_line_7': 'CAFE_TOPIC_TROUBLE_CLEARING_LEVEL',
        'cafe_line_8': 'CAFE_TOPIC_TROUBLE_GETTING_MEDAL',
        'cafe_line_9': 'CAFE_TOPIC_TROUBLE_CLEARING_CAMPAIGN',
        'cafe_line_10': 'CAFE_TOPIC_REMEMBERING',
        'cafe_line_11': 'CAFE_TOPIC_UPCOMING_CAMPAIGN',
    }
    # 为什么核对控制码：它们会切换高亮和字号，只对上可见文字仍可能显示错。
    highlight = [r'\0051', r'\0015', r'\0054', r'\0018']
    emphasis = [r'\0032', r'\001l'] + highlight[:2] + [r'\0030', r'\001s'] + highlight[2:]
    control_sequences = {
        **{name: highlight for name in ('cafe_line_6', 'cafe_line_7',
                                        'cafe_line_8', 'cafe_line_9', 'cafe_line_11')},
        'cafe_line_13': highlight[:2] * 2 + highlight[2:],
        'cafe_line_14': emphasis,
        'cafe_line_18': highlight[2:] * 2 + highlight[:2] * 2 + highlight[2:],
        'cafe_line_21': emphasis,
        'cafe_line_extra_1': emphasis,
        'cafe_line_extra_3': emphasis,
    }

    def case_body(name, kind):
        indent = '                ' if kind == 'topic' else '        '
        pattern = rf'(?m)^{indent}case {re.escape(name)}:'
        match = re.search(pattern, text)
        if not match:
            return None
        next_case = re.search(r'(?m)^' + indent + r'(?:case|default)\b',
                              text[match.end():])
        return text[match.end():match.end() + next_case.start()] if next_case else None

    def literals(expression):
        return ''.join(literal[1:-1] for literal in LITERAL.findall(remove_comments(expression)))

    def visible(value):
        return CONTROL_TOKEN.sub('', value).replace(r'\n', '\n')

    def compact(value):
        return ''.join(char for char in visible(value) if not char.isspace())

    if key in topic_cases:
        section = case_body(topic_cases[key], 'topic')
        if section is None:
            return False
        if key == 'cafe_line_10':
            assignments = re.findall(r'\bstring\s*=\s*(.*?);', section, re.S)
            values = [literals(assignments[0])] if assignments else []
        else:
            if len(re.findall(r'strcat\(s,\s*levelName\s*\)', section)) != 1:
                return False
            fragments = re.findall(r'strcat\(s,\s*(.*?)\);', section, re.S)
            values = [''.join(literals(fragment) for fragment in fragments)]
    elif key == 'cafe_line_18':
        section = case_body('CAFE_EV_CAMPAIGN_ADVICE_00', 'event')
        if section is None:
            return False
        branches = re.search(r'#ifdef\s+PARADISE\s*string\s*=\s*(.*?)'
                             r'#else\s*string\s*=\s*(.*?)#endif\s*(.*?);', section, re.S)
        values = ([literals(branches.group(side) + branches.group(3)) for side in (1, 2)]
                  if branches else [])
    elif key in event_cases:
        case, index = event_cases[key]
        section = case_body(case, 'event')
        assignments = re.findall(r'\bstring\s*=\s*(.*?);', section or '', re.S)
        values = [literals(assignments[index])] if len(assignments) > index else []
    else:
        return False

    if key in ('cafe_line_4', 'cafe_line_5'):
        # 为什么合并核对：游玩时间最长的分支把归档第 4、5 句放在同一字符串。
        rows = json.loads((ARCHIVE / 'src/cafe.json').read_text(encoding='utf-8'))
        parts = {row['key']: row['translation'] for row in rows}
        translation = parts['cafe_line_4'] + parts['cafe_line_5']
    expected = compact(translation)
    controls = control_sequences.get(key, [])
    return bool(values and all(compact(value) == expected
                               and CONTROL_TOKEN.findall(value) == controls
                               and len(visible(value).splitlines()) <= 6
                               for value in values))


def notice_translation_installed(text, archive_name, key, translation):
    """核对手工拼接的入库通知，防止已译片段继续误报未定位。"""
    if archive_name == 'src/arrival.json':
        # 标题和结尾分别占一个打印器；动态资料标题由第三个打印器插入。
        calls = re.findall(r'text_printer_set_string\(printer,\s*("(?:\\.|[^"\\])*")\)', text)
        if len(calls) != 2:
            return False
        if key == 'arrival_title':
            return calls[0][1:-1].strip() == translation + '：'
        if key == 'arrival_message_template':
            return calls[1][1:-1].strip() == translation.strip()
        return False
    if archive_name != 'src/game_select.json':
        return False
    if key == 'game_select_new_game':
        case = re.search(r'case CAMPAIGN_GIFT_NEW_GAME:(.*?)\breturn\s*'
                         r'("(?:\\.|[^"\\])*")\s*;', remove_comments(text), re.S)
        return bool(case and case.group(2) == json.dumps(translation, ensure_ascii=False))

    # 奖励通知不是六个独立字符串，而是格式串加动态关卡名、奖品名和种类。
    # 五个片段共同对上且参数顺序正确时，才认为每个键已接入。
    rows = json.loads((ARCHIVE / 'src/game_select.json').read_text(encoding='utf-8'))
    targets = {row['key']: json.dumps(row['translation'], ensure_ascii=False)[1:-1]
               for row in rows}
    if key not in targets:
        return False
    fmt = (r'\001C' + targets['game_select_perfect_prefix'] + '%s'
           + targets['game_select_perfect_suffix'] + r'\n'
           + targets['game_select_gift_prefix']
           + '%s%s' + targets['game_select_gift_suffix'] + r'\n')
    call = re.search(r'snprintf\(notice->text,\s*sizeof\(notice->text\),\s*'
                     r'("(?:\\.|[^"\\])*")\s*,\s*level->name,\s*giftTitle,\s*giftKind\s*\)', text, re.S)
    kind = re.search(r'giftKind\s*=\s*\(giftType\s*==\s*CAMPAIGN_GIFT_SONG\)\s*'
                     r'\?\s*("(?:\\.|[^"\\])*")\s*:\s*""', text)
    return bool(call and call.group(1)[1:-1] == fmt and kind
                and kind.group(1)[1:-1] == targets['game_select_gift_middle'])


def conditional_level_translation_installed(text, key, translation):
    """核对关卡表的地区双分支：两侧都匹配阶段 5 译文才移除 TODO。"""
    specs = {
        'level_bari_1_result_2': ('SNAPPY_TRIO', 'OK', 1),
        'level_bari_1_result_3': ('SNAPPY_TRIO', 'SUPERB', 2),
        'level_baikin_1_desc': ('SICK_BEATS', 'Level Desc.', 2),
        'level_tap_dance_1_result_1': ('TAP_TRIAL', 'TRY_AGAIN', 2),
        'level_hanabi_1_desc': ('FIREWORKS', 'Level Desc.', 2),
        'level_toss_boys_1_desc': ('TOSS_BOYS', 'Level Desc.', 2),
        'level_toss_boys_1_result_1': ('TOSS_BOYS', 'TRY_AGAIN', 2),
        'level_toss_boys_1_result_2': ('TOSS_BOYS', 'OK', 1),
        'level_toss_boys_1_result_3': ('TOSS_BOYS', 'SUPERB', 2),
        'level_toss_boys_2_desc': ('TOSS_BOYS_2', 'Level Desc.', 2),
        'level_toss_boys_2_result_2': ('TOSS_BOYS_2', 'OK', 1),
        'level_toss_boys_2_result_3': ('TOSS_BOYS_2', 'SUPERB', 2),
        'level_quiz_1_result_1': ('QUIZ_SHOW', 'TRY_AGAIN', 1),
        'level_quiz_1_result_2': ('QUIZ_SHOW', 'OK', 2),
        'level_cafe_counsel': ('CAFE', 'Level Name', 2),
    }
    if key not in specs:
        return False
    entry, field, count = specs[key]
    marker = re.search(r'/\* ' + re.escape(entry) + r' \*/ \{', text)
    if not marker:
        return False
    following = re.search(r'(?m)^    /\* [A-Z][A-Z0-9_]+ \*/ \{', text[marker.end():])
    if not following:
        return False
    section = text[marker.end():marker.end() + following.start()]
    expected = json.dumps(translation, ensure_ascii=False)[1:-1]

    if field == 'Level Desc.':
        # 描述的共同前后句与地区专用末句被 #ifdef 切开，需拼出两版全文。
        region = re.search(r'/\* Level Desc\.\s*\*/(.*?)/\* Level Icon\s*\*/', section, re.S)
        if not region:
            return False
        branches = re.search(r'(.*?)#ifdef\s+PARADISE(.*?)#else(.*?)#endif(.*)',
                             region.group(1), re.S)
        if not branches:
            return False
        values = [''.join(literal[1:-1] for literal in LITERAL.findall(
                  branches.group(1) + branches.group(side) + branches.group(4)))
                  for side in (2, 3)]
        # \0023 是细菌博士说明的字形/显示格式码，必须保留在最前面。
        expected = (r'\0023' if key == 'level_baikin_1_desc' else '') + expected
    else:
        # 评价语和关卡名直接出现在带标签的槽位；双分支须找到两个同名标签。
        pattern = r'/\*\s*' + re.escape(field) + r'\s*\*/\s*("(?:\\.|[^"\\])*")'
        values = [match[1:-1] for match in re.findall(pattern, section)]
    return len(values) == count and all(value == expected for value in values)


def extract():
    output, unresolved = [], []
    previous = {}
    # 这些条目已手动写在源码中，归档键却不等于 C 数组名。按实际数组槽位
    # 逐条核对阶段 5 译文后才跳过，防止源码变化时误报“已完成”。
    manual_slots = {
        'data/data_room/reading.json': ('reading_material_error', {
            'reading_material_error_1': 0, 'reading_material_error_2': 1,
        }),
        'data/medal_corner/toys_menu.inc.json': ('toys_menu_levels', {
            'toy_neko_machine': 0, 'toy_uma_machine': 1,
            'toy_kokuhaku_machine': 2, 'toy_rap_machine': 3,
        }),
        'data/medal_corner/endless_menu.inc.json': ('endless_menu_levels', {
            # 第一个条目有两个条件编译分支，尚未接入，仍须保留 TODO。
            'endless_baikin_hakase_sp': 0, 'endless_quiz_special': 1,
            'endless_manekin_factory': 2,
        }),
    }
    if TABLE.exists():
        with TABLE.open(encoding='utf-8', newline='') as stream:
            previous = {row['id']: row for row in csv.DictReader(stream, delimiter='\t')}
    for (json_path, path, base), members in grouped_archive().items():
        archive_name = json_path.relative_to(ARCHIVE).as_posix()
        if (archive_name in ('src/arrival.json', 'src/game_select.json')
                and path is not None and len(members) == 1):
            key, row = members[0]
            # 为什么单独检查：界面直接调用或运行时拼接，没有同名 C 字符串。
            if (row['stage'] == 5 and notice_translation_installed(
                    path.read_text(encoding='utf-8'), archive_name,
                    key, row['translation'])):
                continue
        if (archive_name == 'data/game_select/levels.inc.json'
                and path is not None and len(members) == 1):
            key, row = members[0]
            # 为什么逐地区检查：自动定位器遇到 #ifdef 时不会猜哪一侧才正确。
            if (row['stage'] == 5 and conditional_level_translation_installed(
                    path.read_text(encoding='utf-8'), key, row['translation'])):
                continue
        if (archive_name in ('src/cafe.json', 'src/cafe_add.json')
                and path is not None and len(members) == 1):
            key, row = members[0]
            # 为什么单独核对：动态关卡名和手工断行的对话没有同名 C 数组。
            # 只有对应剧情分支真的显示已校对文字，才从未定位清单移除。
            if (row['stage'] == 5 and cafe_translation_installed(
                    path.read_text(encoding='utf-8'), key, row['translation'])):
                continue
        if (archive_name == 'data/data_room/reading_material.inc.json'
                and base == 'reading_greeting' and path is not None
                and len(members) == 1):
            key, row = members[0]
            text = path.read_text(encoding='utf-8')
            # 欢迎信的英文标题在两个地区分支里；逐分支拼接相邻 C 字符串，
            # 只有两侧都与阶段 5 译文（含真实换行）一致才算已接入。
            markers = ('/* WELCOME ', '/* MANUAL ',
                       '/* BODY ----------------------------------------------------------- */',
                       '/* STYLE ---------------------------------------------------------- */')
            if all(marker in text for marker in markers):
                material = text.split(markers[0], 1)[1].split(markers[1], 1)[0]
                body = material.split(markers[2], 1)[1].split(markers[3], 1)[0]
                clean = remove_comments(body)
                branches = re.search(r'#ifdef\s+PARADISE(.*?)#else(.*?)#endif', clean, re.S)
                if branches and row['stage'] == 5:
                    expected = json.dumps(row['translation'], ensure_ascii=False)[1:-1]
                    values = [''.join(literal[1:-1] for literal in LITERAL.findall(
                        clean[:branches.start()] + branches.group(side) + clean[branches.end():]))
                        for side in (1, 2)]
                    if values == [expected, expected]:
                        continue
        if (archive_name == 'src/debug_menu.json' and base == 'debug_menu_title'
                and path is not None and len(members) == 1):
            key, row = members[0]
            text = path.read_text(encoding='utf-8')
            # 调试页标题在函数调用里而不是 C 数组里；核对调用参数再消除误报。
            call = r'bmp_font_obj_print_l\(\s*gDebugMenu->objFont,\s*'
            if (row['stage'] == 5 and re.search(
                    call + re.escape(json.dumps(row['translation'], ensure_ascii=False)), text)):
                continue
        if (archive_name == 'src/debug_menu_table.json' and base == 'debug_menu_52'
                and path is not None and len(members) == 1):
            key, row = members[0]
            text = path.read_text(encoding='utf-8')
            # 归档的第 52 项因英文原文拼写不同没法自动对位；用相邻
            # 表项名称限定范围，确认实际标签已是阶段 5 译文。
            if '/* Sick Beats Endless */' in text and '/* Quiz Show Endless */' in text:
                section = text.split('/* Sick Beats Endless */', 1)[1].split('/* Quiz Show Endless */', 1)[0]
                labels = re.findall(r'/\*\s*Label\s*\*/\s*("(?:\\.|[^"\\])*")', section)
                if row['stage'] == 5 and labels == [json.dumps(row['translation'], ensure_ascii=False)]:
                    continue
        if (archive_name == 'data/medal_corner/endless_menu.inc.json'
                and base == 'endless_ura_otoko' and path is not None
                and len(members) == 1):
            key, row = members[0]
            text = path.read_text(encoding='utf-8')
            # 第一项有两个 #ifdef 地区分支；只有两侧都等于阶段 5 译名，
            # 才把它算作已接入，避免只改一个版本就漏掉另一个版本。
            if '/* MR_UPBEAT */' in text and '/* SICK_BEATS */' in text:
                section = text.split('/* MR_UPBEAT */', 1)[1].split('/* SICK_BEATS */', 1)[0]
                titles = re.findall(r'/\*\s*Title\s*\*/\s*("(?:\\.|[^"\\])*")', section)
                if row['stage'] == 5 and titles == [json.dumps(row['translation'], ensure_ascii=False)] * 2:
                    continue
        if archive_name in manual_slots and path is not None and len(members) == 1:
            initializer, positions = manual_slots[archive_name]
            key, row = members[0]
            position = positions.get(key)
            groups = c_initializer(path.read_text(encoding='utf-8'), initializer)
            if (position is not None and row['stage'] == 5 and groups
                    and position < len(groups) and groups[position]
                    and groups[position][2].endswith(row['translation'])):
                # 只有对应槽位确实包含已校对中文时，才消除误报。
                continue
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
        # The 13 keyed poster entries are three concatenated source strings;
        # the groups are assembled manually so control-code boundaries stay
        # intact and the non-stage-5 WISH translation remains TODO.
        if (json_path.relative_to(ARCHIVE).as_posix() == 'games/drum_live/drum_live_menu_engine.json'
                and base == 'drum_live_menu_poster_desc'):
            unresolved = [item for item in unresolved if not item.startswith(
                f'{json_path.relative_to(ARCHIVE)}:{base}[')]
            unresolved.append(f'{json_path.relative_to(ARCHIVE)}:{base}[42]: TODO 未校对（阶段 2）')
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
            if filename == 'src/scenes/debug_menu_table.c' and key == 'debug_menu_51':
                # 导入器原先只看到 PARADISE 一侧；校验两侧译名，
                # 防止另一种地区版本悄悄保留英文。
                if '/* Mr. Upbeat */' not in text or '/* Sick Beats Endless */' not in text:
                    problems.append(row['id'] + ': menu markers missing')
                    continue
                section = text.split('/* Mr. Upbeat */', 1)[1].split('/* Sick Beats Endless */', 1)[0]
                labels = re.findall(r'/\*\s*Label\s*\*/\s*("(?:\\.|[^"\\])*")', section)
                if labels != [json.dumps(row['target'], ensure_ascii=False)] * 2:
                    problems.append(row['id'] + ': conditional branches differ')
                continue
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
