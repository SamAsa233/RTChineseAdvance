"""校验已映射译文的字形与控制码，并报告可能超宽的界面文本。

用法：python tools/text/check_text.py
报告：build/text_report/validation.txt 和 layout_warnings.txt。
"""

from collections import Counter
import csv
import json
from pathlib import Path
import re

from pipeline import ARCHIVE, CONTROL_TOKEN, EDGE_CONTROL_TOKEN, ROOT, TABLE, atomic_text

RANGE = re.compile(r'\{\s*\w+_bin,\s*(\w+)_bin,\s*0x([0-9a-fA-F]+),\s*0x([0-9a-fA-F]+)\s*\}')
VISIBLE = re.compile(r'\\(?:[0-7]{1,3}|x[0-9a-fA-F]{2})')
SPACING = {'small': 1, 'medium': 2, 'large': 2}
READING_TITLES = {
    row['key'] for index, row in enumerate(json.loads(
        (ARCHIVE / 'data/data_room/reading_material.inc.json').read_text(encoding='utf-8')))
    if index < 39 and index % 2 == 0
}


def font_ranges(size):
    text = (ROOT / 'data/text_printer_data.c').read_text(encoding='utf-8')
    section = text.split(f'struct FontGlyphRange font_glyph_range_{size}[] = {{', 1)[1].split('END_OF_RANGE', 1)[0]
    ranges = []
    for symbol, lo, hi in RANGE.findall(section):
        widths = (ROOT / 'bin/font' / size / (symbol + '.bin')).read_bytes()
        start, end = int(lo, 16), int(hi, 16)
        # One inherited PUA range advertises one slot beyond its width file.
        ranges.append((start, min(end, start + len(widths) - 1), widths))
    return ranges


def glyph_width(ranges, codepoint):
    return next((widths[codepoint - lo] for lo, hi, widths in ranges if lo <= codepoint <= hi), 0)


def display_text(raw):
    raw = CONTROL_TOKEN.sub('', raw)
    raw = raw.replace(r'\n', chr(10)).replace(r'\t', ' ').replace(r'\"', '"')
    return VISIBLE.sub('', raw)


def wrapped_lines(text, ranges, max_width, spacing):
    count = 0
    max_seen = 0
    for line in text.split('\n'):
        used = 0
        count += 1
        for ch in line:
            width = glyph_width(ranges, ord(ch))
            if used and used + width > max_width:
                count += 1
                used = 0
            used += width + spacing
            max_seen = max(max_seen, used - spacing)
    return count, max_seen


def layout(row):
    file, key = row['file'], row['key']
    if file.endswith('/game_select/levels.inc.c') and key.endswith('_desc'):
        return 104, 4, 'small'
    if file.endswith('/studio/songs.inc.c'):
        return 144, 1, 'small'
    if file.endswith('/data_room/reading_material.inc.c') and key in READING_TITLES:
        return 232, 1, 'small'
    return None




def rhythm_tweezers_icon_prompt_errors(fonts):
    """按实际按钮宏展开卷毛提示，并核对单行 240 像素文本框。"""
    source = (ROOT / 'games/rhythm_tweezers/rhythm_tweezers_text.c').read_text(encoding='utf-8')
    match = re.search(r'const char D_0805b590\[\]\s*=\s*(.*?);', source, re.S)
    if not match:
        return ['D_0805b590: initializer not found'], '', 0
    tokens = re.findall(r'"(?:\\.|[^"\\])*"|CHAR_A_BUTTON_UTF8|CHAR_DPAD_UTF8', match.group(1))
    macros = [token for token in tokens if token.startswith('CHAR_')]
    errors = []
    if macros != ['CHAR_A_BUTTON_UTF8', 'CHAR_DPAD_UTF8']:
        errors.append('D_0805b590: A 键或十字键宏缺失、重复或顺序变化')
    pieces = []
    for token in tokens:
        if token == 'CHAR_A_BUTTON_UTF8':
            pieces.append(chr(0xE006))
        elif token == 'CHAR_DPAD_UTF8':
            pieces.append(chr(0xE005))
        else:
            pieces.append(token[1:-1])
    shown = display_text(''.join(pieces))
    if '\n' in shown:
        errors.append('D_0805b590: 单行提示中出现了画面换行')
    widths = [glyph_width(fonts['small'], ord(ch)) for ch in shown]
    missing = [f'U+{ord(ch):04X}' for ch, width in zip(shown, widths)
               if not ch.isspace() and not width]
    if missing:
        errors.append('D_0805b590: 缺少字形 ' + ','.join(missing))
    width = sum(widths) + max(0, len(shown) - 1) * SPACING['small']
    if width > 240:
        errors.append(f'D_0805b590: 图标提示宽度 {width}/240px')
    return errors, shown, width


