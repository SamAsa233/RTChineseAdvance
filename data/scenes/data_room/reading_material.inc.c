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
            // 实机核验：2026-09-29 mGBA 确认全文单页显示，中文自动折行无重叠或截断。
            #ifdef BRIT
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
            // 阶段 5 已校对 reading_night_walk_story：中文谜题改为三个编号，所以正文中的编号也逐处对应更新。
            // 相邻的 C 字符串会自动拼接；只有 \n 会让画面换行，故长段按语义拆开源码但不额外插入画面换行。
            // 原版用 BRIT 区分英美拼写；中文虽相同，仍保留两条编译路径并逐条核验。
            // \001C/\001L 切换居中/左对齐，\0031/\0030 和 \001m/\001s 切换字号，强调范围按中文编号调整。
            // 实机核验：2026-09-29 mGBA 确认全文三页，①②③、字号切换、自动折行和末页位置正常。
            #ifdef BRIT
            "出演《夜间漫步》的那位，据说非常喜欢音乐。听说他以前也做过音乐相关的工作，"
            #else
            "出演《夜间漫步》的那位，据说非常喜欢音乐。听说他以前也做过音乐相关的工作，"
            #endif
            "这次会在这款游戏里登场，好像也是托了那层关系的福。前阵子我在街上偶然碰见他，就上前聊了几句，"
            "结果他只丢下一句“最喜欢音乐啦！”，就顺着楼梯往上跑，不知道去了哪里。我当时还稍微想了一下，"
            "要是以后还能在哪儿再见到这位音乐迷就好了。话说回来，他到底叫什么名字呢？\n"
            "\n"
            "好了，接下来是问答时间！\n"
            "那位先生的名字是…\n"
            "\001C" "\0031" "\001m" "①②③\n"
            "\001L" "\0030" "\001s" "请写出各个编号里该填的字！\n"
            "答对的话，就能看到下一页的文章啦！！\n"
            "\n"
            "\0031" "\001m" "\001C" "节奏游戏《问答》的秘密\n"
            "\0030" "\001s" "\001L" "\n"
            "那个游戏里，音乐开始" "\0031" "\001m" "①②" "\0030" "\001s" "后，\n"
            "玩家每按一下按钮，\n"
            "计数器就会照着次数增加，对吧？\n"
            "\n"
            "其实，只要把规则" "\0031" "\001m" "②" "\0030" "\001s" "在一边，\n"
            "不停地猛按按钮，\n"
            "就会发生不得了的事情。\n"
            "\n"
            "诸" "\0031" "\001m" "③" "\0030" "\001s" "不妨亲自试试看。\n"
            "不过嘛，也别抱太大期待啦～！",
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
            	    #ifdef BRIT
	    	"We were given the chance to interview Mr F,\n"
            "inventor of the Horse Machine in the Rhythm Toys\n"
            "section, about its development.\n"
            "\n"
            "\n"
            "Mr F: The idea came about because I just really\n"
            "wanted to share the joys of riding a horse. So\n"
            "development sort of revolved around that idea.\n"
            "\n"
            "Mr F's comments were as simple as they were\n"
            "passionate.\n"
            "\n"
            "Mr F: But in trying to make a game out of it, I found\n"
            "myself losing sight of that end goal. I considered\n"
            "giving up many times.\n"
            "\n"
            "It was a struggle for Mr F, who found it difficult to\n"
            "express his vision within a standard framework.\n"
            "Mr F: But thinking about the kinds of people who\n"
            "use the Horse Machine and get even a little joy\n"
            "out of it...\n"
            "Well, the hardships sort of just drift away.\n"
            "\n"
            "Mr F, you are truly devoted to your craft.\n"
            "We look forward to seeing your next creations.\n"
            "Thank you!",
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
            // 实机核验：2026-09-29 mGBA 确认全文三页，对话引号、英文名称和末页“完”均完整显示。
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
            #ifdef BRIT
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
            #ifdef BRIT
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
            // 实机核验：2026-09-29 mGBA 确认全文两页，跨页段落和右对齐结尾均未截断。
            "来自神秘节奏组织的最后通告。\n"
            #ifdef BRIT
            "Rhythm BRIT Advance.\n"
            "\n"
            "That much is undeniable, and we fully recognise it.\n"
            #else
            "Rhythm Heaven Advance.\n"
            "\n"
            "That much is undeniable, and we fully recognize it.\n"
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
            "Yellow: Hello, I'm Yellow!\n"
            "Blue: Hello, I'm Blue!\n"
            "Both: Y&B! Nice to meet you!\n"
            "\n"
            "Yellow: Hey Blue! You heard? I'm taking a music class!\n"
            "Blue: Wait, really? No way! What instrument are you\n"
            "learning, Yellow? Is it the guitar? Drums maybe?\n"
            "Yellow: Well, my part is...\n"
            "Blue: Yeah? What?\n"
            "Yellow: I'll be playing rhythm!\n"
            "Blue: Wha? You can't \"play\" rhythm, Yellow.\n"
            "It's not an instrument. Where did you hear that?\n"
            "Yellow: Well, I told my teacher I wanted to play\n"
            #ifdef BRIT
            "drums, but he told me I should practise \"rhythm\" first!\n"
            #else
            "黄小胖“不是啦，我跟老师说我想学打鼓，结果老师就叫我先去练节奏啦！”\n"
            #endif
            "Blue: Yellow, I think he meant you need to\n"
            "improve your sense of rhythm.\n"
            "Yellow: Oh yeah, that's much closer! That's\n"
            "incredible! How did you know? Are you psychic?\n"
            "Blue: How did I- Why wouldn't I know!? It's just\n"
            "common sense!\n"
            "Yellow: Hey, man! No need to get so angry.\n"
            "Blue: Ah... You know, you're right, I'm sorry...\n"
            "Yellow: Oop! Blue, your fly is down!\n"
            "Blue: Huh!? Wait, really?\n"
            "Yellow: No, I lied.\n"
            #ifdef BRIT
	    	"Blue: Why you...!\n"
            	"\n"
            	"Yellow: \"Why you\"! Man, that's kind of a\n"
            #else
            "蓝俊“我倒！”\n"
            "黄小胖“你这反应也太老啦。”\n"
            #endif
            "cheesy line, don't you think?\n"
            "Blue: Shut it... I've had enough.\n"
            "Yellow: GRAAAGH!\n"
            "Blue: Huh!? Why are you mad? What did I do?\n"
            "Yellow: Well, weren't we talking about my music class?\n"
            "Blue: Huh? Oh, yeah, that's right.\n"
            "Yellow: Geez... way to derail the whole thing...\n"
            "Blue: Ah, I'm sorry... wait, I'M sorry?\n"
            "You were the one who-- by lying that my fly was down!\n"
            "Yellow: Hey hey, no need to get so angry.\n"
            "Blue: Oh, that's rich! Anyway, what about your\n"
            "sense of rhythm?\n"
            "Yellow: Right! My classmates said that my\n"
            #ifdef BRIT
            "\"scents of rhythm\" will improve with practise.\n"
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
            // 阶段 5 已校对 reading_praise_story；沿用原三处地区分支和强调、对齐控制码。
            // 实机核验：2026-09-29 mGBA 确认全文四页，强调文字与两位见证人的右对齐署名均未截断。
            "我们收到了许多玩过\n"
            #ifdef BRIT
            "《节奏天国》的人寄来的开心来信。\n"
            #else
            "《节奏天国》的人寄来的开心来信。\n"
            #endif
            "\n"
            "来信和邮件（！）实在太多，没法一一介绍，\n"
            "所以这里只挑出其中一小部分，和大家分享。\n"
            "各位也请一定亲自试试看，\n"
            "再把它的效果告诉你的朋友们吧！！\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "明明只是节奏感变好了而已…\n"
            "\n"
            "\0031" "\001m" "居然一下子这么受欢迎，真的没问题吗！？\n"
            "\0030" "\001s" "\n"
            #ifdef BRIT
            "在遇到《节奏天国》之前，\n"
            #else
            "在遇到《节奏天国》之前，\n"
            #endif
            "我几乎完全不受女性注意，\n"
            "但现在却忽然变得很受欢迎… 连人生观都改变了。\n"
            "\n"
            "\001R" "T 先生 38 岁 公司职员\n"
            "\001L" "明明只是节奏感变好了而已…\n"
            "\n"
            "\0031" "\001m" "居然被人说\n"
            "\0031" "\001R" "唱歌变好听了！？"
            "\0030" "\001s" "\n"
            #ifdef BRIT
            "\001L" "在遇到《节奏天国》之前，\n"
            #else
            "\001L" "在遇到《节奏天国》之前，\n"
            #endif
            "我一直被说简直就是跑调代表，\n"
            "可最近却常常被夸。\n"
            "明明我还是一样会跑调，真不可思议。\n"
            "不过真的很开心！\n"
            "\001R" "H 女士 29 岁 家庭主妇\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_FORMULA ("The Rhythm Formula") */ {
        /* TITLE ---------------------------------------------------------- */
            "一看就懂！节奏公式",
        /* BODY ----------------------------------------------------------- */
            // 汉化改动：阶段 5 译文覆盖整篇；保留原字号、对齐控制码和段落空行。
            // 实机核验：2026-09-29 mGBA 确认全文三页，公式、解说和居中位置均完整显示。
            "\001C" "\0032" "\001m" "\n"
            "\n"
            "节奏感 ⊃ 律动\n"
            "\n"
            "节奏感 ≠ 律动\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "解说：“律动”是构成节奏感的要素之一，并不等同于节奏感本身。  \n"
            "\001C" "\0032" "\001m" "\n"
            "\n"
            "\n"
            "\n"
            "节奏 ≠ 节奏感\n"
            "\n"
            "\001C" "\0030" "\001s" "\n"
            "解说：节奏是用来划分时间的；节奏感则是通过律动来表现、感受，或自然而然流露出来的东西。  \n"
            "\001C" "\0031" "\001m" "\n"
            "\n"
            "\n"
            "舞跳得好 ≠ 节奏感好\n"
            "\001C" "\0030" "\001s" "\n"
            "解说：舞跳得好的人，并不一定就代表“节奏感很好”。",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_classroom_gfx_table,
            /* BGM */ &reading_style_classroom_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_DIAGNOSIS ("Rhythm Diagnosis") */ {
        /* TITLE ---------------------------------------------------------- */
            "节奏感类型测试",
        /* BODY ----------------------------------------------------------- */
            // 汉化改动：阶段 5 译文按原来的 23 页接入；阅读器每页固定显示 9 行。
            // 每页末尾的编号必须处于第 9 行，否则后续题目会因自动分页整体错位。
            // 实机核验：2026-09-29 mGBA 逐页确认共 23 页，选项跳转提示、页码和四种结果页均完整。
            // 第 1 页：说明与第一题。
            "\001C" "\0031" "\001m" "节奏感类型测试\n"
            "\0030" "\001s" "\n"
            "来测一测你的节奏感类型。\n"
            "请选择符合你的选项！\n"
            "\n"
            "你觉得自己算是有节奏感的人。\n"
            "YES 前往第 2 页！\n"
            "NO 前往第 3 页！\n"
            "-1-\n"
            // 第 2 页：音乐类型选择。
            "\n"
            "摇滚和流行乐，你更喜欢…\n"
            "\n"
            "\n"
            "\n"
            "摇滚 前往第 4 页！\n"
            "流行乐 前往第 5 页！\n"
            "\n"
            "-2-\n"
            // 第 3 页：音乐类型选择。
            "\n"
            "爵士和古典，你更喜欢…\n"
            "\n"
            "\n"
            "\n"
            "爵士 前往第 6 页！\n"
            "古典 前往第 7 页！\n"
            "\n"
            "-3-\n"
            // 第 4 页。
            "\n"
            "你觉得没有节奏感就跳不了舞。\n"
            "\n"
            "\n"
            "\n"
            "YES 前往第 8 页！\n"
            "NO 前往第 9 页！\n"
            "\n"
            "-4-\n"
            // 第 5 页。
            "\n"
            "你觉得只要听得出节奏感，\n"
            "就能表现出来。\n"
            "\n"
            "\n"
            "YES 前往第 10 页！\n"
            "NO 前往第 11 页！\n"
            "\n"
            "-5-\n"
            // 第 6 页。
            "\n"
            "你觉得世上不存在完全没有节奏感的人。\n"
            "\n"
            "\n"
            "\n"
            "YES 前往第 9 页！\n"
            "NO 前往第 8 页！\n"
            "\n"
            "-6-\n"
            // 第 7 页。
            "\n"
            "你觉得节奏感是天生的，\n"
            "无法靠训练成长。\n"
            "\n"
            "\n"
            "YES 前往第 10 页！\n"
            "NO 前往第 11 页！\n"
            "\n"
            "-7-\n"
            // 第 8 页。
            "\n"
            "你觉得节奏感这东西，\n"
            "越有感觉越帅。\n"
            "\n"
            "\n"
            "YES 前往第 12 页！\n"
            "NO 前往第 13 页！\n"
            "\n"
            "-8-\n"
            // 第 9 页。
            "\n"
            "你觉得节奏感和“有感觉”，\n"
            "几乎是同一回事。\n"
            "\n"
            "\n"
            "YES 前往第 14 页！\n"
            "NO 前往第 15 页！\n"
            "\n"
            "-9-\n"
            // 第 10 页。
            "\n"
            "你觉得就算节奏感好，\n"
            "也不会受欢迎。\n"
            "\n"
            "\n"
            "YES 前往第 16 页！\n"
            "NO 前往第 17 页！\n"
            "\n"
            "-10-\n"
            // 第 11 页。
            "\n"
            "你觉得只要节奏感好，\n"
            "听起来就不太容易跑调。\n"
            "\n"
            "\n"
            "YES 前往第 18 页！\n"
            "NO 前往第 19 页！\n"
            "\n"
            "-11-\n"
            // 第 12 页。
            "\n"
            "你觉得节奏感在年轻时\n"
            "更容易养成。\n"
            "\n"
            "\n"
            "YES 前往第 23 页！\n"
            "NO 前往第 21 页！\n"
            "\n"
            "-12-\n"
            // 第 13 页。
            "\n"
            "你觉得成年以后就没法再\n"
            "提升节奏感了。\n"
            "\n"
            "\n"
            "YES 前往第 21 页！\n"
            "NO 前往第 22 页！\n"
            "\n"
            "-13-\n"
            // 第 14 页。
            "\n"
            "你觉得节奏感和日常生活\n"
            "毫无关系。\n"
            "\n"
            "\n"
            "YES 前往第 23 页！\n"
            "NO 前往第 22 页！\n"
            "\n"
            "-14-\n"
            // 第 15 页。
            "\n"
            "你觉得即使花了三年以上培养出的节奏感，\n"
            "只要不持续去留意它，很快也会忘掉。\n"
            "\n"
            "\n"
            "YES 前往第 23 页！\n"
            "NO 前往第 20 页！\n"
            "\n"
            "-15-\n"
            // 第 16 页。
            "\n"
            "你觉得节奏感还是要靠刻意而严格的\n"
            "训练，才比较学得扎实。\n"
            "\n"
            "\n"
            "YES 前往第 23 页！\n"
            "NO 前往第 22 页！\n"
            "\n"
            "-16-\n"
            // 第 17 页。
            "\n"
            "你觉得只要有意识地去练，\n"
            "哪怕只有 30 分钟，节奏感也会变好。\n"
            "\n"
            "\n"
            "YES 前往第 22 页！\n"
            "NO 前往第 23 页！\n"
            "\n"
            "-17-\n"
            // 第 18 页。
            "\n"
            "你觉得节奏感这东西，\n"
            "一直去感受反而不好。\n"
            "\n"
            "\n"
            "YES 前往第 23 页！\n"
            "NO 前往第 20 页！\n"
            "\n"
            "-18-\n"
            // 第 19 页。
            "\n"
            "你觉得节奏感不是靠理解理论，\n"
            "而是靠反复练习掌握的。\n"
            "\n"
            "\n"
            "YES 前往第 23 页！\n"
            "NO 前往第 21 页！\n"
            "\n"
            "-19-\n"
            // 第 20 页：律动十足型。
            "\001C" "你的节奏感类型\n"
            "\0031" "\001m" "律动十足型" "\0030" "\001s" "\n"
            "\n"
            "\001C" "你对节奏感的看法很不错。\n"
            "就算现在还不太有自信，\n"
            "今后也一定能和节奏一起\n"
            "过上快乐的人生。\n"
            "尽情享受吧！\n"
            "\001C" "-20-\n"
            // 第 21 页：害羞型。
            "\001C" "你的节奏感类型\n"
            "\0031" "\001m" "害羞型" "\0030" "\001s" "\n"
            "\n"
            "\001C" "你是不是有点太怕“节奏感”这回事了呢？\n"
            "节奏感是每个人都拥有的东西。\n"
            "只要一边享受，一边一点点\n"
            "去留意节奏，节奏感会逐渐提升。\n"
            "放心吧。\n"
            "\001C" "-21-\n"
            // 第 22 页：容易来劲型。
            "\001C" "你的节奏感类型\n"
            "\0031" "\001m" "容易来劲型" "\0030" "\001s" "\n"
            "\n"
            "\001C" "如果你能更清楚地区分节奏感和“有感觉”\n"
            "之间的区别，那就更好了。就算再有感觉，\n"
            "要是最关键的节奏感不行，那股劲也只会\n"
            "白白空转，很可惜。只要把节奏感练扎实，\n"
            "你那股活力说不定能让大家都更开心哦！？\n"
            "\001C" "-22-\n"
            // 第 23 页：一板一眼型。
            "\001C" "你的节奏感类型\n"
            "\0031" "\001m" "一板一眼型" "\0030" "\001s" "\n"
            "\n"
            "\001C" "你可能把“节奏感”这件事看得太难了。\n"
            "试着更轻松地和节奏相处，\n"
            "让它自然融进日常生活里，\n"
            "说不定节奏感就会慢慢变好。\n"
            "那样一定也会更开心！\n"
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
            // 汉化改动：阶段 5 译文只覆盖《培养》和第二首中的五句英文，其余英文原样保留。
            // 实机核验：2026-09-29 mGBA 确认全文三页，中文诗句、字号切换和第二首英文混排均正常。
            "\001C" "\0031" "\001m" "《培养》\n"
            "\n"
            "\001C" "\0030" "\001s" "我正在培养它。\n"
            "为了有朝一日，它能振翅高飞。\n"
            "在平淡无奇的日常生活之中，\n"
            "更自然地，\n"
            "更快乐地。\n"
            "如今还很渺小的，\n"
            "我的节奏感…\n"
            "\001C" "\0031" "\001m" "Karate Rhythm\n"
            "\001C" "\0030" "\001s" "\n"
            "Hey! Baby! How's it going?\n"
            "This beat is non-stop.\n"
            "Hey! Baby! Listen to my phrase.\n"
            "I can give you\n"
            "the sense of rhythm.\n"
            "Oh, Yeah.\n"
            "Awake, baby! Trust me!\n"
            "This beat is non-stop!\n"
            "New groove in your soul.\n"
            "Oh, Yeah!\n"
            "This beat!\n"
            "You are growing up well.\n"
            "Hey, Baby!\n"
            "Hold onto your ambition.\n"
            "Hey! Oh, Yeah!\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_sea_gfx_table,
            /* BGM */ &reading_style_sea_bgm
        /* ---------------------------------------------------------------- */
    },

    /* RHYTHM_HAIKU ("Rhythm Haiku Folio") */ {
        /* TITLE ---------------------------------------------------------- */
            "节奏俳句集",
        /* BODY ----------------------------------------------------------- */
            // 阶段 5 已校对 reading_haiku_1～5；五首诗仍按左、中、右三行显示。
            // 实机核验：2026-09-29 mGBA 确认五首各占一页，诗句左中右对齐及释文折行均未截断。
            "\n"
            // reading_haiku_1：前三行是诗句，第四行是释文。
            "\001L" "\0030" "\001s" "一起来锻炼\n"
            "\001C" "\0030" "\001s" "每个人都拥有的\n"
            "\001R" "\0030" "\001s" "那份节奏感\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "“潜在的节奏感可以通过训练不断成长。日复一日的反复练习，效果最好。”\n"
            "\n"
            "\n"
            // reading_haiku_2：前三行是诗句，第四行是释文。
            "\001L" "\0030" "\001s" "日常生活中\n"
            "\001C" "\0030" "\001s" "一举一动竟如此\n"
            "\001R" "\0030" "\001s" "富有节奏感\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "“节奏感最好在日常生活中持续感受并培养。走路、刷牙、做饭时，都可以试着有意识地按着节奏行动。”\n"
            "\n"
            "\n"
            // reading_haiku_3：前三行是诗句，第四行是释文。
            "\001L" "\0030" "\001s" "说到节奏感\n"
            "\001C" "\0030" "\001s" "律动若是也够好\n"
            "\001R" "\0030" "\001s" "那就更加酷\n"
            "\n"
            "\001C" "\0030" "\001s" "“不过，节奏感和律动并不是一回事。要一边留意节奏、一边慢慢练，也把那股感觉带出来。”\n"
            "\n"
            "\n"
            // reading_haiku_4：前三行是诗句，第四行是释文。
            "\001L" "\0030" "\001s" "等不住 break\n"
            "\001C" "\0030" "\001s" "那个女孩总显得\n"
            "\001R" "\0030" "\001s" "差了半拍呢\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "“准确数清 break 很难，人往往会忍不住抢拍。能不能沉住气等到正确时机，会大大影响一个人看起来够不够帅。”\n"
            "\n"
            "\n"
            // reading_haiku_5：前三行是诗句，第四行是释文。
            "\001L" "\0030" "\001s" "就算是大人\n"
            "\001C" "\0030" "\001s" "也能飞快地提升\n"
            "\001R" "\0030" "\001s" "那份节奏感\n"
            "\001L" "\0030" "\001s" "\n"
            "\001C" "\0030" "\001s" "“只要平时有意识地把握节奏，即使成年以后，节奏感也依然能够得到显著提升。”\n"
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
            "+ Iestyn129\n"
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
			#ifdef BRIT
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
			"+ TheAwkwardGirl\n"
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
            "+ Opera Zebb\n"
            "+ Kayyluhh\n"
            "+ Xx_Player25_xX\n"
            "\n"
            "\n"
			"Special Thanks:\n"
			"+ The decomp folks again\n"
			"+ Everyone in the Rhythm Heaven Advance Discord\n"
            "+ The Detail Detectors (You know who you are!)\n"
			"  ... and you!\n"
            "\n"
            "Thank you all for your hard work!\n"
            "And thank YOU for playing this patch!\n",
        /* STYLE ---------------------------------------------------------- */
            /* GFX */ reading_style_mail_gfx_table,
            /* BGM */ &reading_style_mail_bgm
        /* ---------------------------------------------------------------- */
    }
};
