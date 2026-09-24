// Level Entries Table
struct LevelData level_data_table[] = {
    /* KARATE_MAN */ {
        /* Entry Scene   */ &scene_karate_man,
        /* Level Name    */ "空手道家",
        /* Level Desc.   */ "向飞来的东西\n"
                            "按" CHAR_A_BUTTON_UTF8 "出拳\n"
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
                            "按" CHAR_A_BUTTON_UTF8 "出拳！\n"
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
        /* Level Name    */ "Marching Orders",
        /* Level Desc.   */ "Ready, march! Following\n"
                            "orders as a unit builds\n"
                            "your camaraderie.\n"
							"Also, rhythm.",
        /* Level Icon    */ 21,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Wait! You left without us!",
            /* OK        */ "Today's mission: Cleaning. ",
            /* SUPERB    */ "Mission success! We rescued the alien!"
        }
    },
    /* MARCHING_ORDERS_2 */ {
        /* Entry Scene   */ &scene_marching_orders_2,
        /* Level Name    */ "Marching Orders 2",
        /* Level Desc.   */ "Ready, march!\n"
                            "This mission requires\n"
                            "finesse and technique,\n"
                            "so march your best!",
        /* Level Icon    */ 20,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This is unacceptable...",
            /* OK        */ "I know we can perform better than that!",
            /* SUPERB    */ "Now THIS is a reward!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* WIZARDS_WALTZ */ {
        /* Entry Scene   */ &scene_wizards_waltz,
        /* Level Name    */ "Wizard's Waltz",
        /* Level Desc.   */ "There's a lonely girl\n"
                            "over there. Put your\n"
                            "flower power to good\n"
                            "use and cheer her up!",
        /* Level Icon    */ 23,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_wizards_waltz_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "... I'm scared!",
            /* OK        */ "These will look SO lovely when they bloom!",
            /* SUPERB    */ "Who could feel lonely with all these flowers?"
        }
    },
    /* BUNNY_HOP */ {
        /* Entry Scene   */ &scene_bunny_hop,
        /* Level Name    */ "Bunny Hop",
        /* Level Desc.   */ "This rabbit has an\n"
                            "impossible goal: to jump\n"
                            "to the moon! Can you\n"
                            "make her dream reality?",
        /* Level Icon    */ 24,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bunny_hop_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I'm not sure I thought this through...",
            /* OK        */ "Didn't quite stick the landing...",
            /* SUPERB    */ "A perfect landing! Who needs rockets?!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* FIREWORKS */ {
        /* Entry Scene   */ &scene_fireworks,
        /* Level Name    */ "Fireworks",
        /* Level Desc.   */ "It's not summertime\n"
                            "without fireworks!\n"
                            "Light them up to fill the\n"
                            #ifdef PARADISE
                            "sky with pretty colours!",
                            #else
                            "sky with pretty colors!",
                            #endif
        /* Level Icon    */ 26,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_fireworks_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Cough, cough... I think I blew it...",
            /* OK        */ "That wasn't half bad!",
            /* SUPERB    */ "I am THE go-to fireworks guy!"
        }
    },
    /* POWER_CALLIGRAPHY */ {
        /* Entry Scene   */ &scene_power_calligraphy,
        /* Level Name    */ "Power Calligraphy",
        /* Level Desc.   */ "Japanese calligraphy\n"
                            "requires grace, finesse,\n"
                            "and a shocking amount\n"
                            "of upper body strength.",
        /* Level Icon    */ 28,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_power_power_calligraphy_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Maybe I should stick with pencils...",
            /* OK        */ "Precision! Grace! What's not to like?",
            /* SUPERB    */ "Woo! Calligraphy party!"
        }
    },
    /* POWER_CALLIGRAPHY_2 */ { // this still kills me lmao
        /* Entry Scene   */ &scene_power_calligraphy,
        /* Level Name    */ "Power Calligraphy 2",
        /* Level Desc.   */ "haha unused\n"
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
        /* Level Name    */ "Toss Team",
        /* Level Desc.   */ "This trio of friends love\n"
                            #ifdef PARADISE
                            "practising volleyball.\n"
                            #else
                            "practicing volleyball.\n"
                            #endif
                            "Listen for their names\n"
                            "as they pass their ball!",
        /* Level Icon    */ 30,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_toss_boys_gfx_tables,
        /* Epilogue Text */ {
            #ifdef PARADISE
            /* TRY_AGAIN */ "We've been thrown out!",
            #else
            /* TRY_AGAIN */ "We've been tossed out!",
            #endif
            /* OK        */ "Next time, we'll toss better than the best!",
            #ifdef PARADISE
            /* SUPERB    */ "Chuck World Championship, here we come!"
            #else
            /* SUPERB    */ "Toss World Championship, here we come!"
            #endif
        }
    },
    /* TOSS_BOYS_2 */ {
        /* Entry Scene   */ &scene_toss_boys_2,
        /* Level Name    */ "Toss Team 2",
        /* Level Desc.   */ "This trio of friends love\n"
                            #ifdef PARADISE
                            "practising volleyball.\n"
                            #else
                            "practicing volleyball.\n"
                            #endif
                            "Today, they're training\n"
                            "harder than ever!",
        /* Level Icon    */ 29,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_toss_boys_2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Our spirits have been deflated...",
            /* OK        */ "We still have a long way to go!",
            #ifdef PARADISE
            /* SUPERB    */ "Three cheers for our star thrower!"
            #else
            /* SUPERB    */ "Three cheers for our star tosser!"
            #endif
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RAT_RACE */ {
        /* Entry Scene   */ &scene_rat_race,
        /* Level Name    */ "Rat Race",
        /* Level Desc.   */ "You are a rat. She is\n"
                            "a cat. You love cheese.\n"
                            "All the ingredients of a\n"
                            "tense encounter.",
        /* Level Icon    */ 31,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rat_race_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I guess we could try to eat the plate...",
            /* OK        */ "You know, I really like cheese. Like, a LOT.",
            /* SUPERB    */ "We'll have to start a family to eat all this!"
        }
    },
    /* TRAM_PAULINE */ {
        /* Entry Scene   */ &scene_tram_pauline,
        /* Level Name    */ "Tram & Pauline",
        /* Level Desc.   */ "Gather round, one and\n"
                            "all! Tram and Pauline's\n"
                            "acrobatic magic show\n"
							"is about to begin!",
        /* Level Icon    */ 32,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_tram_pauline_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We've transformed the show into a failure!",
            /* OK        */ "At least we only messed up half the show...",
            /* SUPERB    */ "We're the perfect duo!"
        }
    },
    /* SHOWTIME */ {
        /* Entry Scene   */ &scene_showtime,
        /* Level Name    */ "Showtime",
        /* Level Desc.   */ "Our plucky penguins\n"
                            "are ready for their act!\n"
                            "Get out there and wow\n"
                            "the crowd! It's showtime!",
        /* Level Icon    */ 36,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_showtime_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We've betrayed our audience...",
            /* OK        */ "I know we're capable of more than this...",
            /* SUPERB    */ "They loved us out there!"
        }
    },
    /* SPACE_DANCE */ {
        /* Entry Scene   */ &scene_space_dance,
        /* Level Name    */ "Space Dance",
        /* Level Desc.   */ "You want a dancing\n"
                            "challenge? Try dancing\n"
                            "in zero gravity!\n"
							"IN SPAAAAAAAAAACE!",
        /* Level Icon    */ 40,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_space_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Our despair has lead us into a black hole!",
            /* OK        */ "Let us aim for the stars!",
            /* SUPERB    */ "We are galactic superstars!"
        }
    },
    /* COSMIC_DANCE */ {
        /* Entry Scene   */ &scene_cosmic_dance,
        /* Level Name    */ "Cosmic Dance",
        /* Level Desc.   */ "These paragons of\n"
                            "dancing have mastered\n"
                            "their zero-G moves\n"
                            "and want to show off!",
        /* Level Icon    */ 16,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_cosmic_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We cannot go on like THIS!",
            /* OK        */ "Is that the best you guys can do?",
            /* SUPERB    */ "All aboard... for SPACE!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RAP_MEN */ {
        /* Entry Scene   */ &scene_rap_men,
        /* Level Name    */ "RAPMEN",
        /* Level Desc.   */ "The coolest rapping\n"
                            "duo has arrived! Their\n"
                            "hot rapping skills are\n"
                            "the talk of the town!",
        /* Level Icon    */ 42,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rap_men_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "We need more practice...",
            /* OK        */ "I think our tone was off.",
            /* SUPERB    */ "We're looking forward to hearing from you again!"
        }
    },
    /* RAP_WOMEN */ {
        /* Entry Scene   */ &scene_rap_women,
        /* Level Name    */ "RAPWOMEN",
        /* Level Desc.   */ "The RAPMEN have\n"
                            "some new rivals!\n"
                            "Don't be deceived\n"
                            "by their cute voices!",
        /* Level Icon    */ 15,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rap_women_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "No... This isn't right.",
            /* OK        */ "I know we can rap better than this!",
            /* SUPERB    */ "Yes, yes, YES! We've got it!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* QUIZ_SHOW */ {
        /* Entry Scene   */ &scene_quiz_show,
        /* Level Name    */ "Quiz Show",
        /* Level Desc.   */ "Play a quiz where you\n"
                            "copy the host's pattern.\n"
                            "Seems simple, right?\n"
                            "Simple, but not easy.",
        /* Level Icon    */ 43,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_quiz_show_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I can do better... I can do better...",
            #ifdef PARADISE
            /* OK        */ "Must study... for next time... Zzz...",
            #else
            /* OK        */ "Gotta study... for next time... Zzz...",
            #endif
            /* SUPERB    */ "I won the grand prize! A world tour!"
        }
    },
    /* BON_ODORI */ {
        /* Entry Scene   */ &scene_bon_odori,
        /* Level Name    */ "The☆Bon Odori",
        /* Level Desc.   */ "Let's celebrate the\n"
                            "Japanese Bon Festival!\n"
                            "Clap along as they sing\n"
                            "their traditional song!",
        /* Level Icon    */ 35,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bon_odori_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I feel so cold...",
            /* OK        */ "Oh... the quaint fizzle of a sparkler...",
            /* SUPERB    */ "That was so much fun! I can't wait for next year!"
        }
    },
    /* BON_DANCE */ {
        /* Entry Scene   */ &scene_bon_dance,
        /* Level Name    */ "The☆Bon Dance",
        /* Level Desc.   */ "The Bon Festival has\n"
                            "a modern-day style!\n"
                            "Clap along to this\n"
                            "new arrangement!",
        /* Level Icon    */ 17,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_bon_dance_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "It's over...",
            /* OK        */ "When did it start raining?",
            /* SUPERB    */ "Our new Bon Dance is a lot of fun!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_1 */ {
        /* Entry Scene   */ &scene_remix_1,
        /* Level Name    */ "Remix 1",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "Stage 1's games have\n"
                            "all been remixed!\n"
                            "Think you can beat it?",
        /* Level Icon    */ 22,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix1_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "You were as good as... a cat's snack.",
            /* OK        */ "You were as good as... an ordinary breakfast.",
            /* SUPERB    */ "You were as good as... why, a delicious dinner!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_2 */ {
        /* Entry Scene   */ &scene_remix_2,
        /* Level Name    */ "Remix 2",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got a lively\n"
                            "atmosphere perfect\n"
                            "for dance lessons!",
        /* Level Icon    */ 27,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix2_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "That was as lively as... playing ball by yourself.",
            /* OK        */ "That was as lively as... a pleasant game of catch.",
            /* SUPERB    */ "That was as lively as... a huge baseball tournament!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_3 */ {
        /* Entry Scene   */ &scene_remix_3,
        /* Level Name    */ "Remix 3",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got an\n"
                            "adorable love song with\n"
                            "adorable love lyrics!",
        /* Level Icon    */ 33,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix3_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Their love ended in... heartbreak...",
            /* OK        */ "Their love ended in... a good friendship.",
            /* SUPERB    */ "Their love ended in... a tender marriage!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_4 */ {
        /* Entry Scene   */ &scene_remix_4,
        /* Level Name    */ "Remix 4",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got a casual,\n"
                            "easygoing vibe, like a\n"
                            "nice, pleasant stroll...",
        /* Level Icon    */ 34,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix4_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Today's forecast... raining buckets.",
            /* OK        */ "Today's forecast... very cloudy.",
            /* SUPERB    */ "Today's forecast... clear skies all day!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_5 */ {
        /* Entry Scene   */ &scene_remix_5,
        /* Level Name    */ "Remix 5",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This one's got some\n"
                            "melancholic lyrics.\n"
                            "Try to keep your cool!",
        /* Level Icon    */ 39,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix5_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This couple is... in trouble!",
            /* OK        */ "This couple is... a little nervous...",
            /* SUPERB    */ "This couple is... living their happy-ever-after!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_6 */ {
        /* Entry Scene   */ &scene_remix_6,
        /* Level Name    */ "Remix 6",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "Every game you've\n"
                            "played is here! Show\n"
                            "us what you've learned!",
        /* Level Icon    */ 2,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix6_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your fish tank is... pretty sparse.",
            /* OK        */ "Your fish tank is... unique for sure!",
            /* SUPERB    */ "Your fish tank is... unbelievable!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_7 */ {
        /* Entry Scene   */ &scene_remix_7,
        /* Level Name    */ "Remix 7",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "A lot of the remixes\n"
                            "make a comeback here!\n"
                            "It's a remix remix!",
        /* Level Icon    */ 19,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix7_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your Jurassic visit was... terrifying!",
            /* OK        */ "Your Jurassic visit was... rather tame.",
            /* SUPERB    */ "Your Jurassic visit was... too much fun!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_8 */ {
        /* Entry Scene   */ &scene_remix_8,
        /* Level Name    */ "Remix 8",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This special remix is a\n"
                            "real challenge! Show\n"
                            "us what you've learned!",
        /* Level Icon    */ 37,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix8_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Your road trip was... oh boy...",
            /* OK        */ "Your road trip was... a little long.",
            /* SUPERB    */ "Your road trip was... absolutely spectacular!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CAFE */ {
        /* Entry Scene   */ &scene_cafe,
        #ifdef PARADISE
        /* Level Name    */ "Café Counselling",
        #else
        /* Level Name    */ "Café Counseling",
        #endif
        /* Level Desc.   */ "How are you feeling?\n"
                            "If something's on your\n"
                            "mind, feel free to\n"
                            "come and talk.",
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
        /* Level Name    */ "Rhythm Toys",
        /* Level Desc.   */ "Collect medals to\n"
                            "play with some\n"
                            "Rhythm Toys!\n"
                            "Check them out!",
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
        /* Level Name    */ "Endless Games",
        /* Level Desc.   */ "Collect medals to\n"
                            "unlock special\n"
                            "Endless Games!\n"
                            "Check them out!",
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
        /* Level Name    */ "Drum Lessons",
        /* Level Desc.   */ "Collect medals to take\n"
                            "some Drum Lessons.\n"
                            "You could become\n"
                            "a master drummer!",
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
        /* Level Name    */ "Staff Credits",
        /* Level Desc.   */ "Here's the staff who\n"
                            "helped develop\n"
                            "this game. Feel free\n"
                            "to take a look!",
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
        /* Level Name    */ "Concert",
        /* Level Desc.   */ "We're hosting a\n"
                            "concert! You've got\n"
                            "good rhythm, right?\n"
                            "So give it a try!",
        /* Level Icon    */ 44,
        /* Level Type    */ LEVEL_TYPE_BONUS,
        /* Epilogue GFX  */ epilogue_drum_live_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "The cleaner says... \"I know you can do it, keep at it!\"",
            /* OK        */ "The owner says... \"You've got great skills, you know!\"",
            /* SUPERB    */ "The producer says... \"You should play at our place, too!\""
        }
    },
    /* KARATE_MAN */ {
        /* Entry Scene   */ &scene_karate_man_extra,
        /* Level Name    */ "Karate Man",
        /* Level Desc.   */ "We've increased the\n"
                            "speed! Do your best,\n"
                            "as we throw some more\n"
                            "stuff for you to punch.",
        /* Level Icon    */ 54,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_karate_man_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "The tournament didn't go so well...",
            /* OK        */ "I may not have won, but I did really well!",
            /* SUPERB    */ "I won the tournament and took home the gold!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* RHYTHM_TWEEZERS */ {
        /* Entry Scene   */ &scene_rhythm_tweezers_extra,
        /* Level Name    */ "Rhythm Tweezers",
        /* Level Desc.   */ "My roots are showing!\n"
                            "Don't let the speed trip\n"
                            "you up! Pluck them off!\n",
        /* Level Icon    */ 55,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_rhythm_tweezers_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "I can't pluck anything at this speed!",
            /* OK        */ "These hairs are pretty tough to pluck.",
            /* SUPERB    */ "Look at those flowers! They're so relaxing..."
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* MARCHING_ORDERS */ {
        /* Entry Scene   */ &scene_marching_orders_extra,
        /* Level Name    */ "Marching Orders",
        /* Level Desc.   */ "Ready, march!\n"
                            "This mission will require\n"
                            "quick marching, so stay\n"
							"focused!",
        /* Level Icon    */ 56,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_marching_orders_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "MONSTER! Retreat! Retreat!",
            /* OK        */ "Ah, there's the lost puppy!",
            /* SUPERB    */ "We rescued the lost puppy! Hooray!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* SPACEBALL */ {
        /* Entry Scene   */ &scene_spaceball_extra,
        /* Level Name    */ "Spaceball",
        /* Level Desc.   */ "Ignore the camera's\n"
                            "zooms! Make the ball\n"
                            "zoom away! Don't fall\n"
                            "behind! Let it fly!",
        /* Level Icon    */ 57,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_spaceball_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Ahhh! Nooooooo!",
            /* OK        */ "Graaaah!",
            /* SUPERB    */ "A home run! I did it!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* CLAPPY_TRIO */ {
        /* Entry Scene   */ &scene_clappy_trio_extra,
        /* Level Name    */ "The Clappy Trio",
        /* Level Desc.   */ "Clap your hands in\n"
                            "order! You're the third\n"
                            "clapper. Watch out\n"
							"for your fast friends!",
        /* Level Icon    */ 58,
        /* Level Type    */ LEVEL_TYPE_GAME,
        /* Epilogue GFX  */ epilogue_clappy_trio_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "Wait! Don't leave without us!",
            /* OK        */ "This is one nice space cruise!",
            /* SUPERB    */ "I've discovered a new planet! Stellar!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    },
    /* REMIX_1 */ {
        /* Entry Scene   */ &scene_remix_1_extra,
        /* Level Name    */ "Extra Remix",
        /* Level Desc.   */ "Let's test your skills!\n"
                            "This remix is faster\n"
                            "than ever!\n"
                            "Think you can beat it?",
        /* Level Icon    */ 59,
        /* Level Type    */ LEVEL_TYPE_REMIX,
        /* Epilogue GFX  */ epilogue_remix1_extra_gfx_tables,
        /* Epilogue Text */ {
            /* TRY_AGAIN */ "This is going to take a while...",
            /* OK        */ "Just a normal chick. Cheep-Cheep!",
            /* SUPERB    */ "You've grown splendidly! You look downright dignified!"
        },
        /* Level Flags   */ LEVEL_DATA_FLAG_IS_EXTRA | LEVEL_DATA_FLAG_NO_PRACTICE
    }
};
