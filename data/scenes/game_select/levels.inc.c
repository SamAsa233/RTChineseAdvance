// Level Entries Table
struct LevelData level_data_table[] = {
    /* KARATE_MAN */ {
        /* Entry Scene   */ &scene_karate_man,
        /* Level Name    */ "空手道家",
        /* Level Desc.   */ "向飞来的东西\n"
                            "按"CHAR_A_BUTTON_UTF8"出拳\n"
                            "很常见的游戏？\n"
                            "……也许吧。",
        /* Level Icon    */ 8,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "没关系，还有明天。",
            /* OK        */ "总之，先吃饭吧！",
            /* SUPERB    */ "居然打飞了这么多！！"
        }
    },
    /* KARATE_MAN_2 */ {
        /* Entry Scene   */ &scene_karate_man_2,
        /* Level Name    */ "空手道家 2",
        /* Level Desc.   */ "向飞来的东西\n"
                            "按"CHAR_A_BUTTON_UTF8"出拳！\n"
                            "不过，这速度\n"
                            "有点古怪哦。",
        /* Level Icon    */ 0,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "这节奏是什么鬼啊——！！",
            /* OK        */ "嘛，先不管那些。来吃饭吧！",
            /* SUPERB    */ "差不多就是这样啦——！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CLAPPY_TRIO */ {
        /* Entry Scene   */ &scene_clappy_trio,
        /* Level Name    */ "啪叽啪叽三人组",
        /* Level Desc.   */ "我们要依次拍手哦！\n"
                            "你排在第３个。\n"
                            "仔细看好前面两人！",
        /* Level Icon    */ 4,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_clappy_trio_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "同伴都走啦！",
            /* OK        */ "现在就满足，可能还早了点呢。",
            /* SUPERB    */ "这三人组，配合也太默契啦！！"
        }
    },
    /* SNAPPY_TRIO */ {
        /* Entry Scene   */ &scene_snappy_trio,
        /* Level Name    */ "帅气帅气三人组",
        /* Level Desc.   */ "原本穿着随意的他们\n"
                            "这次换上了\n"
                            "一身笔挺西装！\n"
                            "太帅了！！",
        /* Level Icon    */ 10,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_snappy_trio_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "呀啊！饶了我吧！！",
            /* OK        */ "就差那么一点点了呢…",
            #ifdef PARADISE
            /* SUPERB    */ "Perfect sync! It must be the outfits, right?"
            #else
            /* SUPERB    */ "配合十分默契！ 耶——！"
            #endif
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* POLYRHYTHM */ {
        /* Entry Scene   */ &scene_polyrhythm,
        /* Level Name    */ "复合节奏",
        /* Level Desc.   */ "掌握"CHAR_DPAD_UTF8"与"CHAR_A_BUTTON_UTF8"\n"
							"同时按下的诀窍！\n"
							"其实挺简单的。\n"
							"大概吧……",
        /* Level Icon    */ 3,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_polyrhythm_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "这红色小东西，想实现大规模量产真是相当困难啊…",
            /* OK        */ "源源不断地生产红色小东西吧！",
            /* SUPERB    */ "可真是一个劲儿地猛造红色小东西啊！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* POLYRHYTHM_2 */ {
        /* Entry Scene   */ &scene_polyrhythm_2,
        /* Level Name    */ "复合节奏 2",
        /* Level Desc.   */ "这就是左右分控！\n"
                            "跟着节奏完成操作，\n"
                            "来吧，复合节奏！\n"
                            "耶——！",
        /* Level Icon    */ 51,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_polyrhythm_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "红色小东西，还得再多生产点才行…",
            /* OK        */ "再多一点 再多一点，继续生产红色小东西！",
            /* SUPERB    */ "红色小东西要铺天盖地大规模量产咯！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NIGHT_WALK */ {
        /* Entry Scene   */ &scene_night_walk,
        /* Level Name    */ "夜空漫步",
        /* Level Desc.   */ "跟着音乐一起\n"
                            "尽情跳起来！\n"
                            "星星聚集，\n"
                            "你也奔向夜空…",
        /* Level Icon    */ 7,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_night_walk_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "下一次可要再加把劲喔…",
            /* OK        */ "在夜空下散步，真开心呀。",
            /* SUPERB    */ "星星们正在欢迎你哦！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NIGHT_WALK_2 */ {
        /* Entry Scene   */ &scene_night_walk_2,
        /* Level Name    */ "夜空漫步 2",
        /* Level Desc.   */ "跟着音乐节拍\n"
                            "尽情跳起来！\n"
                            "遇到电击鱼\n"
                            "可要小心哦。",
        /* Level Icon    */ 41,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_night_walk_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "哇呀——！失败了！！",
            /* OK        */ "夜晚的风吹起来可真舒服呀。",
            /* SUPERB    */ "你已经跟星星们成好朋友啦！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RHYTHM_TWEEZERS */ {
        /* Entry Scene   */ &scene_rhythm_tweezers,
        /* Level Name    */ "节奏脱毛",
        /* Level Desc.   */ "那讨厌的“毛”\n"
                            "总是不停地长出来！\n"
                            "拔掉它，\n"
                            "拔掉它！",
        /* Level Icon    */ 14,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "这样可根本卖不出去啊！",
            /* OK        */ "为啥俺家的蔬菜会长毛啊？",
            /* SUPERB    */ "一身轻松！空气真新鲜！！"
        }
    },
    /* RHYTHM_TWEEZERS_2 */ {
        /* Entry Scene   */ &scene_rhythm_tweezers_2,
        /* Level Name    */ "节奏脱毛 2",
        /* Level Desc.   */ "那讨厌的“毛”\n"
                            "居然又长出来了！\n"
                            "拔掉它，\n"
                            "拔掉它！",
        /* Level Icon    */ 25,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "为什么会长毛啊——！？",
            /* OK        */ "为啥偏偏只有俺家的蔬菜会长毛…？",
            /* SUPERB    */ "一身轻松！空气好得不得了！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SICK_BEATS */ {
        /* Entry Scene   */ &scene_sick_beats,
        /* Level Name    */ "细菌博士",
        /* Level Desc.   */ "\0023" "来自助手的通报\n"
                            "“不好了！\n"
                            "细菌爆发啦！！\n"
                            #ifdef PARADISE
                            "Help us, Dr Cutlery!",
                            #else
                            "博士，快来救命啊～”",
                            #endif
        /* Level Icon    */ 13,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_sick_beats_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "研究失败了。",
            /* OK        */ "或许失败乃成功之母呢！",
            /* SUPERB    */ "研制出了超级厉害的药剂！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* BOUNCY_ROAD */ {
        /* Entry Scene   */ &scene_bouncy_road,
        /* Level Name    */ "跳杆之路",
        /* Level Desc.   */ "飞过来的圆球，\n"
                            "那可是好东西，\n"
							"千万别漏接哦！",
        /* Level Icon    */ 12,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bouncy_road_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "还挺有难度啊——！",
            /* OK        */ "刚才这些配合还挺厉害呢！",
            /* SUPERB    */ "简单 简单♪"
        }
    },
    /* BOUNCY_ROAD_2 */ {
        /* Entry Scene   */ &scene_bouncy_road_2,
        /* Level Name    */ "跳杆之路 2",
        /* Level Desc.   */ "飞过来的圆球。\n"
                            "那真的是个\n"
                            "好东西哟～。\n"
                            "可别漏接哦！",
        /* Level Icon    */ 50,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bouncy_road_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "呜哇！搞砸了！！",
            /* OK        */ "你刚才已经相当努力了呢！",
            /* SUPERB    */ "轻松 轻松♪"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NINJA_BODYGUARD */ {
        /* Entry Scene   */ &scene_ninja_bodyguard,
        /* Level Name    */ "忍者",
        /* Level Desc.   */ "敌人来袭！\n"
                            "用"CHAR_DPAD_UTF8"与"CHAR_A_BUTTON_UTF8"迎战！\n"
                            "富士山！！",
        /* Level Icon    */ 5,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_ninja_bodyguard_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "啊呀！主公昏倒了！！",
            /* OK        */ "主公！对不起啊〜。",
            /* SUPERB    */ "被人夸干得漂亮啦！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* NINJA_REINCARNATE */ {
        /* Entry Scene   */ &scene_ninja_reincarnate,
        /* Level Name    */ "忍者的后代",
        /* Level Desc.   */ "我爷爷的\n"
                            "爷爷的\n"
                            "爷爷啊，\n"
                            "可是忍者呢。",
        /* Level Icon    */ 38,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_ninja_reincarnate_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "别输啊！就指望你了——！！",
            /* OK        */ "嗯，底子不错嘛。加油！",
            /* SUPERB    */ "你很强。祝你幸福…！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SNEAKY_SPIRITS */ {
        /* Entry Scene   */ &scene_sneaky_spirits,
        /* Level Name    */ "白色的鬼",
        /* Level Desc.   */ "那个白色的家伙\n"
                            "在小瞧咱们！\n"
                            "气死我啦——！！\n"
                            "得狠狠教训它！",
        /* Level Icon    */ 1,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_sneaky_spirits_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "竟被逃掉的家伙捉弄了！",
            /* OK        */ "拿下！",
            /* SUPERB    */ "干掉一大堆！！"
        }
    },
    /* SNEAKY_SPIRITS_2 */ {
        /* Entry Scene   */ &scene_sneaky_spirits_2,
        /* Level Name    */ "白色的鬼 2",
        /* Level Desc.   */ "那个白色的家伙\n"
                            "完全不把咱们放在眼里！\n"
                            "可恶可恶！！\n"
                            "得狠狠教训它一顿！",
        /* Level Icon    */ 53,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_sneaky_spirits_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "哇啊！被耍得毫无还手之力！",
            /* OK        */ "鬼：“什、什么呀～”",
            /* SUPERB    */ "你们，都给我好好反省！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SAMURAI_SLICE */ {
        /* Entry Scene   */ &scene_samurai_slice,
        /* Level Name    */ "居合斩",
        /* Level Desc.   */ "闪开 闪开，\n"
                            "那群家伙来了。\n"
                            "你身为武士，\n"
                            "格杀勿论！",
        /* Level Icon    */ 18,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_samurai_slice_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "刀刃崩口了！",
            /* OK        */ "仍需继续磨练！",
            /* SUPERB    */ "这锋利度，简直棒极了！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SPACEBALL */ {
        /* Entry Scene   */ &scene_spaceball,
        /* Level Name    */ "空中击球手",
        /* Level Desc.   */ "别在意镜头缩放！\n"
                            "就这样，请饶了我吧。\n"
                            "不要依赖视觉！\n"
                            "大胆上吧～！",
        /* Level Icon    */ 9,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "就这样，请饶了我吧。",
            /* OK        */ "朝着更高处继续练吧！",
            /* SUPERB    */ "我居然拿到这个啦——！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SPACEBALL_2 */ {
        /* Entry Scene   */ &scene_spaceball_2,
        /* Level Name    */ "空中击球手 2",
        /* Level Desc.   */ "别在意镜头缩放！\n"
                            "用心去击球！\n"
                            "不要依赖视觉！\n"
                            "眼泪也别擦啦～！",
        /* Level Icon    */ 52,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "你在干什么啦！",
            /* OK        */ "怎么能在这里结束！",
            /* SUPERB    */ "大家快看快看——！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* TAP_TRIAL */ {
        /* Entry Scene   */ &scene_tap_trial,
        /* Level Name    */ "踢踏舞",
        /* Level Desc.   */ "你是个女孩子。\n"
                            "要跟着旁边那群猴子\n"
                            "一起踩出踢踏节奏哦！",
        /* Level Icon    */ 6,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tap_trial_gfx_tables,
        /* Epilogue Text */ {
            #ifdef PARADISE
            /* TRY_AGAIN */ "Better tap out.",
            #else
            /* TRY_AGAIN */ "真不甘心呀。",
            #endif
            /* OK        */ "虽然有几处怪怪的啦！",
            /* SUPERB    */ "心情已经嗨到顶了！！"
        }
    },
    /* TAP_TRIAL_2 */ {
        /* Entry Scene   */ &scene_tap_trial_2,
        /* Level Name    */ "超级踢踏舞",
        /* Level Desc.   */ "猴子们强化啦！\n"
                            "你还能不能\n"
                            "跟上他们呢！？\n"
                            "别输呀〜！",
        /* Level Icon    */ 11,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tap_trial_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "不会吧——！",
            /* OK        */ "嗯〜… 感觉还差了那么一点…",
            /* SUPERB    */ "这股感觉，根本停不下来啦！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* MARCHING_ORDERS */ {
        /* Entry Scene   */ &scene_marching_orders,
        /* Level Name    */ "行军",
        /* Level Desc.   */ "现在开始行进。\n"
                            "擅自行动可是会\n"
                            "毁掉整个队伍的！\n"
							"好好努力吧。",
        /* Level Icon    */ 21,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "哇啊！被丢下啦！",
            /* OK        */ "今天的任务，是打扫卫生哦♪",
            /* SUPERB    */ "拯救外星人大成功！！"
        }
    },
    /* MARCHING_ORDERS_2 */ {
        /* Entry Scene   */ &scene_marching_orders_2,
        /* Level Name    */ "行军 2",
        /* Level Desc.   */ "现在开始行进。\n"
                            "这次的动作\n"
                            "有点复杂！\n"
                            "好好努力吧。",
        /* Level Icon    */ 20,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "这、这样可不行！唔〜嗯…",
            /* OK        */ "唔！舞步还得更帅才行！",
            /* SUPERB    */ "我居然还拿到了这种奖励！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* WIZARDS_WALTZ */ {
        /* Entry Scene   */ &scene_wizards_waltz,
        /* Level Name    */ "魔法使",
        /* Level Desc.   */ "你是一位魔法使。\n"
                            "给那个怕寂寞的\n"
                            "小姑娘送上一朵花吧。",
        /* Level Icon    */ 23,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_wizards_waltz_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "这种我不要啦〜，好可怕呀〜！",
            /* OK        */ "要是能开出更多花，我会更开心呀〜。",
            /* SUPERB    */ "哇——！我已经不寂寞啦！"
        }
    },
    /* BUNNY_HOP */ {
        /* Entry Scene   */ &scene_bunny_hop,
        /* Level Name    */ "跃兔",
        /* Level Desc.   */ "这只小白兔\n"
                            "最擅长跳跃啦。\n"
                            "踩着节拍，\n"
                            "一起渡过大海吧！",
        /* Level Icon    */ 24,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bunny_hop_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "我想回月亮上去〜！",
            /* OK        */ "落地失败啦…",
            /* SUPERB    */ "满分！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* FIREWORKS */ {
        /* Entry Scene   */ &scene_fireworks,
        /* Level Name    */ "烟火",
        /* Level Desc.   */ "说到夏天嘛，\n"
                            "果然还是烟火吧？\n"
                            "就让它绚丽多彩地\n"
                            #ifdef PARADISE
                            "sky with pretty colours!",
                            #else
                            "升上夜空吧！",
                            #endif
        /* Level Icon    */ 26,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_fireworks_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "咳咳咳… 失败。",
            /* OK        */ "做得相当不错嘛！",
            /* SUPERB    */ "说到烟火就交给我吧！！"
        }
    },
    /* POWER_CALLIGRAPHY */ {
        /* Entry Scene   */ &scene_power_calligraphy,
        /* Level Name    */ "节奏书法",
        /* Level Desc.   */ "要用毛笔来写日文。y\n"
                            "而你负责的，\n"
                            "只有最精彩的部分。",
        /* Level Icon    */ 28,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_power_power_calligraphy_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "呼〜… 不行呀。",
            /* OK        */ "再多享受一些书法的乐趣吧！",
            /* SUPERB    */ "书法这玩意儿也太带感啦！！"
        }
    },
    /* POWER_CALLIGRAPHY_2 */ { // this still kills me lmao
        /* Entry Scene   */ &scene_power_calligraphy,
        /* Level Name    */ "节奏书法 2",
        /* Level Desc.   */ "被捣蛋鬼偷走了\n"
                            "\n"
                            "\n"
                            "",
        /* Level Icon    */ 28,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_power_calligraphy_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "",
            /* OK        */ "",
            /* SUPERB    */ ""
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* TOSS_BOYS */ {
        /* Entry Scene   */ &scene_toss_boys,
        /* Level Name    */ "传球少年",
        /* Level Desc.   */ "感情超好的三人组，\n"
                            #ifdef PARADISE
                            "practising volleyball.\n"
                            #else
                            "一边互相喊话，\n"
                            #endif
                            "一边总是开心地\n"
                            "练习传球呢。",
        /* Level Icon    */ 30,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_toss_boys_gfx_tables,
        /* Epilogue Text */ {
            #ifdef PARADISE
            /* TRY_AGAIN */ "We've been thrown out!",
            #else
            /* TRY_AGAIN */ "完全不行啦〜！",
            #endif
            /* OK        */ "你肯定还能做得更好！",
            #ifdef PARADISE
            /* SUPERB    */ "Chuck World Championship, here we come!"
            #else
            /* SUPERB    */ "目标是拿下传球世界锦标赛冠军——！！"
            #endif
        }
    },
    /* TOSS_BOYS_2 */ {
        /* Entry Scene   */ &scene_toss_boys_2,
        /* Level Name    */ "传球少年 2",
        /* Level Desc.   */ "感情超好的三人组，\n"
                            #ifdef PARADISE
                            "practising volleyball.\n"
                            #else
                            "一边互相喊话，\n"
                            #endif
                            "一边总是开心地\n"
                            "练习传球呢。",
        /* Level Icon    */ 29,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_toss_boys_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "惨兮兮啦〜！",
            /* OK        */ "怎么能在这里结束！",
            #ifdef PARADISE
            /* SUPERB    */ "Three cheers for our star thrower!"
            #else
            /* SUPERB    */ "最强阵容诞生啦ー！！"
            #endif
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RAT_RACE */ {
        /* Entry Scene   */ &scene_rat_race,
        /* Level Name    */ "蹑鼠蹑脚",
        /* Level Desc.   */ "你是一只老鼠。\n"
                            "朝着最爱的奶酪\n"
                            "前进吧，\n"
                            "Stop & Go！！",
        /* Level Icon    */ 31,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rat_race_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "我想吃奶酪呀～…",
            /* OK        */ "奶酪真好吃呀。",
            /* SUPERB    */ "大家都吃到了，太好啦！"
        }
    },
    /* TRAM_PAULINE */ {
        /* Entry Scene   */ &scene_tram_pauline,
        /* Level Name    */ "小蹦与小床Tram & Pauline",
        /* Level Desc.   */ "小狐狸小蹦，\n"
                            "再加上小床的\n"
                            "杂技秀就要开始啦！",
        /* Level Icon    */ 32,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tram_pauline_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "大失败啦〜！！",
            /* OK        */ "有点不上不下呀…",
            /* SUPERB    */ "配合得稳稳的！！"
        }
    },
    /* SHOWTIME */ {
        /* Entry Scene   */ &scene_showtime,
        /* Level Name    */ "表演时间",
        /* Level Desc.   */ "企鹅小子们的\n"
                            "表演时间\n"
                            "要开始啦！\n"
                            "好耶好耶！",
        /* Level Icon    */ 36,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_showtime_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "客人们都生气了呢…",
            /* OK        */ "我们可不是只有这点水平…",
            /* SUPERB    */ "太好啦！！ 客人们玩得很开心耶——！！"
        }
    },
    /* SPACE_DANCE */ {
        /* Entry Scene   */ &scene_space_dance,
        /* Level Name    */ "太空之舞",
        /* Level Desc.   */ "这里是失重宇宙。\n"
                            "不过，还是来跳舞吧！\n"
                            "Let's Space Dance！",
        /* Level Icon    */ 40,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_space_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "黑、黑洞来啦——！！",
            /* OK        */ "真想像那颗星星一样闪闪发亮呀…",
            /* SUPERB    */ "我们就是太空超级巨星！！"
        }
    },
    /* COSMIC_DANCE */ {
        /* Entry Scene   */ &scene_cosmic_dance,
        /* Level Name    */ "宇宙之舞",
        /* Level Desc.   */ "代表宇宙的\n"
                            "舞者们！\n"
                            "那种利落动作\n"
                            "让人完全移不开眼呀！！",
        /* Level Icon    */ 16,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_cosmic_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "完、完蛋啦——！！",
            /* OK        */ "你们就只有这点本事吗？",
            /* SUPERB    */ "我们可是超级宇宙明星啊！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RAP_MEN */ {
        /* Entry Scene   */ &scene_rap_men,
        /* Level Name    */ "饶舌男",
        /* Level Desc.   */ "一对超酷的搭档\n"
                            "登场啦！\n"
                            "火热的\n"
                            "让人兴奋到不行！",
        /* Level Icon    */ 42,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rap_men_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "我们这样也太土了吧…",
            /* OK        */ "啧。总觉得状态不太对啊。",
            /* SUPERB    */ "以后也请多多关照啦——！！"
        }
    },
    /* RAP_WOMEN */ {
        /* Entry Scene   */ &scene_rap_women,
        /* Level Name    */ "饶舌女",
        /* Level Desc.   */ "那群饶舌男的\n"
                            "对手登场啦！\n"
                            "这可爱嗓音\n"
                            "简直让人神魂颠倒！",
        /* Level Icon    */ 15,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rap_women_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "不是这种感觉啦…",
            /* OK        */ "总觉得还是差了那么一点点…！",
            /* SUPERB    */ "对对对，就是这个就是这个啦——！！耶——咿！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* QUIZ_SHOW */ {
        /* Entry Scene   */ &scene_quiz_show,
        /* Level Name    */ "节奏问答",
        /* Level Desc.   */ "这是个很简单的问答，\n"
                            "只要猜中主持人\n"
                            "“敲了几下”\n"
                            "就可以啦。",
        /* Level Icon    */ 43,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_quiz_show_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "嘛，也就这样吧。",
            #ifdef PARADISE
            /* OK        */ "Must study... for next time... Zzz...",
            #else
            /* OK        */ "为了下次，学习、学习……Zzz",
            #endif
            /* SUPERB    */ "我居然赢得了环球旅行！"
        }
    },
    /* BON_ODORI */ {
        /* Entry Scene   */ &scene_bon_odori,
        /* Level Name    */ "The☆盂兰盆舞",
        /* Level Desc.   */ "跟着盂兰盆舞的\n"
                            "歌声，\n"
                            "“啪”地\n"
                            "拍手吧。",
        /* Level Icon    */ 35,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bon_odori_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "变冷了呢…",
            /* OK        */ "手持烟花，总让人有点伤感呢。",
            /* SUPERB    */ "啊，太有趣了！"
        }
    },
    /* BON_DANCE */ {
        /* Entry Scene   */ &scene_bon_dance,
        /* Level Name    */ "盆舞The☆Bon Dance",
        /* Level Desc.   */ "这是现代版的\n"
                            "盂兰盆舞！\n"
                            "超带感哦！\n"
                            "耶！",
        /* Level Icon    */ 17,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bon_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "别再跳了…",
            /* OK        */ "嗯，开始下雨了。",
            /* SUPERB    */ "盆舞真的太有意思了！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_1 */ {
        /* Entry Scene   */ &scene_remix_1,
        /* Level Name    */ "Remix 1",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 22,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix1_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的表现 ：猫咪零食级",
            /* OK        */ "本次的表现 ：早餐级",
            /* SUPERB    */ "本次的表现 ：竟然是晚餐级！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_2 */ {
        /* Entry Scene   */ &scene_remix_2,
        /* Level Name    */ "Remix 2",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 27,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的热度 ：独自练习的程度",
            /* OK        */ "本次的热度 ：开心传接球的程度",
            /* SUPERB    */ "本次的热度 ：精彩大赛的程度！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_3 */ {
        /* Entry Scene   */ &scene_remix_3,
        /* Level Name    */ "Remix 3",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 33,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix3_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的爱意 ： 好像已经心碎了…",
            /* OK        */ "本次的爱意 ： 非常友好的感觉呢♪",
            /* SUPERB    */ "本次的爱意 ： 甜甜蜜蜜——！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_4 */ {
        /* Entry Scene   */ &scene_remix_4,
        /* Level Name    */ "Remix 4",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 34,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix4_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的天气 ： 雨",
            /* OK        */ "本次的天气 ： 多云",
            /* SUPERB    */ "本次的天气 ：快乐的大晴天！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_5 */ {
        /* Entry Scene   */ &scene_remix_5,
        /* Level Name    */ "Remix 5",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 39,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix5_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的二人 ：被人搅和了！",
            /* OK        */ "本次的二人 ：今后可能有点不安……",
            /* SUPERB    */ "本次的二人 ：过上幸福生活啦♪"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_6 */ {
        /* Entry Scene   */ &scene_remix_6,
        /* Level Name    */ "Remix 6",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 2,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix6_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的内容 ： 有些孤单的感觉",
            /* OK        */ "本次的内容 ： 意外的感觉",
            /* SUPERB    */ "本次的内容 ： 难以置信的感觉！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_7 */ {
        /* Entry Scene   */ &scene_remix_7,
        /* Level Name    */ "Remix 7",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 19,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix7_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的恐龙 ：有点坏心眼",
            /* OK        */ "本次的恐龙 ： 暖呼呼的",
            /* SUPERB    */ "本次的恐龙 ： 太好玩了～！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_8 */ {
        /* Entry Scene   */ &scene_remix_8,
        /* Level Name    */ "Remix 8",
        /* Level Desc.   */ "想检验一下\n"
                            "你的实力吗？\n"
                            "让之前的经验\n"
                            "发挥作用吧！",
        /* Level Icon    */ 37,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix8_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "本次的兜风 ：真是的…",
            /* OK        */ "本次的兜风 ：看来还要开很久啊",
            /* SUPERB    */ "本次的兜风 ： 太爽快了！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CAFE */ {
        /* Entry Scene   */ &scene_cafe,
        #ifdef PARADISE
        /* Level Name    */ "Café Counselling",
        #else
        /* Level Name    */ "咖啡谈心",
        #endif
        /* Level Desc.   */ "最近状态怎么样？\n"
                            "要是有什么在意的事，\n"
                            "就来这里\n"
                            "聊一聊吧。",
        /* Level Icon    */ 45,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_cafe_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* RHYTHM_TOYS */ {
        /* Entry Scene   */ &scene_toys_menu,
        /* Level Name    */ "节奏玩具",
        /* Level Desc.   */ "收集奖牌，\n"
                            "去玩玩那些会发声的玩具吧！\n"
                            "有好几个哦。",
        /* Level Icon    */ 46,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_toys_menu_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* ENDLESS_GAMES */ {
        /* Entry Scene   */ &scene_endless_menu,
        /* Level Name    */ "无尽游戏",
        /* Level Desc.   */ "收集奖牌，\n"
                            "去挑战特别游戏吧！\n"
                            "有好几个哦。",
        /* Level Icon    */ 47,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_endless_menu_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* DRUM_LESSONS */ {
        /* Entry Scene   */ &scene_lessons_menu,
        /* Level Name    */ "击鼓课程",
        /* Level Desc.   */ "收集奖牌，\n"
                            "去上击鼓课程吧。\n"
                            "要变得更厉害哦！",
        /* Level Icon    */ 48,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_lessons_menu_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* STAFF_CREDIT */ {
        /* Entry Scene   */ &scene_staff_credit,
        /* Level Name    */ "制作人员",
        /* Level Desc.   */ "要是你愿意的话，\n"
                            "也来看看吧。\n"
                            "这里是这款游戏的\n"
                            "制作人员哦。",
        /* Level Icon    */ 49,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_staff_credit_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ NULL,
            /* OK        */ NULL,
            /* SUPERB    */ NULL
        }
    },
    /* LIVE_MENU */ {
        /* Entry Scene   */ &scene_drum_live,
        /* Level Name    */ "现场演出",
        /* Level Desc.   */ "要登台演出啦！\n"
                            "我觉得你的节奏感\n"
                            "已经很不错了，\n"
                            "放轻松就好～",
        /* Level Icon    */ 44,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_drum_live_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "阿姨：“下次再加油呀！”",
            /* OK        */ "老板：“你啊，还挺有天分哦”",
            /* SUPERB    */ "制作人：“要不要来我们这边试试？”"
        }
    },
    /* KARATE_MAN */ {
        /* Entry Scene   */ &scene_karate_man_extra,
        /* Level Name    */ "空手道家",
        /* Level Desc.   */ "向飞来的东西\n"
                            "按"CHAR_A_BUTTON_UTF8"出拳！\n"
                            "用干劲和气势\n"
                            "把它们打飞吧！",
        /* Level Icon    */ 54,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "比赛当天表现不太行。",
            /* OK        */ "比赛当天，感觉还挺不错的！",
            /* SUPERB    */ "比赛当天夺冠了！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RHYTHM_TWEEZERS */ {
        /* Entry Scene   */ &scene_rhythm_tweezers_extra,
        /* Level Name    */ "节奏脱毛",
        /* Level Desc.   */ "那讨厌的“毛”\n"
                            "总是不停地长出来！\n"
                            "不要被速度迷惑了\n"
                            "拔掉它，\n"
                            "拔掉它！",

        /* Level Icon    */ 55,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "毛长得太快了啊…",
            /* OK        */ "还真是挺难对付的毛啊",
            /* SUPERB    */ "嗯——清爽了！去看看花吧！",
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* MARCHING_ORDERS */ {
        /* Entry Scene   */ &scene_marching_orders_extra,
        /* Level Name    */ "行军",
        /* Level Desc.   */ "现在开始行进。\n"
                            "这次需要非常迅速地\n"
                            "做出判断。\n"
							"好好努力吧。",
        /* Level Icon    */ 56,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "撤退！撤退啦！！",
            /* OK        */ "啊，发现走失的小朋友了！",
            /* SUPERB    */ "救到走失的小朋友啦！太好了！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SPACEBALL */ {
        /* Entry Scene   */ &scene_spaceball_extra,
        /* Level Name    */ "空中击球手",
        /* Level Desc.   */ "别在意镜头缩放！\n"
                            "用心去击球！\n"
                            "不要依赖视觉，\n"
                            "把球打飞吧～！",
        /* Level Icon    */ 57,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "哇，不行啊～！",
            /* OK        */ "耶。",
            /* SUPERB    */ "成功啦——！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CLAPPY_TRIO */ {
        /* Entry Scene   */ &scene_clappy_trio_extra,
        /* Level Name    */ "啪叽啪叽三人组",
        /* Level Desc.   */ "我们要依次拍手哦！\n"
                            "你排在第３个。\n"
                            "仔细看好前面两人再拍哦！",
        /* Level Icon    */ 58,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_clappy_trio_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "哦～！",
            /* OK        */ "愉快的太空巡航。",
            /* SUPERB    */ "第一个到达未知星球！伟业！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_1 */ {
        /* Entry Scene   */ &scene_remix_1_extra,
        /* Level Name    */ "Extra Remix",
        /* Level Desc.   */ "这是额外关卡的Remix哦。\n"
                            "能跟上这个速度吗？\n"
                            "到最后都要\n"
                            "尽情享受哦！",
        /* Level Icon    */ 59,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix1_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "还有很长的路要走呢。",
            /* OK        */ "很普通呢～。啾啾。",
            /* SUPERB    */ "成长得很出色呢！好厉害！！"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    }
};
