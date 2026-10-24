"""Build sparse 16x16 outlined OBJ glyphs for every supplied translation.

新要求2：小号采用 Fusion Bold Pixel 12px，大号采用用户提供的方正像素14并自动加粗。
仅做一像素描边与字身内阴影；描边后的可见边界贴住字格左侧和底部。
这样既能让标题显示中文，也不用把两万多个 CJK 汉字全部放进 ROM。

Example: python tools/font/build_outline_font.py --extra 节奏天国
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re

from build_text_font import ROOT, THIRD, read_bdf, read_unifont, shrink_nearest
from PIL import ImageFont
from fontTools.ttLib import TTFont
from dump_4bpp import encode_glyph

BEGIN = '/* BEGIN GENERATED CJK */'
END = '/* END GENERATED CJK */'
ARCHIVE = ROOT / 'text/zh_hans/source/utf8'
# 保存实际标题字符清单，避免换电脑后依赖被忽略的 build 临时文件而生成不同字库。
CHARSET = ROOT / 'tools/font/outline_chars.txt'


def atomic_write(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + '.tmp')
    temp.write_bytes(data)
    os.replace(temp, path)


def needed_codepoint(char):
    # 标题/歌词也使用全角感叹号和波浪号，不能只收录汉字，否则运行时会落到方框。
    cp = ord(char)
    return 0x4E00 <= cp <= 0x9FFF or 0xFF01 <= cp <= 0xFF5E


def collect_chars(extra, char_file=CHARSET):
    chars = {'□'}
    for path in ARCHIVE.rglob('*.json'):
        for row in json.loads(path.read_text(encoding='utf-8')):
            chars.update(ch for ch in row['translation'] if needed_codepoint(ch))
    chars.update(ch for ch in extra if needed_codepoint(ch))
    if char_file.exists():
        chars.update(ch for ch in char_file.read_text(encoding='utf-8') if needed_codepoint(ch))
    return sorted(ord(ch) for ch in chars)


def trim(rows):
    """只去透明留白，不改变字身像素，也不把细笔画合并到同一个像素。"""
    points = {(x, y) for y, row in enumerate(rows) for x, bit in enumerate(row) if bit}
    if not points:
        raise ValueError('源字体返回空白字形')
    left, right = min(x for x, _ in points), max(x for x, _ in points) + 1
    top, bottom = min(y for _, y in points), max(y for _, y in points) + 1
    return [[int(rows[y][x] != 0) for x in range(left, right)] for y in range(top, bottom)]


class FangzhengFont:
    """用原始 TTF 的单色 14px 点阵，码表先确认缺字，避免误把 .notdef 方框当作汉字。"""
    def __init__(self, path):
        metadata = json.loads((ROOT / 'tools/font/font_sources.json').read_text(encoding='utf-8'))['large']
        data = path.read_bytes()
        if hashlib.sha256(data).hexdigest() != metadata['sha256']:
            raise ValueError('方正字体散列不符，请使用本轮用户提供的方正像素14.TTF')
        with TTFont(path, recalcTimestamp=False) as face:
            self.codepoints = set(face.getBestCmap())
        self.font = ImageFont.truetype(str(path), 14)

    def glyph(self, cp):
        mask = self.font.getmask(chr(cp), mode='1')
        return trim([[int(mask[y * mask.size[0] + x] != 0)
                      for x in range(mask.size[0])] for y in range(mask.size[1])])


def bold_horizontal(source):
    """方正字身向右扩一个像素完成自动加粗；高度及原笔画位置均保持。"""
    width = len(source[0])
    return [[int((x < width and row[x]) or (x > 0 and row[x - 1]))
             for x in range(width + 1)] for row in source]


def glyph_body(cp, size, fusion, fangzheng, unifont):
    if size == 'small' and cp in fusion:
        # 12px 字源本身已经是粗体，直接保留全部原始点阵；不再复用旧 9px 手工“蹑”。
        return trim(fusion[cp][0]), 'fusion bold 12px'
    if size == 'large' and cp in fangzheng.codepoints:
        return bold_horizontal(fangzheng.glyph(cp)), 'fangzheng 14px bold'
    if cp in unifont:
        # 仅字源确实缺少的少量字符回退；方正回退留出一列做相同的自动加粗。
        target = 12 if size == 'small' else 13
        rows = trim(shrink_nearest(unifont[cp], target, target, 0))
        return (bold_horizontal(rows) if size == 'large' else rows), 'unifont fallback'
    raise ValueError(f'{size} 缺字 U+{cp:04X} {chr(cp)}')


def outline(source, size=None):
    """描边 bbox 左边为 x=0、底边为 y=15；阴影只能占据原字身点。"""
    source = trim(source)
    height, width = len(source), len(source[0])
    if width > 14 or height > 14:
        raise ValueError(f'字身 {width}x{height} 加描边超过 16x16，拒绝静默裁切')
    left, top = 1, 15 - height
    points = {(left + x, top + y) for y, row in enumerate(source) for x, bit in enumerate(row) if bit}
    border = {(x + dx, y + dy) for x, y in points
              for dy in (-1, 0, 1) for dx in (-1, 0, 1)}
    rows = [[0] * 16 for _ in range(16)]
    for x, y in border:
        rows[y][x] = 8
    for x, y in points:
        # 每条笔画的下沿在字身内部变暗，描边之外不再另加投影像素。
        rows[y][x] = 10 if (x, y + 1) not in points else 11
    return rows


def render_glyph(cp, size, fusion, fangzheng, unifont):
    body, origin = glyph_body(cp, size, fusion, fangzheng, unifont)
    glyph = outline(body)
    # 小号的原版字距为 -1；步进多记一列，抵消它，避免新 12px 字互相压描边。
    width = max(x for row in glyph for x, pixel in enumerate(row) if pixel) + 1
    return glyph, width + (size == 'small'), origin


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
    block = BEGIN + '\n/* 新要求2：大号方正14加粗、小号粗像素12；描边贴左下、阴影仅在字身内，字宽与新字模同步。 */\n' + generated + '\n' + END
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
        section = section.replace('0x25A1, 0x9FFF', '0x25A1, 0xFFEF')
        text = text[:start] + section + text[end:]
        if '/* CJK GENERATED RANGE */' not in section:
            item = (
                '    /* CJK GENERATED RANGE */ {\n'
                f'        bitmap_font_warioware_outline_{size}_cjk_used_raw_4bpp,\n'
                f'        bitmap_font_warioware_outline_{size}_cjk_widths,\n'
                '        0x25A1, 0xFFEF,\n'
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
    parser.add_argument('--chars', type=Path, default=CHARSET)
    parser.add_argument('--extra', default='')
    parser.add_argument('--out', type=Path, default=ROOT / 'graphics/font/outline')
    parser.add_argument('--defs', type=Path, default=ROOT / 'data/font_definitions.c')
    parser.add_argument('--large-font', type=Path, default=THIRD / 'fangzheng-pixel-14.ttf',
                        help='用户提供的方正像素14.TTF；原始字体只在本地保存')
    args = parser.parse_args()
    codepoints = collect_chars(args.extra, args.chars)
    unifont = read_unifont(THIRD / 'unifont.hex', codepoints)
    fangzheng = FangzhengFont(args.large_font)
    fusion = read_bdf(THIRD / 'fusion-bold-12.bdf')
    widths = {}
    reports = []
    glyph_origins = {}
    for size in ('large', 'small'):
        texture_path = args.out / size / f'bitmap_font_warioware_outline_{size}_cjk_used.raw.4bpp'
        preview_path = args.out / size / f'bitmap_font_warioware_outline_{size}_cjk_used.png'
        glyphs, sources, advances = [], {}, []
        glyph_origins[size] = {}
        for cp in codepoints:
            glyph, advance, origin = render_glyph(cp, size, fusion, fangzheng, unifont)
            glyphs.append(glyph)
            advances.append(advance)
            glyph_origins[size][f'U+{cp:04X}'] = origin
            sources[origin] = sources.get(origin, 0) + 1
        widths[size] = advances
        atomic_write(texture_path, b''.join(encode_glyph(glyph) for glyph in glyphs))
        save_preview(preview_path, glyphs)
        reports.append(f'{size}: {sources}; glyphs={len(glyphs)}')
        reports.append(f'{size} fallback: ' + ''.join(chr(cp) for cp in codepoints
                       if glyph_origins[size][f'U+{cp:04X}'] == 'unifont fallback'))
    update_definitions(args.defs, codepoints, widths)
    atomic_write(ROOT / 'build/font_report/outline.report.txt', ('Fusion Bold Pixel 12px v2026.10.16; user Fangzheng 14px synthetic bold\n' + '\n'.join(reports) + '\n').encode('utf-8'))
    atomic_write(ROOT / 'build/font_report/outline.sources.json',
                 (json.dumps(glyph_origins, ensure_ascii=False, indent=2) + '\n').encode('utf-8'))
    print('\n'.join(reports))


if __name__ == '__main__':
    main()
