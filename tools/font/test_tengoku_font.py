"""Check exact round trips of existing text_printer glyph binaries.

Example: python tools/font/test_tengoku_font.py
"""

from pathlib import Path
from build_outline_font import THIRD, collect_chars, outline, read_bdf, read_unifont, skeleton
from dump_4bpp import decode_glyph as decode_4bpp_glyph, encode_glyph as encode_4bpp_glyph
from tengoku_font import decode_glyph, encode_glyph


def main() -> None:
    root = Path(__file__).resolve().parents[2] / "bin" / "font"
    count = 0
    for size, height in (("small", 12), ("medium", 12), ("large", 16)):
        for path in (root / size).glob(f"{size}_*.bin"):
            if "spacing" in path.name:
                continue
            data = path.read_bytes()
            if "_pua_" in path.name and len(data) % (height * 2):
                continue  # PUA has a nonstandard length in this branch.
            assert len(data) % (height * 2) == 0, path
            rebuilt = b"".join(encode_glyph(decode_glyph(data[i:i + height * 2], height)) for i in range(0, len(data), height * 2))
            assert rebuilt == data, path
            count += 1
    # A 16-to-9 OR reduction previously filled almost all of 蹑 (U+8E51).
    path = root / 'small/small_cjk_unified_ideographs_4E00_9FFF.bin'
    offset = (0x8E51 - 0x4E00) * 24
    glyph = decode_glyph(path.read_bytes()[offset:offset + 24], 12)
    ink = sum(sum(row[:9]) for row in glyph)
    assert 20 <= ink < 60, f'U+8E51 is unreadably dense: {ink}/81 pixels'
    # 标题字体以前从 Unifont 缩小后再做八方向描边，导致“蹑”几乎变成实心方块。
    # 核对生成结果确实使用了较稀疏的手工骨架，防止以后重建字库时问题复发。
    codepoints = collect_chars('', root.parents[1] / 'build/text_report/bitmap_font_strings.txt')
    index = codepoints.index(0x8E51)
    outline_path = root.parents[1] / 'graphics/font/outline/small/bitmap_font_warioware_outline_small_cjk_used.raw.4bpp'
    outline_glyph = decode_4bpp_glyph(outline_path.read_bytes()[index * 128:(index + 1) * 128])
    body = sum(pixel in (10, 11) for row in outline_glyph for pixel in row)
    occupied = sum(pixel != 0 for row in outline_glyph for pixel in row)
    assert 30 <= body <= 50, f'U+8E51 title body is unreadably dense: {body} pixels'
    assert occupied < 125, f'U+8E51 title outline is unreadably dense: {occupied} pixels'
    source, origin = skeleton(0x8E51, 'small', read_bdf(THIRD / 'fusion-10.bdf'),
                              read_unifont(THIRD / 'unifont.hex'))
    rebuilt = encode_4bpp_glyph(outline(source, 'small', diagonal=False))
    stored = outline_path.read_bytes()[index * 128:(index + 1) * 128]
    assert origin == 'manual' and rebuilt == stored, 'U+8E51 title glyph was not rebuilt from the manual skeleton'
    print(f"{count} font files round-tripped")


if __name__ == "__main__":
    main()
