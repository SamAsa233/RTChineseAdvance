#!/usr/bin/env python3
"""
Generate GB2312 text data tables for the RTCN Rhythm Heaven Advance TextPrinter.

The original engine decodes Shift-JIS (see text_printer_get_glyph_id in
src/text_printer.c). For the Chinese localization we switch the TextPrinter to
decode GB2312. This tool emits the C tables that live in
data/text_printer_data.c:

  D_08938194  ASCII (0x20-0x7E) -> GB2312 fullwidth code pairs
  D_08938140  GB2312 lead byte (0xA1-0xF7) -> glyph base IDs
  D_089380d0  line cut-off ellipsis
  D_089380d4  fullwidth open brackets
  D_089380e8  fullwidth ending punctuation
  D_089380e4 / D_08938138  halfwidth brackets/punctuation (unchanged ASCII)

Run:  python3 tools/gen_text_gb2312_data.py
"""

# ---------------------------------------------------------------------------
# GB2312-80 zone structure
# ---------------------------------------------------------------------------
# Lead byte 0xA1-0xF7 = zones 1-87.  Each zone holds 94 glyphs (trail 0xA1-0xFE).
# Zones: 01-09 symbols/Latin/Kana/Greek/Cyrillic/pinyin/box-drawing,
#        10-15 unassigned (empty),
#        16-87 Hanzi (GB2312 一级 16-55, 二级 56-87).

ZONE_LEAD_MIN = 0xA1
ZONE_LEAD_MAX = 0xF7
ZONE_TRAIL_MIN = 0xA1
ZONE_TRAIL_MAX = 0xFE
ZONE_COUNT = 94  # per-zone glyph count


def gb2312(lead, trail):
    return (lead << 8) | trail


def glyph_index(lead, trail):
    """Linear full-set glyph index for a GB2312 code."""
    return (lead - ZONE_LEAD_MIN) * ZONE_COUNT + (trail - ZONE_TRAIL_MIN)


# ---------------------------------------------------------------------------
# Fullwidth ASCII -> GB2312 (for D_08938194)
# ---------------------------------------------------------------------------
# Original engine renders ASCII via a fullwidth lookup table (same behaviour we
# keep for the Chinese port): 'A' renders as fullwidth 'Ａ', space as U+3000.
#
# GB2312 fullwidth layout (verified against GB2312-80):
#   0x20 (space)      -> 0xA1A1  (U+3000 IDEOGRAPHIC SPACE)
#   0x21-0x3E (!- >)  -> 0xA1C1 + (c-0x21)   (U+FF01 .. U+FF1E)
#   0x3F-0x5E (?-^)   -> 0xA1DF + (c-0x3F)   (U+FF1F .. U+FF3E)
#   0x5F-0x7E (_-~)   -> 0xA2A1 + (c-0x5F)   (U+FF3F .. U+FF5E)
#
# U+FF5E (fullwidth tilde '~') is NOT in GB2312-80; GBK places it at 0xA2C4.
# We fall back to 0xA1AA (U+2015 HORIZONTAL BAR) so '~' never renders as a
# dropped glyph. Adjust below if you want a different fallback.

ASCII_FULLWIDTH_FALLBACK = gb2312(0xA1, 0xAA)  # U+2015 '―'


def ascii_to_fullwidth(code):
    if code == 0x20:
        return gb2312(0xA1, 0xA1)          # U+3000
    if 0x21 <= code <= 0x3E:
        return gb2312(0xA1, 0xC1 + (code - 0x21))
    if 0x3F <= code <= 0x5E:
        return gb2312(0xA1, 0xDF + (code - 0x3F))
    if 0x5F <= code <= 0x7E:
        gb = gb2312(0xA2, 0xA1 + (code - 0x5F))
        if code == 0x7E:                   # '~' -> U+FF5E not in GB2312-80
            return ASCII_FULLWIDTH_FALLBACK
        return gb
    raise ValueError("not ASCII 0x20-0x7E")


# ---------------------------------------------------------------------------
# Chinese punctuation (GB2312, for D_089380d0/d4/e8)
# ---------------------------------------------------------------------------
ELLIPSIS = gb2312(0xA1, 0xAC)  # U+2026 '…'

