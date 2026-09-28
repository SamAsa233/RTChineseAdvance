"""校验已映射译文的字形与控制码，并报告可能超宽的界面文本。

用法：python tools/text/check_text.py
报告：build/text_report/validation.txt 和 layout_warnings.txt。
"""

from collections import Counter
import csv
import json
from pathlib import Path
import re

from pipeline import ARCHIVE, CONTROL_TOKEN, ROOT, TABLE, atomic_text

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


def main():
    with TABLE.open(encoding='utf-8', newline='') as stream:
        rows = list(csv.DictReader(stream, delimiter='\t'))
    fonts = {size: font_ranges(size) for size in SPACING}
    definitions = (ROOT / 'data/font_definitions.c').read_text(encoding='utf-8')
    outline = definitions.split('bitmap_font_warioware_outline_cjk_codepoints[] = {', 1)[1].split('};', 1)[0]
    outline_codes = {int(value, 16) for value in re.findall(r'0x([0-9a-fA-F]+)', outline)}
    errors, warnings = [], []
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
        elif Counter(CONTROL_TOKEN.findall(row['source'])) != Counter(CONTROL_TOKEN.findall(row['target'])):
            errors.append(f"{row['id']}: control tokens differ")
        bounds = layout(row)
        if bounds and not row['note']:
            width, max_lines, size = bounds
            lines, widest = wrapped_lines(target, fonts[size], width, SPACING[size])
            if lines > max_lines:
                warnings.append(f"{row['id']}: approx {lines}/{max_lines} lines at {width}px; widest line {widest}px")
    report = ROOT / 'build/text_report'
    atomic_text(report / 'validation.txt', '\n'.join(errors) + ('\n' if errors else ''))
    atomic_text(report / 'layout_warnings.txt', '\n'.join(warnings) + ('\n' if warnings else ''))
    print(f'final={sum(row["status"] == "final" for row in rows)}, errors={len(errors)}, warnings={len(warnings)}')
    if errors:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
