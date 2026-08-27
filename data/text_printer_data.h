#pragma once


/* TEXT PRINTER DATA */


// GB2312 full-set layout: 87 zones (0xA1-0xF7) x 94 glyphs = 8178 slots.
// A subset build (only the characters the Chinese translation uses) needs
// fewer; regenerate D_08938140 with tools/gen_text_gb2312_data.py.
#define TEXT_PRINTER_TOTAL_GLYPHS 0x1FF2

struct TextPrinterFont {
    u8 *glyphData;
    u8 *glyphWidths;
    u8 glyphDataSize;
    u8 glyphSpacing;
    u8 unkA;
    u8 unkB;
};

extern struct TextPrinterFont D_089380ac[];

extern char D_089380d0[]; // Line Cut-Off Ellipsis (GB2312)
extern char D_089380d4[]; // Full-Width Open Brackets (GB2312)
extern char D_089380e4[]; // Half-Width Open Brackets
extern char D_089380e8[]; // Full-Width Ending Punctuation (GB2312)
extern char D_08938138[]; // Half-Width Ending Punctuation
extern s16 D_08938140[]; // GB2312 Lead-Byte (0xA1-0xF7) -> Glyph Base IDs
extern char D_08938194[]; // ASCII (0x20-0x7E) -> GB2312 Fullwidth Pairs
extern u8 D_08938258[];
extern u8 D_0893825d[];

extern u8 text_small_glyphs_bin[]; // [D_08938264]
extern u8 text_small_glyph_sizes_bin[]; // [D_089631c4]
extern u8 text_medium_glyphs_bin[]; // [D_08964e68]
extern u8 text_medium_glyph_sizes_bin[]; // [D_0898fdc8]
extern u8 text_large_glyphs_bin[]; // [D_08991a6c]
extern u8 text_large_glyph_sizes_bin[]; // [D_089caeec]
