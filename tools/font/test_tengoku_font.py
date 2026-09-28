"""Check exact round trips of existing text_printer glyph binaries.

Example: python tools/font/test_tengoku_font.py
"""

from pathlib import Path
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
    print(f"{count} font files round-tripped")


if __name__ == "__main__":
    main()
