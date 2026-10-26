"""Build sparse 16x16 outlined OBJ glyphs for every supplied translation.

新要求3：按当前源码重算字符；小号粗像素12，大号华康方圆W7按16px渲染。
用户选择保留16×16字格，大号字身先等比例适配再加粗、描边；字底阴影按示例分层。
这样既能让标题显示中文，也不用把两万多个 CJK 汉字全部放进 ROM。

Example: python tools/font/build_outline_font.py --extra 节奏天国
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
from collections import Counter
from functools import lru_cache

from build_text_font import ROOT, THIRD, read_bdf, read_unifont, shrink_nearest
from PIL import ImageFont
from fontTools.ttLib import TTFont
from dump_4bpp import encode_glyph

BEGIN = '/* BEGIN GENERATED CJK */'
END = '/* END GENERATED CJK */'
# 新要求3：每次从当前源码字面量重算，不再合并旧译文归档或上次字表。
CHARSET = ROOT / 'tools/font/outline_chars.txt'
SOURCE_ROOTS = {'asm', 'audio', 'data', 'games', 'graphics', 'include', 'src'}
SOURCE_SUFFIXES = {'.c', '.h', '.s', '.bs'}
# 先匹配字符串和字符常量，再跳过注释，避免把字符串里的 // 当成注释。
SOURCE_TOKEN = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\r\n]*', re.S)
# ARM 汇编与节奏脚本另有 @ 行注释，字符串内的 @ 仍由前面的字符串分支保留。
ASM_SOURCE_TOKEN = re.compile(SOURCE_TOKEN.pattern + r'|@[^\r\n]*', re.S)


def atomic_write(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + '.tmp')
    temp.write_bytes(data)
    os.replace(temp, path)


def needed_codepoint(char):
    cp = ord(char)
    return (0x3400 <= cp <= 0x9FFF or 0xF900 <= cp <= 0xFAFF
            or 0xFF01 <= cp <= 0xFF5E)


def source_usage():
    """覆盖所有编译分支的实际源码字符串；注释和旧归档不参与所需字符统计。"""
    names = subprocess.check_output(['git', '-C', str(ROOT), 'ls-files', '-co', '--exclude-standard', '-z']).decode('utf-8').split('\0')
    usage = {}
    for name in names:
        path = Path(name)
        if not name or path.parts[0] not in SOURCE_ROOTS or path.suffix not in SOURCE_SUFFIXES:
            continue
        text = (ROOT / path).read_text(encoding='utf-8-sig')
        tokens = ASM_SOURCE_TOKEN if path.suffix in {'.s', '.bs'} else SOURCE_TOKEN
        for match in tokens.finditer(text):
            literal = match.group()
            if not literal.startswith('"'):
                continue
            literal = re.sub(r'(?<!\\)\\(?:u([0-9a-fA-F]{4})|U([0-9a-fA-F]{8}))',
                             lambda m: chr(int(m[1] or m[2], 16)), literal)
            for ch in literal:
                if needed_codepoint(ch):
                    usage.setdefault(ord(ch), set()).add(name)
    return {cp: sorted(files) for cp, files in sorted(usage.items())}


def collect_chars(extra='', char_file=None):
    chars = set(source_usage()) | {0x25A1}
    chars.update(ord(ch) for ch in extra if needed_codepoint(ch))
    # --chars 仅用于显式追加场景外测试字符；默认绝不读取上一次生成的字表。
    if char_file is not None:
        chars.update(ord(ch) for ch in char_file.read_text(encoding='utf-8') if needed_codepoint(ch))
    return sorted(chars)


def trim(rows):
    """只去透明留白，不改变字身像素，也不把细笔画合并到同一个像素。"""
    points = {(x, y) for y, row in enumerate(rows) for x, bit in enumerate(row) if bit}
    if not points:
        raise ValueError('源字体返回空白字形')
    left, right = min(x for x, _ in points), max(x for x, _ in points) + 1
    top, bottom = min(y for _, y in points), max(y for _, y in points) + 1
    return [[int(rows[y][x] != 0) for x in range(left, right)] for y in range(top, bottom)]


class LargeFont:
    """使用本轮用户 TTF 的单色 16px 点阵；先查码表，再按确认的字格上限适配。"""
    def __init__(self, path):
        metadata = json.loads((ROOT / 'tools/font/font_sources.json').read_text(encoding='utf-8'))['large']
        data = path.read_bytes()
        if hashlib.sha256(data).hexdigest() != metadata['sha256']:
            raise ValueError(f"大号字体散列不符，请使用 {metadata['original_filename']}")
        with TTFont(path, recalcTimestamp=False) as face:
            self.codepoints = set(face.getBestCmap())
        self.font = ImageFont.truetype(str(path), metadata['size'])

    def glyph(self, cp):
        mask = self.font.getmask(chr(cp), mode='1')
        return trim([[int(mask[y * mask.size[0] + x] != 0)
                      for x in range(mask.size[0])] for y in range(mask.size[1])])


def fit_body(source, max_width=13, max_height=14):
    """用户已确认：维持16×16字格时，可先等比例缩小大号字身，再留一列加粗。"""
    source = trim(source)
    width, height = len(source[0]), len(source)
    scale = min(1, max_width / width, max_height / height)
    if scale == 1:
        return source
    target = (max(1, round(width * scale)), max(1, round(height * scale)))
    # 用整数中心坐标做最近邻采样，避免浮点边界在不同图像库版本里偏移一像素。
    return trim([[source[min(height - 1, (2 * y + 1) * height // (2 * target[1]))]
                        [min(width - 1, (2 * x + 1) * width // (2 * target[0]))]
                  for x in range(target[0])] for y in range(target[1])])



def bold_horizontal(source):
    """适配后的大号字身向右扩一个像素加粗，完整笔画与描边都留在字格内。"""
    width = len(source[0])
    return [[int((x < width and row[x]) or (x > 0 and row[x - 1]))
             for x in range(width + 1)] for row in source]


def glyph_body(cp, size, fusion, large_font, unifont):
    if size == 'small' and cp in fusion:
        # 12px 字源本身已经是粗体，直接保留全部原始点阵；不再复用旧 9px 手工“蹑”。
        return trim(fusion[cp][0]), 'fusion bold 12px'
    if size == 'large' and cp in large_font.codepoints:
        source = large_font.glyph(cp)
        fitted = fit_body(source)
        origin = 'huakang 16px fit bold' if fitted != source else 'huakang 16px bold'
        return bold_horizontal(fitted), origin
    if cp in unifont:
        # 仅主字源确实缺少的字符回退；大号仍留出一列做同样的自动加粗。
        target = 12 if size == 'small' else 13
        rows = trim(shrink_nearest(unifont[cp], target, target, 0))
        return (bold_horizontal(rows) if size == 'large' else rows), 'unifont fallback'
    raise ValueError(f'{size} 缺字 U+{cp:04X} {chr(cp)}')


@lru_cache(maxsize=1)
def shadow_bands():
    """核对用户示例，并提取最下面三行字身色的主色阶（排除透明和描边）。"""
    from PIL import Image
    info = json.loads((ROOT / 'tools/font/font_sources.json').read_text(encoding='utf-8'))['shading']
    path = ROOT / 'tools/font' / info['sample']
    if hashlib.sha256(path.read_bytes()).hexdigest() != info['sha256']:
        raise ValueError('阴影示例文件散列不符')
    image = Image.open(path).convert('L')
    result = []
    for depth in range(3):
        y = image.height - 2 - depth
        colors = Counter(image.getpixel((x, y)) // 17 for x in range(image.width)
                         if image.getpixel((x, y)) // 17 in (9, 10, 11))
        result.append(colors.most_common(1)[0][0])
    return tuple(result)


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
    bands = shadow_bands()
    for x, y in points:
        # 示例的主要色阶集中在字底三行，不再让每一条横画都出现暗边。
        # 只有一到三行的短标点，最上行仍保留亮色，避免整个标点变暗。
        depth = 14 - y
        rows[y][x] = 11 if height <= 3 and y == top else (bands[depth] if depth < len(bands) else 11)
    return rows


def render_glyph(cp, size, fusion, large_font, unifont):
    body, origin = glyph_body(cp, size, fusion, large_font, unifont)
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
    block = BEGIN + '\n/* 新要求3：字符由当前源码重算；大号华康W7(16px适配字格)，小号粗像素12，阴影按示例集中在字底。 */\n' + generated + '\n' + END
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
    parser.add_argument('--chars', type=Path, help='额外字符文件；默认按当前源码重新统计')
    parser.add_argument('--extra', default='')
    parser.add_argument('--out', type=Path, default=ROOT / 'graphics/font/outline')
    parser.add_argument('--defs', type=Path, default=ROOT / 'data/font_definitions.c')
    parser.add_argument('--large-font', type=Path, default=THIRD / 'huakang-fangyuan-w7.ttf',
                        help='用户提供的华康方圆体w7.ttf；原始字体只在本地保存')
    args = parser.parse_args()
    codepoints = collect_chars(args.extra, args.chars)
    unifont = read_unifont(THIRD / 'unifont.hex', codepoints)
    large_font = LargeFont(args.large_font)
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
            glyph, advance, origin = render_glyph(cp, size, fusion, large_font, unifont)
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
    # 字表只作为本次统计结果输出，下一次生成仍从源码重新扫描。
    atomic_write(CHARSET, ('\n'.join(''.join(chr(cp) for cp in codepoints[i:i + 64])
                                         for i in range(0, len(codepoints), 64)) + '\n').encode('utf-8'))
    usage = {f'U+{cp:04X}': {'char': chr(cp), 'files': files} for cp, files in source_usage().items()}
    atomic_write(ROOT / 'build/font_report/outline.usage.json',
                 (json.dumps(usage, ensure_ascii=False, indent=2) + '\n').encode('utf-8'))
    atomic_write(ROOT / 'build/font_report/outline.report.txt', ('Fusion Bold Pixel 12px v2026.10.16; user Huakang FangYuan W7 16px fit + synthetic bold\n' + '\n'.join(reports) + '\n').encode('utf-8'))
    atomic_write(ROOT / 'build/font_report/outline.sources.json',
                 (json.dumps(glyph_origins, ensure_ascii=False, indent=2) + '\n').encode('utf-8'))
    print('\n'.join(reports))


if __name__ == '__main__':
    main()
