"""Generate the text_printer CJK glyphs from pinned bitmap fonts.

Example: python tools/font/build_text_font.py --size all --charset build/text_report/charset.txt
"""

import argparse
from collections import Counter
from pathlib import Path
import os

from tengoku_font import encode_glyph

ROOT = Path(__file__).resolve().parents[2]
THIRD = Path(__file__).resolve().parent / "third_party"
START, END = 0x4E00, 0x9FFF


def atomic_write(path, data):
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + ".tmp")
    temp.write_bytes(data)
    os.replace(temp, path)


def read_bdf(path):
    result = {}
    cp = advance = width = height = xoff = yoff = None
    rows = []
    bitmap = False
    for raw in path.open(encoding="ascii"):
        line = raw.strip()
        if line.startswith("STARTCHAR"):
            cp = advance = width = height = xoff = yoff = None
            rows, bitmap = [], False
        elif line.startswith("ENCODING "):
            cp = int(line.split()[1])
        elif line.startswith("DWIDTH "):
            advance = int(line.split()[1])
        elif line.startswith("BBX "):
            width, height, xoff, yoff = map(int, line.split()[1:])
        elif line == "BITMAP":
            bitmap = True
        elif line == "ENDCHAR":
            if cp is not None and cp >= 0 and len(rows) == height:
                result[cp] = (rows, xoff, yoff, advance)
            bitmap = False
        elif bitmap:
            bits = int(line, 16)
            padded = len(line) * 4
            rows.append([(bits >> (padded - x - 1)) & 1 for x in range(width)])
    return result


def read_unifont(path):
    result = {}
    for line in path.open(encoding="ascii"):
        code, data = line.strip().split(":", 1)
        cp = int(code, 16)
        if not START <= cp <= END:
            continue
        width = len(data) // 4
        if width not in (8, 16):
            continue
        digits = width // 4
        result[cp] = [[(int(data[y * digits:(y + 1) * digits], 16) >> (width - x - 1)) & 1 for x in range(width)] for y in range(16)]
    return result


def bdf_canvas(glyph, height, baseline):
    source, xoff, yoff, advance = glyph
    rows = [[0] * 16 for _ in range(height)]
    for y, row in enumerate(source):
        cy = baseline - (yoff + len(source) - 1) + y
        if 0 <= cy < height:
            for x, bit in enumerate(row):
                if bit and 0 <= x + xoff < 16:
                    rows[cy][x + xoff] = 1
    return rows, max(1, min(15, advance - 1))


def shrink(source, target, height, top):
    points = [(x, y) for y, row in enumerate(source) for x, bit in enumerate(row) if bit]
    rows = [[0] * 16 for _ in range(height)]
    if not points:
        return rows
    left, right = min(x for x, _ in points), max(x for x, _ in points) + 1
    upper, lower = min(y for _, y in points), max(y for _, y in points) + 1
    for dy in range(target):
        y0 = upper + dy * (lower - upper) // target
        y1 = upper + ((dy + 1) * (lower - upper) + target - 1) // target
        for dx in range(target):
            x0 = left + dx * (right - left) // target
            x1 = left + ((dx + 1) * (right - left) + target - 1) // target
            rows[top + dy][dx] = int(any(source[y][x] for y in range(y0, min(y1, len(source))) for x in range(x0, min(x1, len(source[0])))))
    return rows


def square(height, top, width):
    rows = [[0] * 16 for _ in range(height)]
    for y in range(top, top + width):
        for x in range(width):
            rows[y][x] = int(y in (top, top + width - 1) or x in (0, width - 1))
    return rows


def required_chars(extra):
    chars = set()
    for hi in range(0xB0, 0xF8):
        for lo in range(0xA1, 0xFF):
            try:
                chars.add(ord(bytes((hi, lo)).decode("gb2312")))
            except UnicodeDecodeError:
                pass
    if extra.exists():
        chars.update(ord(ch) for ch in extra.read_text(encoding="utf-8") if START <= ord(ch) <= END)
    return chars