# Fullwidth open brackets (lead byte pairs, terminated by NUL)
FULLWIDTH_OPEN_BRACKETS = [
    gb2312(0xA1, 0xC8),  # （ U+FF08
    gb2312(0xA1, 0xB1),  # 〔 U+3014
    gb2312(0xA1, 0xB3),  # 〈 U+3008
    gb2312(0xA1, 0xB5),  # 《 U+300A
    gb2312(0xA1, 0xB7),  # 「 U+300C
    gb2312(0xA1, 0xB9),  # 『 U+300E
    gb2312(0xA1, 0xBB),  # 【 U+3010
    gb2312(0xA1, 0xFB),  # ［ U+FF3B
]

# Fullwidth ending punctuation (lead byte pairs, terminated by NUL)
FULLWIDTH_END_PUNCTUATION = [
    gb2312(0xA1, 0xA2),  # 、 U+3001
    gb2312(0xA1, 0xA3),  # 。 U+3002
    gb2312(0xA1, 0xCC),  # ， U+FF0C
    gb2312(0xA1, 0xC9),  # ） U+FF09
    gb2312(0xA1, 0xB2),  # 〕 U+3015
    gb2312(0xA1, 0xB4),  # 〉 U+3009
    gb2312(0xA1, 0xB6),  # 》 U+300B
    gb2312(0xA1, 0xB8),  # 」 U+300D
    gb2312(0xA1, 0xBA),  # 』 U+300F
    gb2312(0xA1, 0xBC),  # 】 U+3011
    gb2312(0xA1, 0xFD),  # ］ U+FF3D
    gb2312(0xA1, 0xAC),  # … U+2026
    gb2312(0xA1, 0xDF),  # ？ U+FF1F
    gb2312(0xA1, 0xDB),  # ； U+FF1B
    gb2312(0xA1, 0xDA),  # ： U+FF1A
    gb2312(0xA1, 0xAD),  # ' U+2018
    gb2312(0xA1, 0xAE),  # ' U+2019
    gb2312(0xA1, 0xAF),  # " U+201C
    gb2312(0xA1, 0xB0),  # " U+201D
    gb2312(0xA1, 0xC1),  # ！ U+FF01
    gb2312(0xA1, 0xCE),  # ． U+FF0E
]

# Halfwidth versions (unchanged from the original game)
HALFWIDTH_OPEN_BRACKETS = "([{"
HALFWIDTH_END_PUNCTUATION = "!?,.)]}"


# ---------------------------------------------------------------------------
# Zone base table (D_08938140)
# ---------------------------------------------------------------------------
# glyphID = base[lead-0xA1] + (trail-0xA1); base = -1 for zones with no glyphs.
#
# Default: FULL-SET linear layout so a GB2312-ordered glyph bin works out of
# the box. Once the Chinese translation is final, regenerate this table from
# the actual character set (see subset_zone_bases below) to only pack the
# characters the game really uses.
def full_set_zone_bases():
    return [(i * ZONE_COUNT) for i in range(ZONE_LEAD_MAX - ZONE_LEAD_MIN + 1)]


def subset_zone_bases(used_gb2312_codes):
    """Pack only used GB2312 codes into compact contiguous glyph IDs.

    used_gb2312_codes: iterable of (lead, trail) or int codes actually used by
    the translation.  Zones with nothing used get base -1.
    """
    used = {}
    for code in used_gb2312_codes:
        if isinstance(code, int):
            lead, trail = code >> 8, code & 0xFF
        else:
            lead, trail = code
        used.setdefault(lead, set()).add(trail)

    bases = [-1] * (ZONE_LEAD_MAX - ZONE_LEAD_MIN + 1)
    cursor = 0
    for lead in range(ZONE_LEAD_MIN, ZONE_LEAD_MAX + 1):
        trails = used.get(lead)
        if not trails:
            continue
        bases[lead - ZONE_LEAD_MIN] = cursor
        # Only advance by the number of glyphs in this zone (the zone keeps a
        # dense run from its lowest used trail onward; unused trails above are
        # still reserved so glyphID math stays 'base + (trail-0xA1)').
        cursor += max(trails) - ZONE_TRAIL_MIN + 1
    return bases