def diagnosis_page_errors(row, fonts):
    """确认 23 页诊断正文不会因断行改变页码位置。"""
    raw_lines = row['target'].split(r'\n')
    if raw_lines and raw_lines[-1] == '':
        raw_lines.pop()
    problems = []
    if len(raw_lines) != 23 * 9:
        return [f"{row['id']}: expected 207 explicit lines, got {len(raw_lines)}"]
    footers = [display_text(line).strip() for line in raw_lines[8::9]]
    expected = [f'-{page}-' for page in range(1, 24)]
    if footers != expected:
        problems.append(f"{row['id']}: page footers are not on every ninth line")

    # 控制码会在同一行中切换字号；逐段计算，避免用单一字号低估标题宽度。
    font_size = 'small'
    for line_number, raw_line in enumerate(raw_lines, 1):
        width = 0
        last = 0
        has_glyph = False
        for match in CONTROL_TOKEN.finditer(raw_line):
            segment = display_text(raw_line[last:match.start()])
            for ch in segment:
                width += glyph_width(fonts[font_size], ord(ch))
                if has_glyph:
                    width += SPACING[font_size]
                has_glyph = True
            token = match.group(0)
            if token == r'\001s':
                font_size = 'small'
            elif token == r'\001m':
                font_size = 'medium'
            elif token == r'\001l':
                font_size = 'large'
            last = match.end()
        for ch in display_text(raw_line[last:]):
            width += glyph_width(fonts[font_size], ord(ch))
            if has_glyph:
                width += SPACING[font_size]
            has_glyph = True
        if width > 230:
            problems.append(f"{row['id']}: explicit line {line_number} is {width}/230px")
    return problems


def main():
    with TABLE.open(encoding='utf-8', newline='') as stream:
        rows = list(csv.DictReader(stream, delimiter='\t'))
    fonts = {size: font_ranges(size) for size in SPACING}
    definitions = (ROOT / 'data/font_definitions.c').read_text(encoding='utf-8')
    outline = definitions.split('bitmap_font_warioware_outline_cjk_codepoints[] = {', 1)[1].split('};', 1)[0]
    outline_codes = {int(value, 16) for value in re.findall(r'0x([0-9a-fA-F]+)', outline)}
    errors, warnings = [], []
    # Rhythm Tweezers 这句的按钮是源码宏，TSV 看不到；单独按实际 PUA 图标宽度核对。
    icon_errors, icon_text, icon_width = rhythm_tweezers_icon_prompt_errors(fonts)
    errors.extend(icon_errors)
    for row in rows:
        if row['status'] != 'final':
            continue
        target = display_text(row['target'])
        for ch in sorted(set(target)):
            if ord(ch) < 128 or ch.isspace():
                continue
            missing = [size for size, ranges in fonts.items() if not glyph_width(ranges, ord(ch))]
            if missing:
                errors.append(f"{row['id']}: U+{ord(ch):04X} {ch} missing in {','.join(missing)}")
            if 0x4E00 <= ord(ch) <= 0x9FFF and ord(ch) not in outline_codes:
                errors.append(f"{row['id']}: U+{ord(ch):04X} {ch} missing in outline font")
        if row['note']:
            warnings.append(f"{row['id']}: {row['note']}")
        else:
            source_tokens = CONTROL_TOKEN.findall(row['source'])
            if row['id'] == 'games/drum_intro/drum_intro_unused_2_text.c:D_0805d928':
                # 英文「...And」中的 .A 是普通字母，不是显示控制码；只排除这一处误识别。
                source_tokens = [token for token in source_tokens if token != '.A']
            if Counter(source_tokens) != Counter(CONTROL_TOKEN.findall(row['target'])):
                errors.append(f"{row['id']}: control tokens differ")
            if row['key'].startswith(('cafe_dialogue_shouts_praise[', 'cafe_dialogue_shouts_cheer[')):
                # 这十句依靠前置空行把喝彩文字放到气泡中央；只数打印码会漏掉被删掉的 \n。
                if EDGE_CONTROL_TOKEN.findall(row['source']) != EDGE_CONTROL_TOKEN.findall(row['target']):
                    errors.append(f"{row['id']}: cafe shout controls or line breaks differ")
        if row['key'] == 'reading_diagnosis' and not row['note']:
            # 该文章依靠固定九行分页；任何超宽自动折行都会使后续页码错位。
            errors.extend(diagnosis_page_errors(row, fonts))
        bounds = layout(row)
        if bounds and not row['note']:
            width, max_lines, size = bounds
            lines, widest = wrapped_lines(target, fonts[size], width, SPACING[size])
            if lines > max_lines:
                warnings.append(f"{row['id']}: approx {lines}/{max_lines} lines at {width}px; widest line {widest}px")
    report = ROOT / 'build/text_report'
    atomic_text(report / 'validation.txt', '\n'.join(errors) + ('\n' if errors else ''))
    atomic_text(report / 'layout_warnings.txt', '\n'.join(warnings) + ('\n' if warnings else ''))
    # 记录精确宽度，方便在无法截图时仍能证明它不会自动换行或越过文本框。
    atomic_text(report / 'rhythm_tweezers_icon_prompt.txt',
                f'text={icon_text}\nwidth={icon_width}/240px\nstatus={"pass" if not icon_errors else "error"}\n')
    print(f'final={sum(row["status"] == "final" for row in rows)}, errors={len(errors)}, warnings={len(warnings)}')
    if errors:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
