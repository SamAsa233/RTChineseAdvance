"""Check exact round trips of existing text_printer glyph binaries.

Example: python tools/font/test_tengoku_font.py
"""

from pathlib import Path
from build_outline_font import THIRD, ROOT, LargeFont, collect_chars, source_usage, SOURCE_TOKEN, ASM_SOURCE_TOKEN, shadow_bands, trim, read_bdf, read_unifont
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
    # 新要求3：从实际源码重新统计，并检查全部交付字模的底部分层阴影。
    assert shadow_bands() == (9, 10, 10), '示例字底色阶变化，需重新核对'
    codepoints = collect_chars('')
    fusion = read_bdf(THIRD / 'fusion-bold-12.bdf')
    large_font = LargeFont(THIRD / 'huakang-fangyuan-w7.ttf')
    assert codepoints == sorted(set(source_usage()) | {0x25A1}), '默认统计混入旧字表'
    assert all(ord(ch) in codepoints for ch in '乓庞捣英'), '拉取后的新增字符未纳入'
    fixture = '/* 忽略 */ const char *a="保留//内容"; // 忽略\nconst char *b="有效";'
    assert [m[0] for m in SOURCE_TOKEN.finditer(fixture) if m[0].startswith('"')] == ['"保留//内容"', '"有效"']
    fixture = '.ascii "真实@内容" @ "这是注释"'
    assert [m[0] for m in ASM_SOURCE_TOKEN.finditer(fixture) if m[0].startswith('"')] == ['"真实@内容"']
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
            assert all(pixel in (0, 8, 9, 10, 11) for row in glyph for pixel in row), '外部投影残留'
            body = {(x, y) for y, row in enumerate(glyph) for x, pixel in enumerate(row) if pixel in (9, 10, 11)}
            expected_border = {(x + dx, y + dy) for x, y in body for dx in (-1, 0, 1) for dy in (-1, 0, 1)}
            assert occupied == expected_border, f'{size} {chr(cp)} 描边以外多出像素或被裁切'
            top = min(y for _, y in body)
            for x, y in body:
                expected = 11 if 15 - top <= 3 and y == top else (9 if y == 14 else 10 if y >= 12 else 11)
                assert glyph[y][x] == expected, '阴影不符合示例字底分层'
            assert widths[i] - (size == 'small') == max(x for x, _ in occupied) + 1, '字距会压住描边'
            assert encode_4bpp_glyph(glyph) == raw[i * 128:(i + 1) * 128]
            # 有字源的字符逐点比对：小号不能缩成旧 9px；大号在允许的字身范围内等比例适配，再恰好向右加粗一像素。
            source = trim(fusion[cp][0]) if size == 'small' and cp in fusion else (
                large_font.glyph(cp) if size == 'large' and cp in large_font.codepoints else None)
            if source is not None:
                if size == 'large':
                    # 独立按最近邻中心坐标计算期望结果，避免把缩放或裁切错误一起带进测试。
                    h, w = len(source), len(source[0])
                    scale = min(1, 13 / w, 14 / h)
                    tw, th = max(1, round(w * scale)), max(1, round(h * scale))
                    source = trim([[source[min(h - 1, (2 * y + 1) * h // (2 * th))][min(w - 1, (2 * x + 1) * w // (2 * tw))]
                                    for x in range(tw)] for y in range(th)])
                points = {(x, y) for y, row in enumerate(source) for x, bit in enumerate(row) if bit}
                if size == 'large':
                    points |= {(x + 1, y) for x, y in list(points)}
                expected_body = {(x + 1, y + 15 - len(source)) for x, y in points}
                assert body == expected_body, f'{size} {chr(cp)} 源字形不符或加粗失败'
        for cp in (0xFF01, 0xFF5E, 0x8E51):
            assert cp in codepoints, f'缺少回归字符 {cp:04X}'
    assert 0x8E51 in fusion, '蹑应直接取 12px 粗像素字源'
    print(f"{count} font files round-tripped; fresh source charset, Huakang16 fit, example shading and bottom-left anchoring verified")


if __name__ == "__main__":
    main()
