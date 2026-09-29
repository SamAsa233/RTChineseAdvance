"""Build sparse 16x16 outlined OBJ glyphs for every supplied translation.

汉化改动：只为译文实际出现的汉字生成 16x16 标题字模，并补上原版标题使用的描边和阴影。
这样既能让标题显示中文，也不用把两万多个 CJK 汉字全部放进 ROM。

Example: python tools/font/build_outline_font.py --extra 节奏天国
"""

import argparse
import json
import os
from pathlib import Path
import re

from build_text_font import ROOT, THIRD, bdf_canvas, read_bdf, read_unifont, shrink
from dump_4bpp import encode_glyph

BEGIN = '/* BEGIN GENERATED CJK */'
END = '/* END GENERATED CJK */'
ARCHIVE = ROOT / 'text/zh_hans/source/utf8'


def atomic_write(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + '.tmp')
    temp.write_bytes(data)
    os.replace(temp, path)


def collect_chars(extra, char_file):
    chars = {'□'}
    for path in ARCHIVE.rglob('*.json'):
        for row in json.loads(path.read_text(encoding='utf-8')):
            chars.update(ch for ch in row['translation'] if 0x4E00 <= ord(ch) <= 0x9FFF)
    chars.update(ch for ch in extra if 0x4E00 <= ord(ch) <= 0x9FFF)
    if char_file.exists():
        chars.update(ch for ch in char_file.read_text(encoding='utf-8') if 0x4E00 <= ord(ch) <= 0x9FFF)
    return sorted(ord(ch) for ch in chars)


def skeleton(cp, size, fusion, unifont):
    target = 11 if size == 'large' else 9
    if cp == 0x25A1:
        rows = [[int(y in (0, target - 1) or x in (0, target - 1)) for x in range(target)] for y in range(target)]
        return rows, 'square'
    if cp in fusion:
        canvas, _ = bdf_canvas(fusion[cp], 16 if size == 'large' else 12, 9)
        top = 0 if size == 'large' else 2
        return [row[:target] for row in canvas[top:top + target]], 'fusion'
    if cp in unifont:
        canvas = shrink(unifont[cp], target, 16, 0)
        return [row[:target] for row in canvas[:target]], 'unifont downsample'
    rows = [[int(y in (0, target - 1) or x in (0, target - 1)) for x in range(target)] for y in range(target)]
    return rows, 'missing box'


def outline(source, size):
    rows = [[0] * 16 for _ in range(16)]
    left = 2 if size == 'large' else 3
    top = 3 if size == 'large' else 5
    points = {(left + x, top + y) for y, row in enumerate(source) for x, bit in enumerate(row) if bit}
    border = {(x + dx, y + dy) for x, y in points for dy in (-1, 0, 1) for dx in (-1, 0, 1) if 0 <= x + dx < 16 and 0 <= y + dy < 16}
    for x, y in border:
        if y + 1 < 16 and (x, y + 1) not in border:
            rows[y + 1][x] = 9  # lower cast shadow
    for x, y in border:
        rows[y][x] = 8  # dark outline
    for x, y in points:
        rows[y][x] = 10 if y >= top + len(source) - 2 else 11  # light body, darker baseline
    return rows