def build(size, required, fusion, unifont, out, report, keep):
    height = 16 if size == "large" else 12
    target = 15 if size == "large" else (9 if size == "small" else 11)
    top = 2 if size == "small" else 0
    name = f"{size}_cjk_unified_ideographs_4E00_9FFF.bin"
    glyph_path = out / size / name
    spacing_path = out / size / name.replace(f"{size}_", f"{size}_spacing_", 1)
    previous = glyph_path.read_bytes() if keep else b""
    old_widths = spacing_path.read_bytes() if keep else b""
    glyphs, widths = bytearray(), bytearray()
    counts, bbox, width_hist = Counter(), Counter(), Counter()
    review, missing, clipped = [], [], []
    for cp in range(START, END + 1):
        index = cp - START
        if cp not in required:
            glyphs.extend(previous[index * height * 2:(index + 1) * height * 2] if previous else bytes(height * 2))
            widths.append(old_widths[index] if old_widths else 0)
            continue
        if size != "large" and cp in fusion:
            rows, width = bdf_canvas(fusion[cp], height, 9)
            counts["fusion"] += 1
        elif cp in unifont:
            if size == "large":
                rows = shrink(unifont[cp], 15, 16, 0)
                width = 15
                if any(row[15] for row in unifont[cp]):
                    clipped.append(cp)
                counts["unifont"] += 1
            else:
                rows, width = shrink(unifont[cp], target, height, top), target
                review.append(cp)
                counts["unifont_downsample"] += 1
        elif size == "large" and cp in fusion:
            rows, width = bdf_canvas(fusion[cp], 16, 13)
            review.append(cp)
            counts["fusion_fallback"] += 1
        else:
            rows, width = square(height, top, target), target
            missing.append(cp)
            counts["missing_box"] += 1
        glyphs.extend(encode_glyph(rows))
        widths.append(width)
        ys = [y for y, row in enumerate(rows) if any(row)]
        bbox[(min(ys), max(ys)) if ys else None] += 1
        width_hist[width] += 1
    assert len(glyphs) == (END - START + 1) * height * 2
    assert len(widths) == END - START + 1
    assert all(any(glyphs[(cp - START) * height * 2:(cp - START + 1) * height * 2]) for cp in required if START <= cp <= END)
    atomic_write(glyph_path, bytes(glyphs))
    atomic_write(spacing_path, bytes(widths))
    lines = ["Fusion Pixel v2026.09.01; GNU Unifont 17.0.05", f"size={size}; required={len(required)}; sources={dict(counts)}", f"bbox={bbox.most_common(8)}", f"widths={width_hist.most_common(8)}", "manual review=" + " ".join(f"U+{cp:04X}" for cp in review), "missing boxes=" + " ".join(f"U+{cp:04X}" for cp in missing), "column 15 clipped by spacing=" + " ".join(f"U+{cp:04X}" for cp in clipped)]
    atomic_write(report / f"{size}.report.txt", ("\n".join(lines) + "\n").encode("utf-8"))
    print(size, dict(counts), "bbox", bbox.most_common(1), "width", width_hist.most_common(1))


def add_em_dash(size, fusion, out):
    """Fill U+2014, absent from the pre-existing general punctuation font."""
    height = 16 if size == 'large' else 12
    if size == 'large':
        rows = [[int(y == 8 and x < 15) for x in range(16)] for y in range(height)]
        width = 15
    else:
        rows, width = bdf_canvas(fusion[0x2014], height, 9)
    index = 0x2014 - 0x2000
    base = out / size / f'{size}_general_punctuation_2000_206F.bin'
    spacing = out / size / f'{size}_spacing_general_punctuation_2000_206F.bin'
    glyphs = bytearray(base.read_bytes())
    widths = bytearray(spacing.read_bytes())
    glyphs[index * height * 2:(index + 1) * height * 2] = encode_glyph(rows)
    widths[index] = width
    atomic_write(base, glyphs)
    atomic_write(spacing, widths)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--size", choices=("small", "medium", "large", "all"), default="all")
    parser.add_argument("--charset", type=Path, default=ROOT / "build/text_report/charset.txt")
    parser.add_argument("--keep-existing", action="store_true")
    parser.add_argument("--out", type=Path, default=ROOT / "bin/font")
    parser.add_argument("--report", type=Path, default=ROOT / "build/font_report")
    args = parser.parse_args()
    required = required_chars(args.charset)
    print("GB2312 plus translation", len(required))
    unifont = read_unifont(THIRD / "unifont.hex")
    for size in (("small", "medium", "large") if args.size == "all" else (args.size,)):
        fusion = read_bdf(THIRD / f"fusion-{10 if size == 'small' else 12}.bdf")
        build(size, required, fusion, unifont, args.out, args.report, args.keep_existing)
        add_em_dash(size, fusion, args.out)


if __name__ == "__main__":
    main()
