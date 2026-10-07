"""Decode or round-trip WarioWare 16x16 OBJ glyph textures.

汉化改动：把标题的 4bpp 字模解码后再编码，确认转换前后的字节完全一致；
需要时还可输出预览图，方便检查描边、阴影和复杂汉字有没有粘连。

Example: python tools/font/dump_4bpp.py graphics/font/outline/large/bitmap_font_warioware_outline_large_hiragana_3040_309F.raw.4bpp --limit 96
"""

import argparse
from collections import Counter
from pathlib import Path


def decode_glyph(data):
    if len(data) != 128:
        raise ValueError('OBJ glyph is 128 bytes')
    rows = [[0] * 16 for _ in range(16)]
    for ty in range(2):
        for tx in range(2):
            tile = data[(ty * 2 + tx) * 32:(ty * 2 + tx + 1) * 32]
            for y in range(8):
                for x in range(8):
                    value = tile[y * 4 + x // 2]
                    rows[ty * 8 + y][tx * 8 + x] = (value >> (4 * (x % 2))) & 15
    return rows


def encode_glyph(rows):
    if len(rows) != 16 or any(len(row) != 16 for row in rows):
        raise ValueError('OBJ glyph is 16x16 pixels')
    output = bytearray()
    for ty in range(2):
        for tx in range(2):
            for y in range(8):
                for x in range(0, 8, 2):
                    a = rows[ty * 8 + y][tx * 8 + x]
                    b = rows[ty * 8 + y][tx * 8 + x + 1]
                    output.append(a | (b << 4))
    return bytes(output)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('path', type=Path)
    parser.add_argument('--limit', type=int, default=128)
    parser.add_argument('--out', type=Path)
    args = parser.parse_args()
    data = args.path.read_bytes()
    if len(data) % 128:
        raise ValueError('texture length is not a multiple of 128')
    glyphs = [decode_glyph(data[i:i + 128]) for i in range(0, len(data), 128)]
    assert b''.join(encode_glyph(glyph) for glyph in glyphs) == data
    used = Counter(value for glyph in glyphs for row in glyph for value in row)
    print('glyphs', len(glyphs), 'palette indices', dict(used))
    if args.out:
        try:
            from PIL import Image
        except ImportError:
            Image = None
        limit = min(args.limit, len(glyphs))
        columns = 16
        scale = 2
        width = columns * 18
        height = ((limit + columns - 1) // columns) * 18
        canvas = [[0] * width for _ in range(height)]
        for i, glyph in enumerate(glyphs[:limit]):
            left, top = (i % columns) * 18, (i // columns) * 18
            for y in range(16):
                for x in range(16):
                    canvas[top + y][left + x] = glyph[y][x] * 17
        args.out.parent.mkdir(parents=True, exist_ok=True)
        if Image:
            image = Image.new('L', (width, height))
            image.putdata([value for row in canvas for value in row])
            image.save(args.out)
        else:
            args.out.with_suffix('.pgm').write_bytes(f'P5\n{width} {height}\n255\n'.encode() + bytes(value for row in canvas for value in row))


if __name__ == '__main__':
    main()
