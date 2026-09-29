/* 中文文本：选项页仅接入阶段 5 的已校对译文；控制码待复核项见 TODO_未校对.md。 */
#include "global.h"
#include "graphics.h"
#include "src/scenes/options.h"
#include "graphics/options/options_graphics.h"
#include "text.h"


  /* OPTIONS MENU - SCENE DATA */


// [D_089cfac8] Graphics Table
struct GraphicsTable options_gfx_table[] = {
    /* BG Tileset */ {
        /* Src.  */ &options_bg_tiles,
        /* Dest. */ BG_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Map */ {
        /* Src.  */ &options_bg_map,
        /* Dest. */ BG_MAP_BASE(0xE800),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* OBJ Tileset */ {
        /* Src.  */ &options_obj,
        /* Dest. */ OBJ_TILESET_BASE(0),
        /* Size  */ COMPRESSED_GFX_SOURCE
    },
    /* BG Palette */ {
        /* Src.  */ options_pal,
        /* Dest. */ BG_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    /* OBJ Palette */ {
        /* Src.  */ options_pal,
        /* Dest. */ OBJ_PALETTE_BUFFER(0),
        /* Size  */ 0x200
    },
    END_OF_GRAPHICS_TABLE
};


// [D_089cfb10] Buffered Textures List
struct CompressedData *options_buffered_textures[] = {
    END_OF_BUFFERED_TEXTURES_LIST
};

// 阶段 5 已校对：保留确认框的三行控制字节和原有居中留白，只替换可见文字。
// TODO 未校对：中文全角空格的实际光标位置仍需在选项画面核验。
const char options_data_clear_confirm_text[] =
        "\0023" "\0013" "\001C" "真的要删掉吗？\n"
        "\0021" "\0011" "\001C" "　　　　　　　确认\n"
        "　　　　　　　取消";

const char *options_desc_text[] = {
    /* SOUND MODE ------------------------------------- */
        "\0023" "\0013" "\001C" "声音模式\n"
        "\0024" "\0011" "\001L" "立体声　　" TEXT_COLOR_1 "戴耳机就选这个！推荐！\n"
        "\0024" "\0011" "\001L" "单声道　　" CHAR_1_PIXEL_GAP_UTF8 TEXT_COLOR_1 "用主机喇叭就选这个。",
    /* DATA CLEAR ------------------------------------- */
        "\0023" "\0013" "\001C" "清除数据\n"
        "\0021" "\0011" "\001C" "会把至今为止的记录" TEXT_COLOR_2 "全部" TEXT_COLOR_1 "删掉，然后从头开始。\n"
        "要想清楚哦！"
    /* ------------------------------------------------ */
};

const char *advance_options_label_text[] = {
    "Sound Effects",
    "Music",
#ifdef RUMBLE
    "Rumble",
#endif
    "Show Disclaimer",
    "Game Select Music",
};

const char *advance_options_desc_text[] = {
    /* NON-JP SFX ------------------------------------- */
        // TODO 未校对：advance_options_desc_text[0] 译文包未到 stage 5，暂留原文。
        "\0023" "\0013" "\001C" "Sound Effects\n"
        "\0024" "\0011" "\001L" "English   " "\0021" "Use the localized sound effects.\n"
        "\0024" "\0011" "\001L" "Japanese  " "\0021" "Use the original sound effects.",
    /* NON-JP MUSIC ----------------------------------- */
        // TODO 未校对：advance_options_desc_text[1] 译文包未到 stage 5，暂留原文。
        "\0023" "\0013" "\001C" "Music\n"
        "\0024" "\0011" "\001L" "English   " "\0021" "Use the localized music.\n"
        "\0024" "\0011" "\001L" "Japanese  " "\0021" "Use the original music.",
    /* RUMBLE ----------------------------------------- */
#ifdef RUMBLE
        // TODO 未校对：advance_options_desc_text[2] 译文包未到 stage 5，暂留原文。
        "\0023" "\0013" "\001C" "Rumble\n"
        "\0024" "\0011" "\001L" "On        " "\0021" "Rumble is active during gameplay.\n"
        "\0024" "\0011" "\001L" "Off       " "\0021" "Rumble is disabled.",
#endif
    /* SHOW DISCLAIMER -------------------------------- */
        // TODO 未校对：advance_options_desc_text[3] 译文包未到 stage 5，暂留原文。
        "\0023" "\0013" "\001C" "Show Disclaimer\n"
        "\0024" "\0011" "\001L" "Show      " "\0021" "Show the disclaimer at startup.\n"
        "\0024" "\0011" "\001L" "Skip      " "\0021" "Skip the disclaimer at startup.",
    /* ALT GAME SELECT MUSIC --------------------------- */
        // TODO 未校对：advance_options_desc_text[4] 译文包未到 stage 5，暂留原文。
        "\0023" "\0013" "\001C" "Game Select Music\n"
        "\0024" "\0011" "\001L" "Normal    " "\0021" "Use Game Select 2 after the credits.\n"
        "\0024" "\0011" "\001L" "Swapped   " "\0021" "Use Game Select 1 after the credits.",
};


// [D_089cfb1c] Audio Options
struct Animation *options_sound_mode_anim[][2] = {
    /* Stereo */ {
        /* Selected   */ anim_options_select_stereo,
        /* Unselected */ anim_options_off_stereo
    },
    /* Monaural */ {
        /* Selected   */ anim_options_select_mono,
        /* Unselected */ anim_options_off_mono
    }
};
