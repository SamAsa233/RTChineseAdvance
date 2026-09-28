#include "global.h"
#include "debug_menu.h"


/* DEBUG MENU TABLE */


// [D_089ddbe8] Debug Menu Table
struct DebugMenuEntry debug_menu_entry_table[] = {
    /* R-IQ (Title Screen) */ {
        /* Scene */ &scene_title,
        /* Label */ "Ｒ－ＩＱ　（标题）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Main Menu) */ {
        /* Scene */ &scene_main_menu,
        /* Label */ "Ｒ－ＩＱ　（菜单）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Game Select) */ {
        /* Scene */ &scene_game_select,
        /* Label */ "Ｒ－ＩＱ　（游戏）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Rhythm Data Room) */ {
        /* Scene */ &scene_data_room,
        /* Label */ "Ｒ－ＩＱ　（资料室）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Studio) */ {
        /* Scene */ &scene_studio,
        /* Label */ "Ｒ－ＩＱ　（录音室）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Options) */ {
        /* Scene */ &scene_options_menu,
        /* Label */ "Ｒ－ＩＱ　（选项）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 1) */ {
        /* Scene */ &scene_results_ver_debug,
        /* Label */ "Ｒ－ＩＱ　（结果）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 2) */ {
        /* Scene */ &scene_results_ver_rank,
        /* Label */ "Ｒ－ＩＱ　（结果　２）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 3) */ {
        /* Scene */ &scene_results_ver_score,
        /* Label */ "Ｒ－ＩＱ　（结果　３）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Result 4) */ {
        /* Scene */ &scene_epilogue,
        /* Label */ "Ｒ－ＩＱ　（结果　４）",
        /* Epil. */ TRUE
    },
    /* R-IQ (Rhythm Library) */ {
        /* Scene */ &scene_arrival,
        /* Label */ "Ｒ－ＩＱ　（获得信件）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Perfect) */ {
        /* Scene */ &scene_perfect,
        /* Label */ "Ｒ－ＩＱ　（完美）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Endless Games) */ {
        /* Scene */ &scene_endless_menu,
        /* Label */ "Ｒ－ＩＱ　（无尽游戏）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Drum Lessons) */ {
        /* Scene */ &scene_lessons_menu,
        /* Label */ "Ｒ－ＩＱ　（击鼓课程）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Rhythm Toys) */ {
        /* Scene */ &scene_toys_menu,
        /* Label */ "Ｒ－ＩＱ　（节奏玩具）",
        /* Epil. */ FALSE
    },
    /* R-IQ (Cafe) */ {
        /* Scene */ &scene_cafe,
        #ifdef PARADISE
        /* Label */ "Ｒ－ＩＱ　（咖啡谈心）", // shoutout to british people
        #else
        /* Label */ "R-IQ (Cafe Counseling)",
        #endif
        /* Epil. */ FALSE
    },
    /* Warning */ {
        /* Scene */ &scene_warning,
        /* Label */ "警告",
        /* Epil. */ FALSE
    },
    /* GBP Handshake */ {
        /* Scene */ &scene_gbp_handshake,
        /* Label */ "ＧＢＰ　手柄震动",
        /* Epil. */ FALSE
    },
    /* Disclaimer */ {
        /* Scene */ &scene_disclaimer,
        /* Label */ "声明",
        /* Epil. */ FALSE
    },
    /* Opening (A Type) */ {
        /* Scene */ &scene_drum_samurai_demo_cutscene,
        /* Label */ "开场　（类型A）",
        /* Epil. */ FALSE
    },
    /* Opening (B Type) */ {
        /* Scene */ &scene_drum_samurai_opening_cutscene,
        /* Label */ "开场　（类型B）",
        /* Epil. */ FALSE
    },
    /* Rhythm Test (Total) */ {
        /* Scene */ &scene_rhythm_test_opening,
        /* Label */ "节奏感测试　（开场）"
    },
    /* Rhythm Test (Click) */ {
        /* Scene */ &scene_rhythm_test_click,
        /* Label */ "节奏感测试　（点击）",
    },
    /* Rhythm Test (Cue) */ {
        /* Scene */ &scene_rhythm_test_cue,
        /* Label */ "节奏感测试　（数拍）",
    },
    /* Rhythm Test (Trick) */ {
        /* Scene */ &scene_rhythm_test_trick,
        /* Label */ "节奏感测试　（棘手）"
    },
    /* Reading Material */ {
        /* Scene */ &scene_reading,
        /* Label */ "信件",
        /* Epil. */ FALSE
    },
    /* Studio Drummer */ {
        /* Scene */ &scene_drum_studio_ver0,
        /* Label */ "录音室打鼓　（Ｖｅｒ．　０）",
        /* Epil. */ FALSE
    },
    /* Studio Drummer */ {
        /* Scene */ &scene_drum_studio_ver2,
        /* Label */ "录音室打鼓　（Ｖｅｒ．　２）",
        /* Epil. */ FALSE
    },
 /* Drum LIVE */ {
        /* Scene */ &scene_drum_live,
        /* Label */ "现场演出",
        /* Epil. */ TRUE
    },
    /* Ending (from clearing Remix 6) */ {
        /* Scene */ &scene_staff_credit_remix_6,
        /* Label */ "结尾　（通关）",
        /* Epil. */ FALSE
    },
    /* Ending (from Game Select) */ {
        /* Scene */ &scene_staff_credit,
        /* Label */ "结尾　（再次观看）",
        /* Epil. */ FALSE
    },
    /* Lesson (Basic 1) */ {
        /* Scene */ &scene_drum_lesson_basic_1,
        /* Label */ "课程 （入门　１）",
        /* Epil. */ FALSE
    },
    /* Lesson (Basic 2) */ {
        /* Scene */ &scene_drum_lesson_basic_2,
        /* Label */ "课程 （入门　２）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 1) */ {
        /* Scene */ &scene_drum_lesson_short_1,
        /* Label */ "课程 （基础　１）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 2) */ {
        /* Scene */ &scene_drum_lesson_short_2,
        /* Label */ "课程 （基础　２）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 3) */ {
        /* Scene */ &scene_drum_lesson_short_3,
        /* Label */ "课程 （基础　３）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 4) */ {
        /* Scene */ &scene_drum_lesson_short_4,
        /* Label */ "课程 （基础　４）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 5) */ {
        /* Scene */ &scene_drum_lesson_short_5,
        /* Label */ "课程 （基础　５）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 6) */ {
        /* Scene */ &scene_drum_lesson_short_6,
        /* Label */ "课程 （基础　６）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 7) */ {
        /* Scene */ &scene_drum_lesson_short_7,
        /* Label */ "课程 （基础　７）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 8) */ {
        /* Scene */ &scene_drum_lesson_short_8,
        /* Label */ "课程 （基础　８）",
        /* Epil. */ FALSE
    },
    /* Lesson (Short 9) */ {
        /* Scene */ &scene_drum_lesson_short_9,
        /* Label */ "课程 （基础　９）",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 1) */ {
        /* Scene */ &scene_drum_lesson_long_1,
        /* Label */ "课程 （进阶　１）",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 2) */ {
        /* Scene */ &scene_drum_lesson_long_2,
        /* Label */ "课程 （进阶　２）",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 3) */ {
        /* Scene */ &scene_drum_lesson_long_3,
        /* Label */ "课程 （进阶　３）",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 4) */ {
        /* Scene */ &scene_drum_lesson_long_4,
        /* Label */ "课程 （进阶　４）",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 5) */ {
        /* Scene */ &scene_drum_lesson_long_5,
        /* Label */ "课程 （进阶　５）",
        /* Epil. */ FALSE
    },
    /* Lesson (Long 6) */ {
        /* Scene */ &scene_drum_lesson_long_6,
        /* Label */ "课程 （进阶　６）",
        /* Epil. */ FALSE
    },
    /* Lesson (High-Tech 1) */ {
        /* Scene */ &scene_drum_lesson_hi_tech_1,
        /* Label */ "课程 （技巧　１）",
        /* Epil. */ FALSE
    },
    /* Lesson (High-Tech 2) */ {
        /* Scene */ &scene_drum_lesson_hi_tech_2,
        /* Label */ "课程 （技巧　２）",
        /* Epil. */ FALSE
    },
    /* Mr. Upbeat */ {
        /* Scene */ &scene_mr_upbeat,
        #ifdef PARADISE
        /* Label */ "反拍男",
        #else
        /* Label */ "Mr. Upbeat",
        #endif
        /* Epil. */ FALSE
    },
    /* Sick Beats Endless */ {
        /* Scene */ &scene_sick_beats_endless,
        /* Label */ "Sick Beats Special",
        /* Epil. */ FALSE
    },
    /* Quiz Show Endless */ {
        /* Scene */ &scene_quiz_show_endless,
        /* Label */ "节奏问答　特别篇",
        /* Epil. */ FALSE
    },
    /* Mannequin Factory */ {
        /* Scene */ &scene_mannequin_factory,
        /* Label */ "头模工厂",
        /* Epil. */ FALSE
    },
    /* Rhythm Toys (Cat Machine) */ {
        /* Scene */ &scene_cat_machine,
        /* Label */ "猫咪发声机",
        /* Epil. */ FALSE
    },
    /* Mechanical Horse */ {
        /* Scene */ &scene_mechanical_horse,
        /* Label */ "骑马机",
        /* Epil. */ FALSE

    },
    /* Rhythm Toys (Confession Machine) */ {
        /* Scene */ &scene_love_machine,
        /* Label */ "告白机",
        /* Epil. */ FALSE
    },
    /* Rhythm Toys (Rap Machine) */ {
        /* Scene */ &scene_rap_machine,
        /* Label */ "饶舌发声机",
        /* Epil. */ FALSE
    },
    /* Karate Man */ {
        /* Scene */ &scene_karate_man,
        /* Label */ "空手道家",
        /* Epil. */ TRUE
    },
    /* Karate Man 2 */ {
        /* Scene */ &scene_karate_man_2,
        /* Label */ "空手道家　２",
        /* Epil. */ TRUE
    },
    /* Karate Man (Extra) */ {
        /* Scene */ &scene_karate_man_extra,
        /* Label */ "空手道家　（额外）　ＷＩＰ",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers */ {
        /* Scene */ &scene_rhythm_tweezers,
        /* Label */ "节奏脱毛",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers 2 */ {
        /* Scene */ &scene_rhythm_tweezers_2,
        /* Label */ "节奏脱毛　２",
        /* Epil. */ TRUE
    },
    /* Rhythm Tweezers (Extra) */ {
        /* Scene */ &scene_rhythm_tweezers_extra,
        /* Label */ "节奏脱毛　（额外）",
        /* Epil. */ TRUE
    },
    /* Marching Orders */ {
        /* Scene */ &scene_marching_orders,
        /* Label */ "行军",
        /* Epil. */ TRUE
    },
    /* Marching Orders 2 */ {
        /* Scene */ &scene_marching_orders_2,
        /* Label */ "行军　２",
        /* Epil. */ TRUE
    },
    /* Marching Orders (Extra) */ {
        /* Scene */ &scene_marching_orders_extra,
        /* Label */ "行军　（额外）",
        /* Epil. */ TRUE
    },
    /* Spaceball */ {
        /* Scene */ &scene_spaceball,
        /* Label */ "空中击球手",
        /* Epil. */ TRUE
    },
    /* Spaceball 2 */ {
        /* Scene */ &scene_spaceball_2,
        /* Label */ "空中击球手　２",
        /* Epil. */ TRUE

    },
    /* Spaceball (Extra) */ {
        /* Scene */ &scene_spaceball_extra,
        /* Label */ "空中击球手　（额外）",
        /* Epil. */ TRUE
    },
    /* The Clappy Trio */ {
        /* Scene */ &scene_clappy_trio,
        /* Label */ "啪叽啪叽三人组",
        /* Epil. */ TRUE
    },
    /* The Snappy Trio */ {
        /* Scene */ &scene_snappy_trio,
        /* Label */ "帅气帅气三人组",
        /* Epil. */ TRUE
    },
    /* The Clappy Trio (Extra) */ {
        /* Scene */ &scene_clappy_trio_extra,
        /* Label */ "啪叽啪叽三人组　（额外）　ＷＩＰ",
        /* Epil. */ TRUE
    },
    /* Sneaky Spirits */ {
        /* Scene */ &scene_sneaky_spirits,
        /* Label */ "白色的鬼",
        /* Epil. */ TRUE
    },
    /* Sneaky Spirits 2 */ {
        /* Scene */ &scene_sneaky_spirits_2,
        /* Label */ "白色的鬼　２",
        /* Epil. */ TRUE
    },
    /* Samurai Slice */ {
        /* Scene */ &scene_samurai_slice,
        /* Label */ "居合斩",
        /* Epil. */ TRUE
    },
    /* Rat Race */ {
        /* Scene */ &scene_rat_race,
        /* Label */ "蹑鼠蹑脚",
        /* Epil. */ TRUE
    },
    /* Sick Beats */ {
        /* Scene */ &scene_sick_beats,
        /* Label */ "细菌博士",
        /* Epil. */ TRUE
    },
    /* The Bon Odori */ {
        /* Scene */ &scene_bon_odori,
        /* Label */ "Ｔｈｅ　盂兰盆舞",
        /* Epil. */ TRUE
    },
    /* Bon Dance */ {
        /* Scene */ &scene_bon_dance,
        /* Label */ "盆舞",
        /* Epil. */ TRUE
    },
    /* Wizard's Waltz */ {
        /* Scene */ &scene_wizards_waltz,
        /* Label */ "魔法使",
        /* Epil. */ TRUE
    },
    /* Showtime */ {
        /* Scene */ &scene_showtime,
        /* Label */ "表演时间",
        /* Epil. */ TRUE
    },
    /* Bunny Hop */ {
        /* Scene */ &scene_bunny_hop,
        /* Label */ "跃兔",
        /* Epil. */ TRUE
    },
    /* Tram & Pauline */ {
        /* Scene */ &scene_tram_pauline,
        /* Label */ "小蹦与小床",
        /* Epil. */ TRUE
    },
    /* Space Dance */ {
        /* Scene */ &scene_space_dance,
        /* Label */ "太空之舞",
        /* Epil. */ TRUE
    },
    /* Cosmic Dance */ {
        /* Scene */ &scene_cosmic_dance,
        /* Label */ "宇宙之舞",
        /* Epil. */ TRUE
   },
    /* Quiz Show */ {
        /* Scene */ &scene_quiz_show,
        /* Label */ "节奏问答",
        /* Epil. */ TRUE
    },
    /* Night Walk */ {
        /* Scene */ &scene_night_walk,
        /* Label */ "夜间漫步",
        /* Epil. */ TRUE
    },
    /* Night Walk 2 */ {
        /* Scene */ &scene_night_walk_2,
        /* Label */ "夜间漫步　２",
        /* Epil. */ TRUE
    },
    /* Power Calligraphy */ {
        /* Scene */ &scene_power_calligraphy,
        /* Label */ "节奏书法",
        /* Epil. */ TRUE
    },
    /* Polyrhythm */ {
        /* Scene */ &scene_polyrhythm,
        /* Label */ "复合节奏",
        /* Epil. */ TRUE
    },
    /* Polyrhythm 2 */ {
        /* Scene */ &scene_polyrhythm_2,
        /* Label */ "复合节奏　２",
        /* Epil. */ TRUE
    },
    /* Rap Men */ {
        /* Scene */ &scene_rap_men,
        /* Label */ "饶舌男",
        /* Epil. */ TRUE
    },
    /* Rap Women (by YONE) */ {
        /* Scene */ &scene_rap_women,
        /* Label */ "饶舌女　（米政美版）",
        /* Epil. */ TRUE
    },
    /* Bouncy Road */ {
        /* Scene */ &scene_bouncy_road,
        /* Label */ "跳杆之路",
        /* Epil. */ TRUE
    },
    /* Bouncy Road 2 */ {
        /* Scene */ &scene_bouncy_road_2,
        /* Label */ "跳杆之路　２",
        /* Epil. */ TRUE
    },
    /* Ninja Bodyguard */ {
        /* Scene */ &scene_ninja_bodyguard,
        /* Label */ "忍者",
        /* Epil. */ TRUE
    },
    /* Ninja Bodyguard 2 */ {
        /* Scene */ &scene_ninja_reincarnate,
        /* Label */ "忍者的后代",
        /* Epil. */ TRUE
    },
    /* Toss Boys */ {
        /* Scene */ &scene_toss_boys,
        /* Label */ "传球少年",
        /* Epil. */ TRUE
    },
    /* Toss Boys 2 */ {
        /* Scene */ &scene_toss_boys_2,
        /* Label */ "传球少年　２",
        /* Epil. */ TRUE
    },
    /* Fireworks */ {
        /* Scene */ &scene_fireworks,
        /* Label */ "烟火",
        /* Epil. */ TRUE
    },
    /* Tap Trial */ {
        /* Scene */ &scene_tap_trial,
        /* Label */ "踢踏舞",
        /* Epil. */ TRUE
    },
    /* Tap Trial 2 */ {
        /* Scene */ &scene_tap_trial_2,
        /* Label */ "超级踢踏舞",
        /* Epil. */ TRUE
    },
    /* Remix 1 */ {
        /* Scene */ &scene_remix_1,
        /* Label */ "Ｒｅｍｉｘ　１",
        /* Epil. */ TRUE
    },
    /* Remix 2 */ {
        /* Scene */ &scene_remix_2,
        /* Label */ "Ｒｅｍｉｘ　２",
        /* Epil. */ TRUE
    },
    /* Remix 3 */ {
        /* Scene */ &scene_remix_3,
        /* Label */ "Ｒｅｍｉｘ　３",
        /* Epil. */ TRUE
    },
    /* Remix 4 */ {
        /* Scene */ &scene_remix_4,
        /* Label */ "Ｒｅｍｉｘ　４",
        /* Epil. */ TRUE
    },
    /* Remix 5 */ {
        /* Scene */ &scene_remix_5,
        /* Label */ "Ｒｅｍｉｘ　５",
        /* Epil. */ TRUE
    },
    /* Remix 6 */ {
        /* Scene */ &scene_remix_6,
        /* Label */ "Ｒｅｍｉｘ　６",
        /* Epil. */ TRUE
    },
    /* Remix 7 */ {
        /* Scene */ &scene_remix_7,
        /* Label */ "Ｒｅｍｉｘ　７",
        /* Epil. */ TRUE
    },
    /* Remix 8 */ {
        /* Scene */ &scene_remix_8,
        /* Label */ "Ｒｅｍｉｘ　８",
        /* Epil. */ TRUE
    },
    /* Remix 1 (Extra) */ {
        /* Scene */ &scene_remix_1_extra,
        /* Label */ "Ｒｅｍｉｘ　１　（额外）　ＷＩＰ",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 1) */ {
        /* Scene */ &scene_drum_intro_unused,
        /* Label */ "击鼓课程　（未使用）",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 2) */ {
        /* Scene */ &scene_drum_intro_unused_2,
        /* Label */ "击鼓课程　（未使用　２）",
        /* Epil. */ TRUE
    },
    /* Drum Intro (Unused 3) */ {
        /* Scene */ &scene_drum_intro_unused_3,
        /* Label */ "击鼓课程　（未使用　３）",
        /* Epil. */ TRUE
    },
    /* Tanuki and Monkey */ {
        /* Scene */ &scene_tanuki_and_monkey,
        /* Label */ "狸猫与猴子　（未使用）",
        /* Epil. */ TRUE
    },
    /* Metronome */ {
        /* Scene */ &scene_metronome,
        /* Label */ "节拍器　（未使用）",
        /* Epil. */ TRUE
    },
    /* Drum Girls LIVE */ {
        /* Scene */ &scene_drum_girls_live_unused,
        /* Label */ "Ｄｒｕｍ　Ｇｉｒｌｓ　（未使用）",
        /* Epil. */ TRUE
    },
    /* Horse Machine (Unused) */ {
        /* Scene */ &scene_mechanical_horse_unused,
        /* Label */ "骑马机　（未使用）",
        /* Epil. */ TRUE
    },
    /* Marching Orders (Unused) */ {
        /* Scene */ &scene_marching_orders_unused,
        /* Label */ "行军　（未使用）",
        /* Epil. */ TRUE
    },
    /* Spaceball (Unused) */ {
        /* Scene */ &scene_spaceball_unused,
        /* Label */ "空中击球手　（未使用）",
        /* Epil. */ TRUE
    },
    /* Spaceball (Unused 2) */ {
        /* Scene */ &scene_spaceball_unused_2,
        /* Label */ "空中击球手　（未使用　２）",
        /* Epil. */ TRUE
    },
    /* Snappy Trio (Unused) */ {
        /* Scene */ &scene_snappy_trio_unused,
        /* Label */ "帅气帅气三人组　（未使用）",
        /* Epil. */ TRUE
    },
    /* Rap Women (by KAZU) */ {
        /* Scene */ &scene_rap_women_unused,
        /* Label */ "饶舌女　（大泽和义版）",
        /* Epil. */ TRUE
    },
    /* Bouncy Road (Unused) */ {
        /* Scene */ &scene_bouncy_road_unused,
        /* Label */ "跳杆之路　（未使用）",
        /* Epil. */ TRUE
    },
    /* Bouncy Road (Unused 2) */ {
        /* Scene */ &scene_bouncy_road_unused_2,
        /* Label */ "跳杆之路　（未使用　２）",
        /* Epil. */ TRUE
    },
    /* Tap Trial (Unused) */ {
        /* Scene */ &scene_tap_trial_unused,
        /* Label */ "踢踏舞　（未使用）",
        /* Epil. */ TRUE
    },
    /* Dance Lesson 1 */ {
        /* Scene */ &scene_remix_1_unused,
        /* Label */ "舞蹈课　１　（未使用）",
        /* Epil. */ TRUE
    },
    /* RIQ Data Check */ {
        /* Scene */ &scene_data_check,
        /* Label */ "Ｒ－ＩＱ　数据查看",
        /* Epil. */ FALSE
    },
    /* Asset Test */ {
        /* Scene */ &scene_asset_test,
        /* Label */ "素材测试",
        /* Epil. */ FALSE  
    },
    /* Flash Memory Test */ {
        /* Scene */ &scene_flash_mem_test,
        /* Label */ "闪存测试",
        /* Epil. */ FALSE
    },
    /* Read Error */ {
        /* Scene */ &scene_read_error,
        /* Label */ "读取错误",
        /* Epil. */ FALSE  
    },
    /* Template Scene */ {
        /* Scene */ &scene_template,
        /* Label */ "场景模板",
        /* Epil. */ FALSE  
    },
    /* Data Clear */ {
        /* Scene */ &scene_data_clear,
        /* Label */ "数据清除",
        /* Epil. */ FALSE
    },
    /* R-IQ Save Editor */ {
        /* Scene */ &scene_save_editor,
        /* Label */ "Ｒ－ＩＱ　存档编辑器",
        /* Epil. */ FALSE
    },
    /* Sequence Player */ {
        /* Scene */ &scene_sequence_player,
        /* Label */ "序列播放器",
        /* Epil. */ FALSE
    },
    /* Debug Menu */ {
        /* Scene */ &scene_debug_menu,
        /* Label */ "调试菜单",
        /* Epil. */ FALSE
    },
    END_OF_DEBUG_ENTRIES
};


// [D_089ddf60] Page Number Digits
char debug_menu_counter_digits[] = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


// Render Text
void debug_menu_render_table(s32 targetPage, s32 targetRow) {
    char string[100];
    s32 totalPages;
    u32 i, j;

    totalPages = (gDebugMenu->totalEntries - 1) / DEBUG_MENU_ENTRY_PER_PAGE;

    if (targetPage < 0) {
        targetPage = totalPages;
    }

    if (targetPage > totalPages) {
        targetPage = 0;
    }

    if ((targetPage * DEBUG_MENU_ENTRY_PER_PAGE) + targetRow >= gDebugMenu->totalEntries) {
        targetRow = (gDebugMenu->totalEntries - 1) - (totalPages * DEBUG_MENU_ENTRY_PER_PAGE);
    }

    if (targetPage != gDebugMenu->page) {
        struct PrintedTextAnim *textAnim;

        for (i = 0; i < DEBUG_MENU_ENTRY_PER_PAGE; i++) {
            if (gDebugMenu->textLines[i] > -1) {
                delete_bmp_font_obj_text_anim(gDebugMenu->objFont, gDebugMenu->textLines[i]);
                sprite_delete(gSpriteHandler, gDebugMenu->textLines[i]);
                gDebugMenu->textLines[i] = -1;
            }
        }

        for (j = 0, i = (targetPage * DEBUG_MENU_ENTRY_PER_PAGE); (i < (targetPage * DEBUG_MENU_ENTRY_PER_PAGE) + DEBUG_MENU_ENTRY_PER_PAGE) && (i < gDebugMenu->totalEntries); j++, i++) {
            textAnim = bmp_font_obj_print_l(gDebugMenu->objFont, debug_menu_entry_table[i].label, 1, 0);
            gDebugMenu->textLines[j] = sprite_create(gSpriteHandler, textAnim->frames, 0, 32, (j * 21) + 32, 0x800, 0, 0, 0);
        }

        delete_bmp_font_obj_text_anim(gDebugMenu->objFont, gDebugMenu->counter);
        snprintf(string, 100, "%c/%c", debug_menu_counter_digits[targetPage], debug_menu_counter_digits[totalPages]);
        textAnim = bmp_font_obj_print_r(gDebugMenu->objFont, string, 1, 4);
        sprite_set_anim(gSpriteHandler, gDebugMenu->counter, textAnim->frames, 0, 0, 0, 0);
    }

    gDebugMenu->page = targetPage;
    gDebugMenu->row = targetRow;

    for (i = 0; i < DEBUG_MENU_ENTRY_PER_PAGE; i++) {
        if (gDebugMenu->textLines[i] > -1) {
            sprite_set_base_palette(gSpriteHandler, gDebugMenu->textLines[i], 0);
        }
    }

    sprite_set_base_palette(gSpriteHandler, gDebugMenu->textLines[gDebugMenu->row], 7);
    sprite_set_x_y(gSpriteHandler, gDebugMenu->cursor, 16, (gDebugMenu->row * 21) + 32);
}