def manual_glyphs(path, codepoints):
    manual_file = ROOT / 'tools/font/outline_manual.txt'
    if not path.exists() or not manual_file.exists():
        return {}
    try:
        from PIL import Image
    except ImportError:
        return {}
    selected = {int(line.strip().removeprefix('U+'), 16) for line in manual_file.read_text(encoding='utf-8').splitlines() if line.strip() and not line.startswith('#')}
    image = Image.open(path).convert('L')
    result = {}
    for i, cp in enumerate(codepoints):
        if cp in selected:
            x0, y0 = (i % 32) * 16, (i // 32) * 16
            result[cp] = [[round(image.getpixel((x0 + x, y0 + y)) / 17) for x in range(16)] for y in range(16)]
    return result


def save_preview(path, glyphs):
    try:
        from PIL import Image
    except ImportError:
        return
    columns = 32
    image = Image.new('L', (columns * 16, ((len(glyphs) + columns - 1) // columns) * 16))
    for i, glyph in enumerate(glyphs):
        x0, y0 = (i % columns) * 16, (i // columns) * 16
        for y in range(16):
            for x in range(16):
                image.putpixel((x0 + x, y0 + y), glyph[y][x] * 17)
    path.parent.mkdir(parents=True, exist_ok=True)
    image.save(path)


def c_array(name, data, kind, per_line):
    lines = [f'const {kind} {name}[] = {{']
    for i in range(0, len(data), per_line):
        values = data[i:i + per_line]
        lines.append('    ' + ', '.join(f'0x{value:04X}' if kind == 'u16' else str(value) for value in values) + (',' if i + per_line < len(data) else ''))
    lines.append('};')
    return '\n'.join(lines)


def update_definitions(path, codepoints, widths):
    raw = path.read_bytes()
    newline = '\r\n' if b'\r\n' in raw else '\n'
    text = raw.decode('utf-8').replace('\r\n', '\n')
    generated = '\n\n'.join((
        c_array('bitmap_font_warioware_outline_cjk_codepoints', codepoints, 'u16', 12),
        c_array('bitmap_font_warioware_outline_large_cjk_widths', widths['large'], 'u8', 24),
        c_array('bitmap_font_warioware_outline_small_cjk_widths', widths['small'], 'u8', 24),
    ))
    block = BEGIN + '\n' + generated + '\n' + END
    if BEGIN in text:
        start = text.index(BEGIN)
        end = text.index(END, start) + len(END)
        text = text[:start] + block + text[end:]
    else:
        marker = '// WarioWare Outline Font'
        if marker not in text:
            raise ValueError('outline range marker missing')
        text = text.replace(marker, block + '\n\n' + marker, 1)
    for name, size in (
        ('bitmap_font_warioware_outline_large_wide_ranges', 'large'),
        ('bitmap_font_warioware_outline_small_ranges', 'small'),
        ('bitmap_font_warioware_outline_large_narrow_ranges', 'large'),
    ):
        start = text.index('struct BitmapFontRange ' + name + '[]')
        end = text.index('\n};', start)
        section = text[start:end]
        if '/* CJK GENERATED RANGE */' not in section:
            item = (
                '    /* CJK GENERATED RANGE */ {\n'
                f'        bitmap_font_warioware_outline_{size}_cjk_used_raw_4bpp,\n'
                f'        bitmap_font_warioware_outline_{size}_cjk_widths,\n'
                '        0x25A1, 0x9FFF,\n'
                '        bitmap_font_warioware_outline_cjk_codepoints,\n'
                '        ARRAY_COUNT(bitmap_font_warioware_outline_cjk_codepoints)\n'
                '    },\n'
            )
            section = section.replace('    END_OF_RANGE', item + '    END_OF_RANGE', 1)
            text = text[:start] + section + text[end:]
    text = re.sub(r'(?<!BITMAP_FONT_)END_OF_RANGE', 'BITMAP_FONT_END_OF_RANGE', text)
    atomic_write(path, text.replace('\n', newline).encode('utf-8'))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--chars', type=Path, default=ROOT / 'build/text_report/bitmap_font_strings.txt')
    parser.add_argument('--extra', default='')
    parser.add_argument('--out', type=Path, default=ROOT / 'graphics/font/outline')
    parser.add_argument('--defs', type=Path, default=ROOT / 'data/font_definitions.c')
    args = parser.parse_args()
    codepoints = collect_chars(args.extra, args.chars)
    unifont = read_unifont(THIRD / 'unifont.hex')
    widths = {}
    reports = []
    for size in ('large', 'small'):
        fusion = read_bdf(THIRD / f"fusion-{12 if size == 'large' else 10}.bdf")
        texture_path = args.out / size / f'bitmap_font_warioware_outline_{size}_cjk_used.raw.4bpp'
        preview_path = args.out / size / f'bitmap_font_warioware_outline_{size}_cjk_used.png'
        manual = manual_glyphs(preview_path, codepoints)
        glyphs, sources = [], {}
        for cp in codepoints:
            source, origin = skeleton(cp, size, fusion, unifont)
            glyphs.append(manual.get(cp, outline(source, size)))
            sources[origin] = sources.get(origin, 0) + 1
        widths[size] = [14 if size == 'large' else 12 for _ in codepoints]
        atomic_write(texture_path, b''.join(encode_glyph(glyph) for glyph in glyphs))
        save_preview(preview_path, glyphs)
        reports.append(f'{size}: {sources}; glyphs={len(glyphs)}')
    update_definitions(args.defs, codepoints, widths)
    atomic_write(ROOT / 'build/font_report/outline.report.txt', ('Fusion Pixel v2026.09.01; Unifont 17.0.05\n' + '\n'.join(reports) + '\n').encode('utf-8'))
    print('\n'.join(reports))


if __name__ == '__main__':
    main()