# ---------------------------------------------------------------------------
# Emit C
# ---------------------------------------------------------------------------
def fmt_bytes16(values, per_row=12):
    out = []
    for i in range(0, len(values), per_row):
        row = ", ".join("0x%04x" % v for v in values[i:i + per_row])
        out.append("    " + row + ",")
    return "\n".join(out)


def fmt_pairs(codes):
    r"""Emit a NUL-terminated char[] as \xNN\xNN escape pairs."""
    parts = []
    for code in codes:
        parts.append("\\x%02X\\x%02X" % (code >> 8, code & 0xFF))
    return '"' + "".join(parts) + '"'


def build_data_section():
    """Return the new data block for data/text_printer_data.c."""
    ascii_table = [ascii_to_fullwidth(c) for c in range(0x20, 0x7F)]
    bases = full_set_zone_bases()

    lines = []
    lines.append("// [D_089380d0] Line Cut-Off Ellipsis (GB2312)")
    lines.append('char D_089380d0[] = %s;' % fmt_pairs([ELLIPSIS]))
    lines.append("")
    lines.append("// [D_089380d4] Full-Width Open Brackets (GB2312)")
    lines.append('char D_089380d4[] = %s;' % fmt_pairs(FULLWIDTH_OPEN_BRACKETS))
    lines.append("")
    lines.append("// [D_089380e4] Half-Width Open Brackets")
    lines.append('char D_089380e4[] = "%s";' % HALFWIDTH_OPEN_BRACKETS)
    lines.append("")
    lines.append("// [D_089380e8] Full-Width Ending Punctuation (GB2312)")
    lines.append('char D_089380e8[] = %s;' % fmt_pairs(FULLWIDTH_END_PUNCTUATION))
    lines.append("")
    lines.append("// [D_08938138] Half-Width Ending Punctuation")
    lines.append('char D_08938138[] = "%s";' % HALFWIDTH_END_PUNCTUATION)
    lines.append("")
    lines.append("// [D_08938140] GB2312 Lead-Byte (0xA1-0xF7) -> Glyph Base IDs")
    lines.append("// glyphID = base + (trail - 0xA1);  -1 = zone has no glyphs")
    lines.append("s16 D_08938140[] = {")
    lines.append(fmt_bytes16(bases, per_row=12))
    lines.append("};")
    lines.append("")
    lines.append("// [D_08938194] ASCII (0x20-0x7E) -> GB2312 Fullwidth Pairs")
    lines.append("// 95 pairs, index = code - 0x20")
    lines.append('char D_08938194[] =')
    lines.append('    ' + fmt_pairs(ascii_table) + ';')
    return "\n".join(lines) + "\n"


def apply_to_data_file(path="data/text_printer_data.c"):
    """Replace the Shift-JIS data block in text_printer_data.c with GB2312.

    The original file contains raw Shift-JIS bytes, so the block is located by
    its ASCII-only anchors and rewritten byte-exactly.
    """
    src = open(path, "rb").read().decode("latin-1")
    start_marker = "// [D_089380d0] Line Cut-Off Ellipsis"
    end_marker = '"\\x0\\x0\\x0";'

    start = src.index(start_marker)
    end = src.index(end_marker, start) + len(end_marker)

    new_section = build_data_section()
    src = src[:start] + new_section + src[end:]
    open(path, "wb").write(src.encode("latin-1"))
    print("Patched %s with GB2312 data tables." % path)


def main():
    import argparse
    parser = argparse.ArgumentParser(
        description="Generate/apply GB2312 text data for the RTCN TextPrinter.")
    parser.add_argument("--apply", action="store_true",
                        help="rewrite data/text_printer_data.c in place "
                             "(default: print the C tables to stdout)")
    args = parser.parse_args()

    if args.apply:
        apply_to_data_file()
    else:
        print(build_data_section())


if __name__ == "__main__":
    main()
