"""Encode and decode text_printer 16-column 1bpp glyphs.

汉化改动：按原游戏 text_printer 的位排列读写正文点阵，并用往返编码检查生成文件。
如果读出后再写回的字节不同，说明字模排列有误，ROM 中就可能出现错位或乱码。

Example: python tools/font/tengoku_font.py bin/font/small/small_ascii_0000_007F.bin 24
"""

from pathlib import Path
import argparse


def decode_glyph(data: bytes, height: int) -> list[list[int]]:
    if len(data) != height * 2 or height % 4:
        raise ValueError("glyph must have 16 columns and a multiple of four rows")
    pixels = [[0] * 16 for _ in range(height)]
    for group in range(height // 4):
        bits = int.from_bytes(data[group * 8:group * 8 + 8], "little")
        for x in range(16):
            for y in range(4):
                pixels[group * 4 + y][x] = (bits >> (x * 4 + y)) & 1
    return pixels


def encode_glyph(pixels: list[list[int]]) -> bytes:
    height = len(pixels)
    if height % 4 or any(len(row) != 16 for row in pixels):
        raise ValueError("glyph must have 16 columns and a multiple of four rows")
    result = bytearray()
    for group in range(height // 4):
        bits = 0
        for x in range(16):
            for y in range(4):
                bits |= bool(pixels[group * 4 + y][x]) << (x * 4 + y)
        result.extend(bits.to_bytes(8, "little"))
    return bytes(result)


def has_glyph(root: Path, size: str, codepoint: int) -> bool:
    height = 16 if size == "large" else 12
    for spacing in (False, True):
        prefix = f"{size}_{'spacing_' if spacing else ''}"
        for path in (root / size).glob(prefix + "*.bin"):
            parts = path.stem.split("_")
            try:
                start, end = int(parts[-2], 16), int(parts[-1], 16)
            except ValueError:
                continue
            if start <= codepoint <= end:
                offset = codepoint - start
                if spacing:
                    return path.read_bytes()[offset] > 0
                data = path.read_bytes()[offset * height * 2:(offset + 1) * height * 2]
                return any(data)
    return False


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("path", type=Path)
    parser.add_argument("glyph_bytes", type=int, choices=(24, 32))
    args = parser.parse_args()
    data = args.path.read_bytes()
    if len(data) % args.glyph_bytes:
        parser.error("file size is not divisible by glyph size")
    for index in range(len(data) // args.glyph_bytes):
        glyph = data[index * args.glyph_bytes:(index + 1) * args.glyph_bytes]
        if encode_glyph(decode_glyph(glyph, args.glyph_bytes // 2)) != glyph:
            raise ValueError(f"round trip failed at {index}")
    print(f"{len(data) // args.glyph_bytes} glyphs round-tripped")


if __name__ == "__main__":
    main()
