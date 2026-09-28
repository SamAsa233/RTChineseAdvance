/* 中文文本：本文件采用译文包中 stage 5 的已校对条目。
 * 字符串中的 \n 是游戏画面换行；相邻引号只是方便阅读源码。
 * 未校对或未定位的条目见 text/zh_hans/TODO_未校对.md。 */
#include "reading_materials.h"

// [D_089d7e74] Reading Material Table
struct ReadingMaterial reading_material_table[TOTAL_READING_MATERIALS] = {
    /* WELCOME ("Rhythm Tengoku Welcome") */ {
        /* TITLE ---------------------------------------------------------- */
            "欢迎来到节奏天国！",
        /* BODY ----------------------------------------------------------- */
            // 阶段 5 已校对：两地区的英文游戏名不同，中文都用《节奏天国》。
            // 保留原 #ifdef；相邻引号只分隔源码，\n 才是译文包中的画面换行。
            // TODO 未校对：资料室阅读页的中文自动折行和分页仍需实机核验。
            #ifdef PARADISE
            "问候语\n"
            "非常感谢你购买《节奏天国》。啊，还是说，是跟朋友借来的？"
            "难、难不成，是、是二手的吗！？\n"
            "嘛，先不提那个。能让你对这款游戏产生兴趣，我们深感荣幸。感谢与你相遇！\n"
            "如果你能长长久久地玩得开心，那就太让人高兴啦！！\n"
            "谢谢你。"
            #else
            "问候语\n"
            "非常感谢你购买《节奏天国》。啊，还是说，是跟朋友借来的？"
            "难、难不成，是、是二手的吗！？\n"
            "嘛，先不提那个。能让你对这款游戏产生兴趣，我们深感荣幸。感谢与你相遇！\n"
            "如果你能长长久久地玩得开心，那就太让人高兴啦！！\n"
            "谢谢你。"
            #endif
            ,
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    },

