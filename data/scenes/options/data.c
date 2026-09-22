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

const char options_data_clear_confirm_text[] =
        "\0023" "\0013" "\001C" "真的要删掉吗？\n"
        "\0021" "\0011" "\001C" "       确认\n"
        "     取消";

const char *options_desc_text[] = {
    /* SOUND MODE ------------------------------------- */
        "\0023" "\0013" "\001C" "声音模式\n"
        "\0024" "\0011" "\001L" "立体声  " TEXT_COLOR_1 " 戴耳机就选这个！推荐！\n"
        "\0024" "\0011" "\001L" "单声道   " CHAR_1_PIXEL_GAP_UTF8 TEXT_COLOR_1 "用主机喇叭就选这个。",
    /* DATA CLEAR ------------------------------------- */
        "\0023" "\0013" "\001C" "清除数据\n"
        "\0021" "\0011" "\001C" "会把至今为止的记录" TEXT_COLOR_2 "全部删掉 " TEXT_COLOR_1 "，然后从头开始。\n"
        TEXT_COLOR_2 " 要想清楚哦！"
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
        "\0023" "\0013" "\001C" "音效\n"
        "\0024" "\0011" "\001L" "中文  " "\0021" "使用中文翻配音效\n"
        "\0024" "\0011" "\001L" "日语  " "\0021" "使用原版日语音效",
    /* NON-JP MUSIC ----------------------------------- */
        "\0023" "\0013" "\001C" "音乐\n"
        "\0024" "\0011" "\001L" "中文翻唱  " "\0021" "使用中文翻唱音乐\n"
        "\0024" "\0011" "\001L" "日语原唱  " "\0021" "使用原版日语音乐",
    /* RUMBLE ----------------------------------------- */
#ifdef RUMBLE
        "\0023" "\0013" "\001C" "震动\n"
        "\0024" "\0011" "\001L" "开       " "\0021" "游玩时设备将会震动\n"
        "\0024" "\0011" "\001L" "关       " "\0021" "游玩时震动将被禁用",
#endif
    /* SHOW DISCLAIMER -------------------------------- */
        "\0023" "\0013" "\001C" "汉化声明\n"
        "\0024" "\0011" "\001L" "展示      " "\0021" "游戏启动时展示汉化声明\n"
        "\0024" "\0011" "\001L" "跳过      " "\0021" "启动时不再展示汉化声明",
    /* ALT GAME SELECT MUSIC --------------------------- */
        "\0023" "\0013" "\001C" "游戏选择菜单音乐\n"
        "\0024" "\0011" "\001L" "启用切换    " "\0021" "二周目将切换新音乐\n"
        "\0024" "\0011" "\001L" "禁用切换    " "\0021" "二周目仍播放旧音乐",
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
