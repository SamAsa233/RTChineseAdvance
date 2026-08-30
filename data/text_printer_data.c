#include "global.h"
#include "text.h"
#include "text_printer_data.h"


/* TEXT PRINTER DATA */


// [D_089380ac] Text Printer Font Table
struct TextPrinterFont D_089380ac[] = {
    /* Small Text */ {
        /* Glyph Data      */ text_small_glyphs_bin,
        /* Glyph Widths    */ text_small_glyph_sizes_bin,
        /* Glyph Data Size */ 0x18,
        /* Glyph Spacing   */ 1,
        /* unkA            */ 11,
        /* unkB            */ 10
    },
    /* Medium Text */ {
        /* Glyph Data      */ text_medium_glyphs_bin,
        /* Glyph Widths    */ text_medium_glyph_sizes_bin,
        /* Glyph Data Size */ 0x18,
        /* Glyph Spacing   */ 2,
        /* unkA            */ 11,
        /* unkB            */ 12
    },
    /* Large Text */ {
        /* Glyph Data      */ text_large_glyphs_bin,
        /* Glyph Widths    */ text_large_glyph_sizes_bin,
        /* Glyph Data Size */ 0x20,
        /* Glyph Spacing   */ 2,
        /* unkA            */ 11,
        /* unkB            */ 16
    },
};

// [D_089380d0] Line Cut-Off Ellipsis (GB2312)
char D_089380d0[] = "";

// [D_089380d4] Full-Width Open Brackets (GB2312)
char D_089380d4[] = "£¨¡²£Û£û¡¸¡º¡¾";

// [D_089380e4] Half-Width Open Brackets
char D_089380e4[] = "([{";

// [D_089380e8] Full-Width Ending Punctuation (GB2312)
char D_089380e8[] = "¡¢¡££¬£®£¿£¡¡«£©¡³£Ý£ý¡¹¡»¡¿";

// [D_08938138] Half-Width Ending Punctuation
char D_08938138[] = "!?,.)]}";

// [D_08938140] GB2312 Lead-Byte (0xA1-0xF7) -> Glyph Base IDs
// glyphID = base + (trail - 0xA1);  -1 = zone has no glyphs
s16 D_08938140[] = {
    0x0000, 0x005e, 0x00bc, 0x011a, 0x0178, 0x01d6, 0x0234, 0x0292, 0x02f0, 0x034e, 0x03ac, 0x040a,
    0x0468, 0x04c6, 0x0524, 0x0582, 0x05e0, 0x063e, 0x069c, 0x06fa, 0x0758, 0x07b6, 0x0814, 0x0872,
    0x08d0, 0x092e, 0x098c, 0x09ea, 0x0a48, 0x0aa6, 0x0b04, 0x0b62, 0x0bc0, 0x0c1e, 0x0c7c, 0x0cda,
    0x0d38, 0x0d96, 0x0df4, 0x0e52, 0x0eb0, 0x0f0e, 0x0f6c, 0x0fca, 0x1028, 0x1086, 0x10e4, 0x1142,
    0x11a0, 0x11fe, 0x125c, 0x12ba, 0x1318, 0x1376, 0x13d4, 0x1432, 0x1490, 0x14ee, 0x154c, 0x15aa,
    0x1608, 0x1666, 0x16c4, 0x1722, 0x1780, 0x17de, 0x183c, 0x189a, 0x18f8, 0x1956, 0x19b4, 0x1a12,
    0x1a70, 0x1ace, 0x1b2c, 0x1b8a, 0x1be8, 0x1c46, 0x1ca4, 0x1d02, 0x1d60, 0x1dbe, 0x1e1c, 0x1e7a,
    0x1ed8, 0x1f36, 0x1f94,
};

// [D_08938194] ASCII (0x20-0x7E) -> GB2312 Fullwidth Pairs
// 95 pairs, index = code - 0x20
char D_08938194[] =
    "\xA1\xA1""£¡¡±££¡ç£¥£¦¡¯£¨£©£ª£«¡¢£­£®£¯£°£±£²£³£´£µ£¶£·£¸£¹£º£»£¼£½£¾£¿£À£Á£Â£Ã£Ä£Å£Æ£Ç£È£É£Ê£Ë£Ì£Í£Î£Ï£Ð£Ñ£Ò£Ó£Ô£Õ£Ö£×£Ø£Ù£Ú£Û£¤£Ý£Þ£ß"
    "\xA1\xA1""£á£â£ã£ä£å£æ£ç£è£é£ê£ë£ì£í£î£ï£ð£ñ£ò£ó£ô£õ£ö£÷£ø£ù£ú£û£ü£ý£þ"
    "\xA1\xA1"
    "\x0\x0\x0";

// [D_08938258]
u8 D_08938258[] = { 32, 16, 10, 8, 4 };

// [D_0893825d]
u8 D_0893825d[] = { 1, 2, 3, 4, 8 };