    /* MANUAL ("Handling Instructions") */ {
        /* TITLE ---------------------------------------------------------- */
            "使用说明书",
        /* BODY ----------------------------------------------------------- */
            "这款游戏的玩法\n"
            "该怎么说呢，这其实不是那种非得写上一大堆说明的复杂游戏哦～。所以，这里其实也没什么好写的啦。\n"
            "啊，对了，重点是要跟着音乐一起摇摆，所以放开来玩会更好！强烈推荐！\n"
            "差不多就是这样。请多关照～。",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* CAFE ("More Than a Barista") */ {
        /* TITLE ---------------------------------------------------------- */
            "听店长讲讲",
        /* BODY ----------------------------------------------------------- */
            "我经营着一家咖啡店。嗯，简单来说，就是这家店的老板。店里的生意嘛，托老顾客们的福，还算过得去。啊，对了，有件事得先说清楚，我是一只狗。\n"
            "来我们店里的客人，多半都很喜欢音乐呢。尤其是不少人对节奏特别讲究。甚至还有客人完成过好多次“完美挑战”，真是让人吃惊哦！\n"
            "不过嘛，平时我虽然像这样经营着咖啡店，其实这只是我的伪装。本来的我嘛……说出来怪不好意思的，其实是戴着狗狗专用耳机，到处撒欢的那种！果然啊，少了那股劲头，日子就过不下去呢。真是拿自己没办法。哈哈哈。\n"
            "我也常常会去各种地方玩，如果你看到我，记得摸摸我哦～！\n"
            "那，下回见。",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_TWEEZERS ("Letter to the Editor") */ {
        /* TITLE ---------------------------------------------------------- */
            "拔毛来稿",
        /* BODY ----------------------------------------------------------- */
            "我是个种菜的大叔。最近啊，我家的蔬菜居然开始长胡子了！又诡异又吓人，这样根本卖不出去，所以我就想把它们的胡子拔掉，可怎么拔都拔不干净。我正发愁的时候，想着换换心情，就一边听音乐一边跟着节奏给蔬菜拔毛。结果居然！拔得干干净净！而且还莫名有点开心！音乐的力量真是太厉害了。大家也一定要试试看给蔬菜拔毛哦！",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* NIGHT_WALK ("Night Walk Riddle") */ {
        /* TITLE ---------------------------------------------------------- */
            "夜空漫步情报",
        /* BODY ----------------------------------------------------------- */
            #ifdef PARADISE
	        "There's this strange fellow who you might recognise\n"
            #else
	        "There's this strange fellow who you might recognize\n"
            #endif
            "from Night Walk.\n"
            "He seems to really love music.\n"
            "\n"
            "Apparently he's worked with music before,\n"
            "and landed a role in this game through connections.\n"
            "\n"
            "\n"
            "\n"
            "I ran into him in the city one time.\n"
            "\n"
            "All he said was \"I love music!\", and then just\n"
            "disappeared up some stairs.\n"
            "I wonder if I'll ever meet that music-loving guy again.\n"
            "\n"
            "Come to think of it, I don't even know his name...\n"
            "\n"
            "\n"
            "Okay, time for a quiz!\n"
            "His name is...\n"
            "\n"
            "\001C" "\0031" "\001m" "①②③④-④③⑤\n"
            "\001L" "\0030" "\001s" "\n"
            "Answer which letters go in each of the numbers!\n"
            "If you answer correctly, you'll be able to read the\n"
            "following text!\n"
            "\n"
            "\n"
            "\0031" "\001m" "\001C" "Quiz Show's Secret\n"
            "\0030" "\001s" "\001C" "\n"
            "In this g" "\0031" "\001m" "③" "\0030" "\001s" "me, the " "\0031" "\001m" "①" "\0030" "\001s" "la" "\0031" "\001m" "④" "\0030" "\001s" "er has to m" "\0031" "\001m" "③" "\0030" "\001s" "tch\n"
            "\0030" "\001s" "the host's " "\0031" "\001m" "⑤" "\0030" "\001s" "umber of button " "\0031" "\001m" "①" "\0030" "\001s" "resses. But\n"
            "\0030" "\001s" "if you mash the butto" "\0031" "\001m" "⑤" "\0030" "\001s" "s rea" "\0031" "\001m" "②②" "\0030" "\001s" "y f" "\0031" "\001m" "③" "\0030" "\001s" "st instead,\n"
            "\0030" "\001s" "somethi" "\0031" "\001m" "⑤" "\0030" "\001s" "g interesting can h" "\0031" "\001m" "③" "\0030" "\001s" "ppen.\n"
            "\0030" "\001s" "It's nothing crazy or an" "\0031" "\001m" "④" "\0030" "\001s" "thing, but it's neat!",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* SPACEBALL ("Inside Spaceball") */ {
        /* TITLE ---------------------------------------------------------- */
            "空中击球手快报",
        /* BODY ----------------------------------------------------------- */
            "我们现在来采访一下正在宇宙空间活跃中的空中击球手先生！\n"
            "Q．这个赛季状态怎么样？\n"
            "A．因为我一直都在吃饭团，状态好极了！\n"
            "Q．目标是什么？\n"
            "A．绝不能断了饭团！就是这个。\n"
            "Q．有女朋友吗？\n"
            "A．有。\n"
            "Q．她最拿手的料理是什么？\n"
            "A．饭团！\n"
            "Q．为什么在游戏里要戴那种头套呢？\n"
            "A．你在说什么？\n"
            "Q．那为什么会穿兔子之类的服装呢？\n"
            "A．不知道。\n"
            "Q．请正面回答问题！\n"
            "A．时间到了，先失陪了。\n"
            "说完这些，空中击球手先生就离席了。看来其中似乎另有隐情。以上，就是来自宇宙空间的报道。",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* MECHANICAL_HORSE ("Mechanical Horse's Story") */ {
        /* TITLE ---------------------------------------------------------- */
            "骑马机开发秘闻",
        /* BODY ----------------------------------------------------------- */
            // 阶段 5 已校对 reading_horse_machine_story；地区版原文整篇只差英文称谓，保留两个完整分支。
            // TODO 未校对：资料室自动折行和分页位置仍需实机查看。
            #ifdef PARADISE
            "我们采访了参与开发奖牌奖励“骑马机”的 F 先生，请他谈了谈开发时的故事。\n"
            "F 先生：“开发是从一个念头开始的，就是想把让马奔跑起来时那种畅快感传达出去。”\n"
            "虽然说得简单，却能听出 F 先生那股认真的热情。\n"
            "F 先生：“不过，一旦想让它同时满足作为游戏的各种条件，就怎么也找不到方向，甚至也有过一度想放弃开发的时候。”\n"
            "F 先生也经历过相当艰难的阶段。想在既定框架里做出自己真正想做的东西，果然不是件容易事。\n"
            "F 先生：“但只要玩过的人哪怕只多开心那么一点点，之前那些辛苦也就全都值了！”\n"
            "F 先生真是处处为玩家着想。我们也期待他今后的作品。非常感谢。",
            #else
            "我们采访了参与开发奖牌奖励“骑马机”的 F 先生，请他谈了谈开发时的故事。\n"
            "F 先生：“开发是从一个念头开始的，就是想把让马奔跑起来时那种畅快感传达出去。”\n"
            "虽然说得简单，却能听出 F 先生那股认真的热情。\n"
            "F 先生：“不过，一旦想让它同时满足作为游戏的各种条件，就怎么也找不到方向，甚至也有过一度想放弃开发的时候。”\n"
            "F 先生也经历过相当艰难的阶段。想在既定框架里做出自己真正想做的东西，果然不是件容易事。\n"
            "F 先生：“但只要玩过的人哪怕只多开心那么一点点，之前那些辛苦也就全都值了！”\n"
            "F 先生真是处处为玩家着想。我们也期待他今后的作品。非常感谢。",
            #endif
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_train_gfx_table,
            /* BGM */ &reading_style_train_bgm
        /* ---------------------------------------------------------------- */
    },

    /* MARCHING_ORDERS ("Marcher's Diary") */ {
        /* TITLE ---------------------------------------------------------- */
            "行军活动记录",
        /* BODY ----------------------------------------------------------- */
            "4 月 16 日 今天正式入队！我要努力帮上大家的忙！\n"
            "4 月 20 日 今天踏步没跟大家踩齐，被队长骂了。\n"
            "4 月 28 日 今天在车站前打扫卫生。一位不认识的老奶奶说“谢谢你们打扫得这么干净”，还给了我糖。好开心！\n"
            "5 月 4 日 最近总觉得没精神。这就是所谓的五月病吗？再不打起精神，怕是要被大家落下了…\n"
            "5 月 8 日 队长有点不对劲…他说昨天在宇宙里跟兔子玩。真的没事吗…？\n"
            "5 月 16 日 最近总能看见跟队长一模一样的人。\n"
            "是我看错了吗？\n"
            "5 月 22 日 我看见了。队长他…\n"
            "活动记录到这里就结束了。\n"
            "队长身上究竟发生了什么！？",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RAP_MEN ("Rap Report") */ {
        /* TITLE ---------------------------------------------------------- */
            "某个电台节目",
        /* BODY ----------------------------------------------------------- */
            // 阶段 5 已校对 reading_radio_story；第 19、20 句原是两种地区游戏名，中文两侧同为《节奏天国》。
            // TODO 未校对：资料室自动折行和分页位置仍需实机查看。
            "嗨大家好啊！我是 DJ SALU！\n"
            "今天也请来了超棒的嘉宾。就是 Rap Men（RM）两位成员！请多关照啦～！\n"
            "RM“啊，你好，我们是 Rap Men。”\n"
            "DJ“新歌很不错嘛～！”\n"
            "RM“那可不～。你听得出来啊？”\n"
            "DJ“嗯嗯，太棒了！”\n"
            "RM“不过啊，我们有个烦恼。”\n"
            "DJ“诶！？那、那个… 是、是什么？”\n"
            "RM“最近冒出来一群山寨货，叫什么 Rap Women。”\n"
            "DJ“真的假的！？”\n"
            "RM“嗯。而且她们还偷偷吃掉了我们放在休息室里的零食。”\n"
            "DJ“诶ー！这也太受打击了…”\n"
            "RM“而且还留了张字条。”\n"
            "DJ“写了什么？”\n"
            "RM“写着‘饭后甜点最棒啦’。”\n"
            "DJ“这也太大胆了吧…”\n"
            "RM“对吧？气得我们当场就喊出来了。”\n"
            "DJ“是喊‘零食没啦～！’那句吗？”\n"
            "RM“！？你怎么知道的？”\n"
            #ifdef PARADISE
            "DJ“因为我也在玩《节奏天国》嘛！那么这里先插播一段广告～”\n"
            "CM“想提升节奏感吗…《节奏天国》！快去买哦！”\n"
            #else
            "DJ“因为我也在玩《节奏天国》嘛！那么这里先插播一段广告～”\n"
            "CM“想提升节奏感吗…《节奏天国》！快去买哦！”\n"
            #endif
            "完",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* BON_ODORI ("Lyrics - The Bon Odori") */ {
        /* TITLE ---------------------------------------------------------- */
            "歌词卡片①",
        /* BODY ----------------------------------------------------------- */
            // TODO 未校对：reading_lyrics_1 译文包未到 stage 5，暂留原文。
            "The☆Bon Odori\n"
            "\n"
            "Vocals: Ami Tokito\n"
            "Lyrics/Music: Tsunku♂\n"
            "Arrangement: Koichi Yuasa (The☆Bon Odori) /\n"
            "Kaoru Okubo (The☆Bon Dance)\n"
            "Translation: castIeRook, Mizuka Lover\n"
            "\n"
            "(This song appears in The☆Bon Odori.)\n"
            "Haa~\n"
            "            Hanabi agare ba~\n"
            "Haa~ Ah~\n"
            "            Kansei agaru~\n"
            "\n"
            "Haa~\n"
            "            Ninki agare ba~\n"
            "Haa~ Ah~\n"
            "            Kyuuryou agaru~\n"
            "Matsuri da wasshoi!\n"
            "Nippon chuu ga wasshoi!\n"
            "\n"
            "Sore hikkuri kaette Dondo pan pan\n"
            "Haa~ Bon Odori~\n"
            "\n"
            "Haa~\n"
            "            Ame ga agare ba~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Yagura ni agaru~\n"
            "\n"
            "Hora! Matsuri da wasshoi!\n"
            "Korezo made in JaPAN\n"
            "\n"
            "Sore hikkuri kaette Dondo pan pan\n"
            "Haa~ Bon Odori~\n"
            "----------------------------------------------\n"
            "Haa~\n"
            "            Oh when the fireworks fly~\n"
            "Haa~ Ah~\n"
            "            Let's send our cheers to the sky~\n"
            "\n"
            "Haa~\n"
            "            If we perform for more eyes~\n"
            "Haa~ Ah~\n"
            "            We'll know our profits will rise~\n"
            "Time for celebration!\n"
            "All throughout the nation!\n"
            "\n"
            "So let's all turn around and Dondo pan pan\n"
            "Haa~ Bon Odori~\n"
            "\n"
            "Haa~\n"
            "            Oh when the rain clears away~\n"
            "\n"
            "Haa~ Ah~\n"
            "            Walk up the platform and play~\n"
            "\n"
            "Come on! Let's all cheer for Obon!\n"
            "The one and only, that's made in JaPAN\n"
            "\n"
            "So let's all turn around and Dondo pan pan\n"
            "Haa~ Bon Odori~\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* REMIX3 ("Lyrics - Honey Sweet Angel of Love") */ {
        /* TITLE ---------------------------------------------------------- */
            "歌词卡片②",
        /* BODY ----------------------------------------------------------- */
            "恋爱的Honey Sweet～Angel\n"
            "演唱：時東ぁみ\n"
            "作词/作曲：淳君\n"
            "编曲：鈴木Daichi秀行\n"
            "是爱情的魅力 是爱情不思议\n"
            "是爱情形式不移 是爱的nuance\n"
            "Honey Sweet～Angel\n"
            "反过来说的话 「温情」是什么呀！\n"
            "我可 是完全 不 明白 啊\n"
            "而且另一方面 再换一个说法\n"
            "温情 好像是 简单的 喜欢把\n"
            "酸酸甜甜像品味 草莓牛奶滋味\n"
            "就那种感觉过后 在我们之间\n"
            "I LOVE YOU\n"
            "是爱情的魅力 是爱情不思议\n"
            "是爱情形式不移 是爱的nuance\n"
            "Honey Sweet～Angel",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* REMIX5 ("Lyrics - WISH Can't Wait For You") */ {
        /* TITLE ---------------------------------------------------------- */
            "歌词卡片③",
        /* BODY ----------------------------------------------------------- */
            "WISH - Can't Wait for You\n"
            "\n"
            "English Vocals: Roxby\n"
            "Japanese Vocals: Soshi Tanaka\n"
            "Lyrics/Music: Tsunku♂\n"
            "Arrangement: Koichi Yuasa\n"
            "Translation: castIeRook\n"
            "\n"
            "(This song appears in Remix 5.)\n"
            "I can't keep waiting forever\n"
            "Tonight we'll say our goodbyes\n"
            "I wish I loved you more when you were by my side\n"
            "The lonely nights, they bring back memories that\n"
            "made it all so bright\n"
            "I'm lost in thought at times that leave me longing\n"
            "\n"
            "\n"
            "\n"
            "When we met under the city lights\n"
            "Like a flame, burning hot and bright\n"
            "\n"
            "Without a care, just a warm embrace\n"
            "It was love without a doubt\n"
            "\n"
            "But this act was just a fleeting play\n"
            "Our hearts started to drift away\n"
            "\n"
            "Our kisses faded and I don't know how\n"
            #ifdef PARADISE
	        "I didn't realise 'til now\n"
            #else
	        "I didn't realize 'til now\n"
            #endif
            "\n"
            "My dreams are clouding up into a haze\n"
            "And you're clouding up into a haze\n"
            "There's a blaze in my chest\n"
            "All this pain, I can't rest\n"
            "And I can't take it anymore!\n"
            "\n"
            "I can't keep waiting forever\n"
            "Tonight we'll say our goodbyes\n"
            "I wish I loved you more when you were by my side\n"
            "The lonely nights, they bring back memories that\n"
            "made it all so bright\n"
            "I'm lost in thought at times that leave me longing\n"
            "\n"
            "\n"
            "\n"
            "I can't keep waiting forever\n"
            "Tonight we'll say our goodbyes\n"
            "To dreams we could have reached if you\n"
            "were by my side\n"
            "Don't you recall the place that we would stay\n"
            "before the light had died?\n"
            "The empty space you left will keep me longing\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* REMIX8 ("The Final Letter") */ {
        /* TITLE ---------------------------------------------------------- */
            "最后的通告",
        /* BODY ----------------------------------------------------------- */
            // 阶段 5 已校对 reading_final_story；末尾两行英文署名合为一行中文，保留右对齐控制码。
            // TODO 未校对：资料室自动折行和分页位置仍需实机查看。
            "来自神秘节奏组织的最后通告。\n"
            #ifdef PARADISE
            "“恭喜你！！Remix 8 的完美达成，简直太棒了～！……不过，这种兴高采烈的祝贺还是先免了。你在《节奏天国》里，的确留下了非常出色的成绩。这是谁都无法否认的事实，我们也完全认可。你真的很厉害！简直厉害得不得了！！……虽然一高兴就想这么大声夸你，不过热热闹闹地称赞你这件事，也先放一放吧。\n"
            #else
            "“恭喜你！！Remix 8 的完美达成，简直太棒了～！……不过，这种兴高采烈的祝贺还是先免了。你在《节奏天国》里，的确留下了非常出色的成绩。这是谁都无法否认的事实，我们也完全认可。你真的很厉害！简直厉害得不得了！！……虽然一高兴就想这么大声夸你，不过热热闹闹地称赞你这件事，也先放一放吧。\n"
            #endif
            "这次你在这款游戏里体会到的节奏，其实还只是节奏界的一小部分而已。如果你因此对节奏产生了更大的兴趣，那就请借这个机会，尽情投入进去吧！因为一旦进入状态，感觉真的非常棒！！这点我可是强烈推荐！！……虽然我一兴奋又忍不住想这么说，不过这种兴冲冲的推荐，也还是先收住吧。\n"
            "我们是认真的。\n"
            "我们是真心希望你，能一直跟着节奏尽情投入！\n"
            "我们相信，能够引领这个节奏世界的人就是你！不如说，除了你，我们已经没法相信别人了！！\n"
            "因为你就是最棒的嘛！！\n"
            "谢谢你玩这款游戏！”\n"
            "\001R" "神秘节奏组织代表　太空大叔",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    },

    /* NINJA_BODYGUARD ("The Ninja Scroll") */ {
        /* TITLE ---------------------------------------------------------- */
            "忍者卷轴",
        /* BODY ----------------------------------------------------------- */
            "各位，初次见面。我叫田中。前阵子，我在后头的仓库里找到了一卷古老的卷轴。上面是这么写的。\n"
            "“看到这卷轴的你啊。你并不是偶然找到它的。为了让它一定会被你找到，我早已施下了忍术。明白吗？没错，写下这些话的我是一名忍者，同时也是你的祖先。\n"
            "前些日子，我从箭雨之中保护了我的主人，也就是主公。当然，是拼了命去守护。完成那桩大事的那一夜，我做了一个梦。梦里有个年轻男子。那是个背离世俗、桀骜不驯的年轻人。根据算命婆婆所说，那个年轻人，似乎就是你。而且你也像我一样，为了守护某个人而拼上性命。是个女性。据说，那位女性正是主公的后代。你忽然看到这样的卷轴，可能一时半会儿也没什么真实感，但我还是希望，你能一直守护着那位女性。”\n"
            "如今，我心里确实有这样一位女性。她就是前些天差点遭人用弹弓瞄准射击，被我拼命救下的那位。虽说我和她今后未必会怎么样，不过这次，我倒想乖乖中一回祖先的忍术……",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_cherry_gfx_table,
            /* BGM */ &reading_style_cherry_bgm
        /* ---------------------------------------------------------------- */
    },

    /* TOSS_BOYS ("Rhythm Stand-Up") */ {
        /* TITLE ---------------------------------------------------------- */
            "节奏漫才",
        /* BODY ----------------------------------------------------------- */
            // 阶段 5 已校对 reading_manzai_story；三处英式/美式台词分支保留，各自接入同一已校对中文。
            // TODO 未校对：资料室自动折行和分页位置仍需实机查看。
            "黄小胖“大家好啊，我是黄小胖！”\n"
            "蓝俊“大家好啊，我是蓝俊！”\n"
            "二人“我们是 Y&B！请多关照～！”\n"
            "黄小胖“喂喂，蓝俊。前几天啊，我去音乐教室体验入学了！”\n"
            "蓝俊“诶ー！真的假的！？你都没跟我说！黄小胖，你要开始学乐器啦！？吉他？鼓？啥啥？”\n"
            "黄小胖“我负责的啊…”\n"
            "蓝俊“嗯嗯，啥啥？”\n"
            "黄小胖“我负责的是 节奏！”\n"
            "蓝俊“哈？节奏？黄小胖，那又不是乐器啊！啥叫节奏啊。”\n"
            #ifdef PARADISE
            "黄小胖“不是啦，我跟老师说我想学打鼓，结果老师就叫我先去练节奏啦！”\n"
            #else
            "黄小胖“不是啦，我跟老师说我想学打鼓，结果老师就叫我先去练节奏啦！”\n"
            #endif
            "蓝俊“黄小胖，他大概是叫你先锻炼节奏感吧。”\n"
            "黄小胖“啊，对哦！好像确实是这么说的！蓝俊，你也太厉害了吧！你怎么知道的！？你是超能力者吗？”\n"
            "蓝俊“什么叫怎么知道… 这不就一听就知道吗！！这是常识啊！！！”\n"
            "黄小胖“嘛嘛，别那么生气啦～”\n"
            "蓝俊“啊、啊啊，也是，对不起…”\n"
            "黄小胖“啊！蓝俊，你裤链开了。”\n"
            "蓝俊“诶！？哇，假的吧！！真的！？”\n"
            "黄小胖“骗你的。”\n"
            #ifdef PARADISE
            "蓝俊“我倒！”\n"
            "黄小胖“你这反应也太老啦。”\n"
            #else
            "蓝俊“我倒！”\n"
            "黄小胖“你这反应也太老啦。”\n"
            #endif
            "蓝俊“吵死了！要你管！！”\n"
            "黄小胖“气死我啦！！！”\n"
            "蓝俊“哇！怎、怎么还是你反过来发火啊。真是完全搞不懂！”\n"
            "黄小胖“然后啊，说回节奏感的事。”\n"
            "蓝俊“啊、啊啊，对哦。”\n"
            "黄小胖“真是的… 别把话题带跑啦。”\n"
            "蓝俊“啊啊抱歉… 等等，带跑话题的不是你吗！！！把话题扯歪的人明明就是你啊ーーー！！还拿裤链开了这种事骗人！！！”\n"
            "黄小胖“嘛嘛，别那么生气嘛。”\n"
            "蓝俊“吵死啦！真是的… 所以说，节奏感到底要说啥？”\n"
            #ifdef PARADISE
            "黄小胖“听说，嵌在的洗澡罐，经过训练就会成长。”\n"
            #else
            "黄小胖“听说，嵌在的洗澡罐，经过训练就会成长。”\n"
            #endif
            "蓝俊“笨蛋！哪来的罐子！是潜在的节奏感吧！”\n"
            "二人“献丑啦ーー！”",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_manzai_gfx_table,
            /* BGM */ &reading_style_manzai_bgm
        /* ---------------------------------------------------------------- */
    },

    /* FAN_MAIL ("Fan Mailbag") */ {
        /* TITLE ---------------------------------------------------------- */
            "喜悦来信",
        /* BODY ----------------------------------------------------------- */
            "We've received many letters from satisfied\n"
            #ifdef PARADISE
            "players of Rhythm Paradise Advance.\n"
            #else
            "players of Rhythm Heaven Advance.\n"
            #endif
            "\n"
            "So, SO many in fact(!), that we can't show all of them,\n"
            "but here are just a few of our players' thoughts!\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "Just by improving my sense of rhythm...\n"
            "\n"
            "\0031" "\001m" "I've become... popular?\n"
            "\0030" "\001s" "\n"
            #ifdef PARADISE
            "Before I found Rhythm Paradise Advance,\n"
            #else
            "Before I found Rhythm Heaven Advance,\n"
            #endif
            "I had no luck with women, but now I'm a real hot shot\n"
            "with a new lease on life!\n"
            "\n"
            "\001R" "Mr. T, Age 38, Office Worker\n"
            "\001L" "Just by improving my sense of rhythm...\n"
            "\n"
            "\0031" "\001m" "I've become...\n"
            "\0031" "\001R" "a better singer?"
            "\0030" "\001s" "\n"
            #ifdef PARADISE
            "\001L" "Before I found Rhythm Paradise Advance,\n"
            #else
            "\001L" "Before I found Rhythm Heaven Advance,\n"
            #endif
            "I was the textbook definition of tone-deaf,\n"
            "but lately people have told me my singing is much nicer!\n"
            "I'm still tone deaf, of course, but at least I'm happy!\n"
            "\001R" "Mrs. H, Age 29, Housewife\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_FORMULA ("The Rhythm Formula") */ {
        /* TITLE ---------------------------------------------------------- */
            "一看就懂！节奏公式",
        /* BODY ----------------------------------------------------------- */
            "\001C" "\0032" "\001m" "\n"
            "\n"
            "Sense of rhythm ⊃ Flow\n"
            "\n"
            "Sense of rhythm ≠ Flow\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "Explanation: Flow is an element included in anyone's\n"
            "sense of rhythm, but not a sense of rhythm itself.\n"
            "\001C" "\0032" "\001m" "\n"
            "\n"
            "\n"
            "\n"
            "Rhythm ≠ Sense of rhythm\n"
            "\n"
            "\001C" "\0030" "\001s" "\n"
            "Explanation: Rhythm is what ticks at a steady pace.\n"
            "A sense of rhythm is how you maintain that pace,\n"
            "expressed naturally by way of flow.\n"
            "\001C" "\0031" "\001m" "\n"
            "\n"
            "\n"
            "Good dancing ≠ Good sense of rhythm\n"
            "\001C" "\0030" "\001s" "\n"
            "Explanation: Someone who's a good dancer does not\n"
            "inherently have a good sense of rhythm.",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_classroom_gfx_table,
            /* BGM */ &reading_style_classroom_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_DIAGNOSIS ("Rhythm Diagnosis") */ {
        /* TITLE ---------------------------------------------------------- */
            "节奏感类型测试",
        /* BODY ----------------------------------------------------------- */
            "\001C" "\0031" "\001m" "Rhythm Diagnosis\n"
            "\0030" "\001s" "\n"
            "Let's diagnose your sense of rhythm.\n"
            "Choose the ones that apply to you!\n"
            "\n"
            "I think that I have a good sense of rhythm.\n"
            "Yes - Go to Page 2!\n"
            "No - Go to Page 3!\n"
            "-1-\n"
            "\n"
            "Between Rock and Pop music, I like...\n"
            "\n"
            "\n"
            "\n"
            "Rock - Go to Page 4!\n"
            "Pop - Go to Page 5!\n"
            "\n"
            "-2-\n"
            "\n"
            "Between Jazz and Classical music, I like...\n"
            "\n"
            "\n"
            "\n"
            "Jazz - Go to Page 6!\n"
            "Classical - Go to Page 7!\n"
            "\n"
            "-3-\n"
            "\n"
            "I think you need a good sense of rhythm to dance well.\n"
            "\n"
            "\n"
            "\n"
            "Yes - Go to Page 8!\n"
            "No - Go to Page 9!\n"
            "\n"
            "-4-\n"
            "\n"
            "I think that if you can hear good rhythm,\n"
            "then you can express it.\n"
            "\n"
            "\n"
            "Yes - Go to Page 10!\n"
            "No - Go to Page 11!\n"
            "\n"
            "-5-\n"
            "\n"
            "I don't think anyone has a sense of rhythm at all.\n"
            "\n"
            "\n"
            "\n"
            "Yes - Go to Page 9!\n"
            "No - Go to Page 8!\n"
            "\n"
            "-6-\n"
            "\n"
            "I think that a sense of rhythm is inherent,\n"
            "meaning you can't improve it with training.\n"
            "\n"
            "\n"
            "Yes - Go to Page 10!\n"
            "No - Go to Page 11!\n"
            "\n"
            "-7-\n"
            "\n"
            "I think that your sense of rhythm is cooler\n"
            "when you have flow.\n"
            "\n"
            "\n"
            "Yes - Go to Page 12!\n"
            "No - Go to Page 13!\n"
            "\n"
            "-8-\n"
            "\n"
            "I think that a sense of rhythm and\n"
            "flow are just about the same thing.\n"
            "\n"
            "\n"
            "Yes - Go to Page 14!\n"
            "No - Go to Page 15!\n"
            "\n"
            "-9-\n"
            "\n"
            "I don't think you can become popular just by\n"
            "having a good sense of rhythm.\n"
            "\n"
            "\n"
            "Yes - Go to Page 16!\n"
            "No - Go to Page 17!\n"
            "\n"
            "-10-\n"
            "\n"
            "I think that having a good sense of rhythm\n"
            "makes it easy to mask being tone deaf.\n"
            "\n"
            "\n"
            "Yes - Go to Page 18!\n"
            "No - Go to Page 19!\n"
            "\n"
            "-11-\n"
            "\n"
            "I think that a good sense of rhythm is easier\n"
            "to acquire at a young age.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 21!\n"
            "\n"
            "-12-\n"
            "\n"
            "I don't think you can improve your\n"
            "sense of rhythm after becoming an adult.\n"
            "\n"
            "\n"
            "Yes - Go to Page 21!\n"
            "No - Go to Page 22!\n"
            "\n"
            "-13-\n"
            "\n"
            "I think that rhythm and\n"
            "everyday life are unrelated.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 22!\n"
            "\n"
            "-14-\n"
            "\n"
            "I think that even a sense of rhythm that you've had\n"
            "for over three years can quickly be lost\n"
            "if you're not mindful of it.\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 20!\n"
            "\n"
            "-15-\n"
            "\n"
            "I think that your sense of rhythm will\n"
            "improve if you train long and hard.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 22!\n"
            "\n"
            "-16-\n"
            "\n"
            "I think that your sense of rhythm can improve\n"
            "in just 30 seconds if you stay mindful of it.\n"
            "\n"
            "\n"
            "Yes - Go to Page 22!\n"
            "No - Go to Page 23!\n"
            "\n"
            "-17-\n"
            "\n"
            "I don't think it's a good thing to\n"
            "always feel a sense of rhythm.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 20!\n"
            "\n"
            "-18-\n"
            "\n"
            "I think that a good sense of rhythm is\n"
            "acquired by repetition, not theory.\n"
            "\n"
            "\n"
            "Yes - Go to Page 23!\n"
            "No - Go to Page 21!\n"
            "\n"
            "-19-\n"
            "\001C" "Your Sense of Rhythm:\n"
            "\0031" "\001m" "Flow Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You have a good attitude about your sense of rhythm.\n"
            "You might not have confidence in your\n"
            "sense of rhythm quite yet, but you could probably\n"
            "use rhythm to lead an enjoyable life.\n"
            "Enjoy getting into the flow!\n"
            "\001C" "-20-\n"
            "\001C" "Your Sense of Rhythm:\n"
            "\0031" "\001m" "Shy Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You're nervous about your sense of rhythm, huh?\n"
            "Everyone has a sense of rhythm.\n"
            "If you live life being mindful of the rhythms\n"
            "around you, your sense of rhythm can only grow.\n"
            "Make sure to relax.\n"
            "\001C" "-21-\n"
            "\001C" "Your Sense of Rhythm:\n"
            "\0031" "\001m" "Carefree Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You should learn the difference between a sense\n"
            "of rhythm and flow. A good flow can only go so far\n"
            "if your sense of rhythm is poor.\n"
            "Steady your sense of rhythm and\n"
            "your flow could improve everyone's mood.\n"
            "\001C" "-22-\n"
            "\001C" "Your Sense of Rhythm:\n"
            "\0031" "\001m" "Catchy Type" "\0030" "\001s" "\n"
            "\n"
            "\001C" "You may have a hard time grasping rhythm.\n"
            "If you find ways to incorporate your sense of rhythm\n"
            "into your daily routine,\n"
            "perhaps it can grow and improve.\n"
            "It might even make things more fun that way!\n"
            "\001C" "-23-\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_classroom_gfx_table,
            /* BGM */ &reading_style_classroom_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_POEM ("Rhythm Poem Digest") */ {
        /* TITLE ---------------------------------------------------------- */
            "节奏诗集",
        /* BODY ----------------------------------------------------------- */
            "\001C" "\0031" "\001m" "To Nurture\n"
            "\n"
            "\001C" "\0030" "\001s" "I have nurtured it,\n"
            "For the day when it will learn to use its wings.\n"
            "In the wake of a casual, everyday life,\n"
            "Naturally,\n"
            "Enjoyably,\n"
            "That which is now only very, very small,\n"
            "My sense of rhythm...\n"
            "\001C" "\0031" "\001m" "Karate Rhythm\n"
            "\001C" "\0030" "\001s" "\n"
            "Hey! Baby! How's it going?\n"
            "This beat is non-stop.\n"
            "Hey! Baby! Listen to my phrase.\n"
            "I can give you\n"
            "the sense of rhythm.\n"
            "Oh, yeah.\n"
            "Awake, baby! Trust me!\n"
            "This beat is non-stop!\n"
            "New groove in your soul.\n"
            "Oh, yeah!\n"
            "This beat!\n"
            "You are growing up well.\n"
            "Hey, baby!\n"
            "Hold onto your ambition.\n"
            "Hey! Oh, yeah!\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_HAIKU ("Rhythm Haiku Folio") */ {
        /* TITLE ---------------------------------------------------------- */
            "节奏俳句集",
        /* BODY ----------------------------------------------------------- */
            "\n"
            "\001L" "\0030" "\001s" "Let us exercise\n"
            "\001C" "\0030" "\001s" "something which everyone has,\n"
            "\001R" "\0030" "\001s" "a sense of rhythm\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"Your sense of rhythm can be developed with\n"
            "practice, especially when it's worked into\n"
            "your daily routine.\"\n"
            "\n"
            "\n"
            "\001L" "\0030" "\001s" "You can make all your\n"
            "\001C" "\0030" "\001s" "everyday activities\n"
            "\001R" "\0030" "\001s" "much more rhythmical\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"It's good to feel and improve your sense of rhythm\n"
            "throughout your day, such as while walking,\n"
            "brushing your teeth, cooking, etc...\n"
            "You should always keep rhythm in mind.\"\n"
            "\n"
            "\001L" "\0030" "\001s" "Your sense of rhythm,\n"
            "\001C" "\0030" "\001s" "if your flow can be improved,\n"
            "\001R" "\0030" "\001s" "gets even cooler\n"
            "\n"
            "\001C" "\0030" "\001s" "\"However, a sense of rhythm and good flow are not\n"
            "one and the same. Try to improve your flow while\n"
            "also being mindful of your sense of rhythm.\"\n"
            "\n"
            "\n"
            "\001L" "\0030" "\001s" "In a break or pause\n"
            "\001C" "\0030" "\001s" "children who lack patience are\n"
            "\001R" "\0030" "\001s" "simply too stubborn\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"It can be difficult to count accurately during a rest,\n"
            "and it's easy to resume the beat early, but the\n"
            "ability to stay calm and wait affects your \n"
            "flow the most.\"\n"
            "\n"
            "\001L" "\0030" "\001s" "Even in adults,\n"
            "\001C" "\0030" "\001s" "something still rapidly grows:\n"
            "\001R" "\0030" "\001s" "Their sense of rhythm\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "\"From simply being mindful of it, your sense of rhythm\n"
            "can grow exponentially, no matter your age.\"\n"
            "\n"
            "\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_haiku_gfx_table,
            /* BGM */ &reading_style_haiku_bgm
        /* ---------------------------------------------------------------- */
    },

    /* READING_MATERIAL_CREDITS */ {
        /* TITLE ---------------------------------------------------------- */
            "Advance Credits",
        /* BODY ----------------------------------------------------------- */
            "Rhythm Heaven Advance is a fan translation project\n"
            "made entirely by fans of the original series.\n"
            "\n"
            "This project wouldn't have been possible without the\n"
            "help of all the incredible people that came together!\n"
            "\n"
            "Whether it was Graphics, Sound, Localization,\n"
            "Translation, Playtesting or even just giving\n"
            "your opinion, every input mattered.\n"
            "So without further ado, here are all the incredible\n"
            "people that helped make this project possible:\n"
            "\n"
			"Main Maintainers:\n"
			"+ ShaffySwitcher\n"
			"+ itaific\n"
			"\n"
			"Coding Contributions:\n"
			"+ Deni_iguess\n"
			"+ patataofcourse\n"
			"+ Conhlee\n"
			"+ Everyone who has worked on the decompilation.\n"
			"\n"
			"Assets & Graphics:\n"
			"+ SkyeStage\n"
			"+ Cash Banooka\n"
			"+ geometricentric\n"
			"+ somethingAccurate\n"
			"+ TinyCastleGuy\n"
			"+ The Eggo55\n"
			"+ vincells\n"
			"+ WindowsTiger\n"
			"+ Kievit\n"
			"+ NotWario\n"
			"+ amdree\n"
			"+ patataofcourse\n"
			"+ Nate Candles\n"
			"+ Borists\n"
			"+ Tailx\n"
			"\n"
			#ifdef PARADISE
            "Localisation / Translation:\n"
            #else
            "Localization / Translation:\n"
            #endif
			"+ Cash Banooka\n"
			"+ SkyeStage\n"
			"+ somethingAccurate\n"
			"+ ShaffySwitcher\n"
			"+ Mizuka Lover\n"
			"+ castIeRook\n"
			"+ patataofcourse\n"
			"+ Various Rhythm Heaven games\n"
			"+ Inspiration from Rhythm Heaven Silver\n"
			"\n"
			"Sound Effects:\n"
			"+ Various Rhythm Heaven games\n"
			"+ Cherryberryfaygo\n"
			"+ Nabix (& his family)\n"
			"+ itaific\n"
			"+ FireChat♂\n"
			"+ saladplainzone\n"
            "+ Bellajenna\n"
            "+ Roxby\n"
            "+ Kievit\n"
			"\n"
            "\n"
            "\n"
            "Remix 3 English Song Credits:\n"
            "Vocals: Bellajenna\n"
            "Translation: castIeRook, Mizuka Lover\n"
            "Mixing: FireChat♂, castIeRook\n"
            "Remix 5 English Song Credits:\n"
            "Vocals: Roxby\n"
            "Translation: castIeRook\n"
            "Revisions: Cash the Nondescript, saladplainzone\n"
            "Mixing: FireChat♂, saladplainzone\n"
			"Playtesting:\n"
			"+ nwqol\n"
			"+ pokedart9001\n"
			"+ MacBass24\n"
			"+ GamblingGambit\n"
			"+ UriaOfFlames\n"
			"+ FernandoLemon\n"
			"+ KingDragoon24\n"
			"+ IloGaming4\n"
			"+ Feder-28\n"
			"+ The Eggo55\n"
			"+ Sammie the Moron\n"
			"+ taylor\n"
			"+ Bluefus\n"
			"+ 0blivion\n"
			"+ Funk\n"
			"+ Borists\n"
			"+ WilliamDavi\n"
			"+ Spooky Jumpropes\n"
			"+ Lilynell\n"
			"+ acerbt\n"
			"+ Lemonici\n"
            "\n"
			"Special Thanks:\n"
			"+ The decomp folks again\n"
			"+ Everyone in the Rhythm Heaven Advance Discord\n"
			"  ... and you!\n"
            "Thank you all for your hard work!\n"
            "And thank YOU for playing this patch!\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    }
};
