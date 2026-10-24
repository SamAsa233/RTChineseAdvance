"""Check exact round trips of existing text_printer glyph binaries.

Example: python tools/font/test_tengoku_font.py
"""

from pathlib import Path
from build_outline_font import THIRD, ROOT, FangzhengFont, collect_chars, trim, read_bdf, read_unifont
import re
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
    # 新要求2：检查全部交付字模，不能只确认生成函数的结果。
    codepoints = collect_chars('')
    fusion = read_bdf(THIRD / 'fusion-bold-12.bdf')
    fangzheng = FangzhengFont(THIRD / 'fangzheng-pixel-14.ttf')
    definitions = (ROOT / 'data/font_definitions.c').read_text(encoding='utf-8')
    for size in ('small', 'large'):
        path = ROOT / f'graphics/font/outline/{size}/bitmap_font_warioware_outline_{size}_cjk_used.raw.4bpp'
        raw = path.read_bytes()
        assert len(raw) == len(codepoints) * 128
        width_array = re.search(r'const u8 bitmap_font_warioware_outline_' + size + r'_cjk_widths\[\] = \{(.*?)\};', definitions, re.S)
        widths = [int(v) for v in re.findall(r'\d+', width_array[1])]
        assert len(widths) == len(codepoints)
        for i, cp in enumerate(codepoints):
            glyph = decode_4bpp_glyph(raw[i * 128:(i + 1) * 128])
            occupied = {(x, y) for y, row in enumerate(glyph) for x, pixel in enumerate(row) if pixel}
            assert occupied and min(x for x, _ in occupied) == 0, f'{size} {chr(cp)} 未贴左'
            assert max(y for _, y in occupied) == 15, f'{size} {chr(cp)} 未贴底'
            assert all(pixel in (0, 8, 10, 11) for row in glyph for pixel in row), '外部投影残留'
            body = {(x, y) for y, row in enumerate(glyph) for x, pixel in enumerate(row) if pixel in (10, 11)}
            expected_border = {(x + dx, y + dy) for x, y in body for dx in (-1, 0, 1) for dy in (-1, 0, 1)}
            assert occupied == expected_border, f'{size} {chr(cp)} 描边以外多出像素或被裁切'
            assert all((glyph[y][x] == 10) == ((x, y + 1) not in body) for x, y in body), '阴影不在字身下沿'
            assert widths[i] - (size == 'small') == max(x for x, _ in occupied) + 1, '字距会压住描边'
            assert encode_4bpp_glyph(glyph) == raw[i * 128:(i + 1) * 128]
            # 有字源的字符逐点比对：小号不能缩成旧 9px；大号必须恰好向右加粗一像素。
            source = trim(fusion[cp][0]) if size == 'small' and cp in fusion else (
                fangzheng.glyph(cp) if size == 'large' and cp in fangzheng.codepoints else None)
            if source is not None:
                points = {(x, y) for y, row in enumerate(source) for x, bit in enumerate(row) if bit}
                if size == 'large':
                    points |= {(x + 1, y) for x, y in list(points)}
                expected_body = {(x + 1, y + 15 - len(source)) for x, y in points}
                assert body == expected_body, f'{size} {chr(cp)} 源字形不符或加粗失败'
        for cp in (0xFF01, 0xFF5E, 0x8E51):
            assert cp in codepoints, f'缺少回归字符 {cp:04X}'
    assert 0x8E51 in fusion, '蹑应直接取 12px 粗像素字源'
    print(f"{count} font files round-tripped; 12px/14px font sources, internal shading and bottom-left anchoring verified")


if __name__ == "__main__":
    main()
