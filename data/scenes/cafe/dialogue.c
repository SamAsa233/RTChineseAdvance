#include "global.h"
#include "graphics.h"
#include "text.h"
#include "src/scenes/cafe.h"
#include "graphics/cafe/cafe_graphics.h"


  /* CAFE - DIALOGUE */


// [D_089cd2e8] Dialogue - First Visit
    /* -------------------------------- */
        //
        // Welcome. This is your
        // first time here, isn't it?
        //
    /* -------------------------------- */
        // This is the Cafe.
        // <When you can't finish a game>,
        // or when you just want a break,
        // please come here and relax.
    /* -------------------------------- */
        //
        // I'm pretty good at Rhythm Games.
        // If you need help, <come to the Cafe>.
        //
    /* -------------------------------- */
        //
        // I'm still unpacking boxes, so
        // please come back in a bit.
        //
    /* -------------------------------- */
        //
        //
        // See you later.
        //
    /* -------------------------------- */

const char *cafe_dialogue_first_visit[] = {
    /* ------------------------------------------------ */
        "欢迎光临。\n你是第一次来这里吧？\n",
    /* ------------------------------------------------ */
        "\n"
        "Feel free to come on by anytime you\n"
        "find the games " "\0051" "\0015" "too hard to play " "\0054" "\0018" "or\n"
        "you just need to take a break.",
    /* ------------------------------------------------ */
        "\n"
        "If there's anything I can\n"
        "do to help, well, " "\0051" "\0015" "that's\n"
        "what I'm here for." "\0054" "\0018" "",
    /* ------------------------------------------------ */
        "我现在正在准备点东西，\n请你晚点再来哦。\n",
    /* ------------------------------------------------ */
        "那，下回见哦。\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd300] Dialogue - Come Back Later
    /* -------------------------------- */
        //
        //
        // Come back in a while!
        //
    /* -------------------------------- */

const char *cafe_dialogue_come_back_later[] = {
    /* ------------------------------------------------ */
        "过一会儿再来哦〜。\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd308] Dialogue - Keep Trying
    /* -------------------------------- */
        //
        // You know, after a few tries
        // I think you'll manage that superb.
        //
    /* -------------------------------- */
        //
        // Just keep moving to the music,
        // and you'll have fun doing it, too.
        //
    /* -------------------------------- */
        //
        // Don't let it frustrate you.
        // You're supposed to enjoy yourself.
        //
    /* -------------------------------- */

const char *cafe_dialogue_keep_trying[] = {
    /* ------------------------------------------------ */
        "多玩几次的话，\n我想你会慢慢抓到诀窍的哦。\n",
    /* ------------------------------------------------ */
        "同时呢，\n你也会越来越享受跟着音乐律动的感觉。\n",
    /* ------------------------------------------------ */
        "别太较劲啦，\n开心玩就好…\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd318] Dialogue - Practicing for the Perfect Campaign
    /* -------------------------------- */
        //
        // Sorry for yelling. I just got
        // a little too excited there.
        //
    /* -------------------------------- */
        //
        // Please try your best
        // for those Perfects.
        // See you soon!
    /* -------------------------------- */

const char *cafe_dialogue_practicing_perfect[] = {
    /* ------------------------------------------------ */
        "抱歉，刚才声音太大了。\n我实在是太替你高兴了…\n",
    /* ------------------------------------------------ */
        "Perfect 也要继续加油哦。\n那回头见。\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd324] Dialogue - Not Practicing for the Perfect Campaign
    /* -------------------------------- */
        //
        // Is that right? Loose lips can sink
        // friendships... please forgive me.
        //
    /* -------------------------------- */
        //
        // Please enjoy the
        // game. See you!
        //
    /* -------------------------------- */

const char *cafe_dialogue_not_practicing_perfect[] = {
    /* ------------------------------------------------ */
        "这样呀。\n还跟你聊了些传闻，\n真是失礼啦。",
    /* ------------------------------------------------ */
        "请继续享受游戏哦。\n那回头见。\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd330] Dialogue - All Perfects Cleared
    /* -------------------------------- */
        //
        // You must have excellent rhythm
        // sense to have gotten this far!
        //
    /* -------------------------------- */
        //
        // Oh, I'm so happy I think
        // I might just start to cry.
        //
    /* -------------------------------- */
        //
        // Well, in celebration I've added
        // more songs to the studio.
        //
    /* -------------------------------- */
        //
        // Wow. It looks like you've
        // mastered the game. Not bad.
        //
    /* -------------------------------- */
        //
        // Had enough, I suppose? Go
        // get some rest. I'll be waiting.
        //
    /* -------------------------------- */

const char *cafe_dialogue_all_perfects_clear[] = {
    /* ------------------------------------------------ */
        "哎呀，都已经玩到这种地步了，\n你的节奏感\n肯定已经变得相当好了呢！",
    /* ------------------------------------------------ */
        "我也高兴得\n眼泪汪汪啦…\n",
    /* ------------------------------------------------ */
        "对了对了，\n作为庆祝，虽然只是小小心意，\n我帮你往录音室里添了些曲子。\n",
    /* ------------------------------------------------ */
        "哎呀呀，这可真是不得了，\n居然全部完成了呀。\n真有你的〜。",
    /* ------------------------------------------------ */
        "你也累了吧？\n稍微休息一下哦。\n那，下回见。",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// Dialogue - Extra Perfects Cleared
const char *cafe_dialogue_extra_perfects_clear[] = {
    /* ------------------------------------------------ */
        "\n"
        "blabla you finished the extra campaign!\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "it's so AWESOME!!\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// Dialogue - All Perfects Cleared (Main + Extra)
const char *cafe_dialogue_all_perfects_clear_big[] = {
    /* ------------------------------------------------ */
        "\n"
        "woohoo main & extra!\n"
        "\n",
    /* ------------------------------------------------ */
        "\n"
        "you finished the campaign!\n"
        "\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd348] Praise
    /* -------------------------------- */
        //
        //
        // Not too bad!!
    /* -------------------------------- */
        //
        //
        // You're good!!
    /* -------------------------------- */
        //
        //
        // Congratulations!!
    /* -------------------------------- */
        //
        //
        // Good job!!
    /* -------------------------------- */
        //
        //
        // Unbelievable!!
    /* -------------------------------- */

const char *cafe_dialogue_shouts_praise[] = {
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "That's great!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "Amazing!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "Congratulations!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "Great job!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
    "\0032" "\001l" "\0051" "\0015" "\n"
    "\n"
    "I can't believe it!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
};


// [D_089cd35c] Encouragement
    /* -------------------------------- */
        //
        //
        // <Go for it!>
    /* -------------------------------- */
        //
        //
        // <Fight!>
    /* -------------------------------- */
        //
        //
        // <Go! Go!>
    /* -------------------------------- */
        //
        //
        // Good luck!
    /* -------------------------------- */
        //
        //
        // I was moved!
    /* -------------------------------- */

const char *cafe_dialogue_shouts_cheer[] = {
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Go for it!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Give it your all!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Keep going!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "Good luck!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
        "\0032" "\001l" "\0051" "\0015" "\n"
        "\n"
        "I'm impressed!" "\0030" "\001s" "\0054" "\0018",
    /* ------------------------------------------------ */
};


// [D_089cd370] Dialogue - Rhythm Sense
    /* -------------------------------- */
        //
        // By the way, I wonder how
        // Rhythm Sense is for humans?
        //
    /* -------------------------------- */
        //
        // Well, not that I'm very
        // aware of it myself.
        //
    /* -------------------------------- */
        //
        // But you'll be a bit happier once you
        // find your Rhythm Sense, I'm sure.
        //
    /* -------------------------------- */
        //
        // Maybe I should try a little harder
        // to get good at Rhythm Heaven...
        //
    /* -------------------------------- */

const char *cafe_dialogue_rhythm_sense[] = {
    /* ------------------------------------------------ */
        "说起来呀，节奏感这种东西，对人类来说究竟意味着什么呢。\n",
    /* ------------------------------------------------ */
        "不过像我嘛，\n平时倒也不怎么会特意去想这个啦。\n",
    /* ------------------------------------------------ */
        "不过，节奏感变好了的话，\n人应该也会稍微开心一点吧。",
    /* ------------------------------------------------ */
        "我也来试着玩玩游戏好了…\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd384] Dialogue - Offbeats
    /* -------------------------------- */
        //
        // I hear the word "offbeat" often.
        // Do you know what an "offbeat" is?
        //
    /* -------------------------------- */
        // Honestly, I wasn't sure
        // what it meant either.
        // So, the other day I looked
        // up the definition.
    /* -------------------------------- */
        //
        // How do I explain it...
        // Well, you naturally clap
        // your hands to music, right?
    /* -------------------------------- */
        // Halfway between one clap
        // and the next (the "onbeats")
        // is called the "offbeat".
        // At least, so I understand.
    /* -------------------------------- */
        // Did you know that already?
        // Sorry if it seems like I'm
        // talking down to you.
        // Anyways, see you again.
    /* -------------------------------- */

const char *cafe_dialogue_offbeats[] = {
    /* ------------------------------------------------ */
        "说起来，这个世界里常听人说的\n“反拍”到底是什么，\n你知道吗？",
    /* ------------------------------------------------ */
        "不过嘛，我其实也没懂得那么多，\n所以讲得可能不太靠谱哦。\n",
    /* ------------------------------------------------ */
        "比如说，\n你跟着音乐很自然地拍手，对吧。\n",
    /* ------------------------------------------------ */
        "那每次拍手和拍手之间，\n刚好正中间的那个时机，\n听说就叫“反拍”。",
    /* ------------------------------------------------ */
        "嗯，大概就是这么回事啦。\n讲得随随便便的，真不好意思哦。\n那，下回见。",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd39c] Dialogue - Rhythm Test
    /* -------------------------------- */
        //
        // Say, when was the last time you
        // checked your "Rhythm Test" score?
        //
    /* -------------------------------- */
        //
        // I just tried it again yesterday, but
        // 65 points seems to be my limit...
        //
    /* -------------------------------- */
        //
        // I always have trouble with
        // the rests in the second test.
        //
    /* -------------------------------- */
        //
        // Counting to yourself is hard, isn't it?
        // I always go too fast or lose my place.
        //
    /* -------------------------------- */
        //
        // Well, nothing we can do but practice.
        // Take care for now.
        //
    /* -------------------------------- */

const char *cafe_dialogue_rhythm_test[] = {
    /* ------------------------------------------------ */
        "说起来，\n你最近有做“节奏感测试”吗？\n",
    /* ------------------------------------------------ */
        "我偶尔也会去测，\n不过，65 分左右就是我的极限啦……\n",
    /* ------------------------------------------------ */
        "那个第二项测试呀，\n我怎么也做不好呢。",
    /* ------------------------------------------------ */
        "要去数空拍这种事，\n还真是挺难的呢〜。\n",
    /* ------------------------------------------------ */
        "不过嘛，就慢慢来吧。\n那，下回见。\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3b4] Dialogue - Drum Lessons
    /* -------------------------------- */
        //
        // Let me ask... have you tried the
        // Drum Lessons in the Prize Corner?
        //
    /* -------------------------------- */
        //
        // I take lessons once a week, but
        // I don't really seem to improve.
        //
    /* -------------------------------- */
        // The teacher is really strict.
        // I asked him for an easier
        // lesson, but he told me to
        // just keep on trying my best.
    /* -------------------------------- */
        //
        // You'll find it's hard to quit
        // once you start a lesson.
        //
    /* -------------------------------- */
        // Maybe it's for the best.
        // For musical instruments, you
        // just have to keep at it.
        // You should try your best, too.
    /* -------------------------------- */

const char *cafe_dialogue_drum_lessons[] = {
    /* ------------------------------------------------ */
        "说起来，奖励角里的击鼓课程，\n你玩过吗？\n",
    /* ------------------------------------------------ */
        "我每周会去上一次课，\n不过怎么也不见\n有多少长进呢。",
    /* ------------------------------------------------ */
        "老师也说过啦，\n这种事本来就各有所好，\n不用勉强自己。话虽如此——",
    /* ------------------------------------------------ */
        "可一旦开始上课呀，\n就还真有点停不下来呢〜。\n",
    /* ------------------------------------------------ */
        "不过嘛，乐器这种东西本来就不是一下子能变厉害的，\n还是耐下心来，慢慢练下去吧…",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3cc] Dialogue - Staying Up All Night
    /* -------------------------------- */
        //
        // By the way, right now
        // I'm terribly tired...
        //
    /* -------------------------------- */
        //
        // I was up all last night playing.
        // I just couldn't stop myself...
        //
    /* -------------------------------- */
        //
        // What? Oh, I was talking to myself.
        // It was a monologue... sorry.
        //
    /* -------------------------------- */
        //
        // Learn from me, and don't forget
        // to take a break every so often.
        // Anyway, see you again.
    /* -------------------------------- */

const char *cafe_dialogue_adhd[] = {
    /* ------------------------------------------------ */
        "说起来，\n我现在不知怎么的，特别困呀…\n",
    /* ------------------------------------------------ */
        "毕竟昨晚玩到很晚嘛…\n",
    /* ------------------------------------------------ */
        "啊，不，没什么，这是我自己的事。\n只是自言自语啦… 抱歉哦。\n",
    /* ------------------------------------------------ */
        "下次要不要去兜个风呢？\n不过，也得看你愿不愿意啦。\n那，下回见。",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3e0] Dialogue - Coffee
    /* -------------------------------- */
        //
        // By the way, here's the
        // coffee you ordered.
        //
    /* -------------------------------- */
        //
        // Hm? You didn't order it?
        // Ah, I see. This is actually
        // for the guy next to you...
    /* -------------------------------- */
        //
        // Well... he isn't a talkative person,
        // but you seem to be getting along.
        //
    /* -------------------------------- */
        //
        // All I can do is pour
        // the coffee, but... heh.
        //
    /* -------------------------------- */

const char *cafe_dialogue_coffee[] = {
    /* ------------------------------------------------ */
        "说起来，\n咖啡已经上好啦。\n",
    /* ------------------------------------------------ */
        "咦？你说你没点？ 啊，这个嘛，是旁边那位请的啦…\n",
    /* ------------------------------------------------ */
        "虽、虽然那位不太爱说话，\n但大概也是想跟你交个朋友吧？\n",
    /* ------------------------------------------------ */
        "我嘛，也就只会给人煮煮咖啡而已啦… 哈哈哈…\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd3f4] Dialogue - Dog
    /* -------------------------------- */
        //
        // By the way, if you hadn't
        // noticed, I'm actually a dog.
        //
    /* -------------------------------- */
        //
        // I'm not one of those young pups,
        // either. I'm nine years old.
        //
    /* -------------------------------- */
        //
        // When you get to be my age,
        // time really does seem to fly.
        //
    /* -------------------------------- */
        //
        // Hey, you're a human, right?
        // Well, despite our species I still
        // hope that we can get along
    /* -------------------------------- */

const char *cafe_dialogue_dog_barista[] = {
    /* ------------------------------------------------ */
        "说起来，\n其实啊，我是一只狗哦。\n",
    /* ------------------------------------------------ */
        "算起来我已经 9 岁了，\n也算一把年纪啦。",
    /* ------------------------------------------------ */
        "哎呀呀，到了这个年纪，\n时间过得可真快呢。\n",
    /* ------------------------------------------------ */
        "客人你是人类吧？\n虽然我是只狗，不过今后\n也请继续跟我好好相处哦〜。",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd408] Dialogue - Music
    /* -------------------------------- */
        //
        // By the way, what do
        // you do when you're sad?
        // I always listen to music.
    /* -------------------------------- */
        //
        // Taking out a good old record and
        // reminiscing about the past
        // always makes me feel better.
    /* -------------------------------- */
        //
        // Music is strange, isn't it?
        // It has this mysterious
        // power to heal the heart.
    /* -------------------------------- */
        //
        // Just don't think that good
        // rhythm makes you qualified
        // to be a doctor, ha ha ha.
    /* -------------------------------- */

const char *cafe_dialogue_healing_with_music[] = {
    /* ------------------------------------------------ */
        "说起来，难过的时候\n你会做什么呢？\n我呀，基本上就是听音乐呢。",
    /* ------------------------------------------------ */
        "把那些挺老的唱片翻出来，\n一边听一边回想当时的事，\n心里就会慢慢放松下来。",
    /* ------------------------------------------------ */
        "音乐真是很不可思议呢〜。\n为什么它能那样\n深深触动人的心呢。",
    /* ------------------------------------------------ */
        "不过嘛，那些详细道理\n我也不懂就是啦。哈哈哈。\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd41c] Dialogue - Speaking Through Rhythm
    /* -------------------------------- */
        //
        // Say... did you know that you can
        // have a conversation with rhythm?
        //
    /* -------------------------------- */
        //
        // By attaching words and meanings
        // to certain beats, you can have a
        // conversation without speaking.
    /* -------------------------------- */
        // For example... you could play
        // a drum beat to ask "How are
        // you?" or say "Please come
        // visit!" even from far away.
    /* -------------------------------- */
        //
        // I learned it from another
        // customer, and now I want
        // to try it for myself.
    /* -------------------------------- */
        // Then again, if we gave speeches
        // with bongos or the neighbors
        // argued with trumpets, it'd get
        // noisy, don't you think? Ha ha ha.
    /* -------------------------------- */

const char *cafe_dialogue_speaking_with_music[] = {
    /* ------------------------------------------------ */
        "说起来，\n你知道节奏也能拿来对话吗？\n",
    /* ------------------------------------------------ */
        "就是把不同的节奏型\n对应成话语和含义，\n然后用来交流的样子哦。\n",
    /* ------------------------------------------------ */
        "听说他们会用响亮的鼓声\n打出节奏，跟远处的人\n交流哦。",
    /* ------------------------------------------------ */
        "前阵子来店里的客人\n告诉我这件事时，\n我就觉得还挺有意思的，不是吗？",
    /* ------------------------------------------------ */
        "不过要是拿鼓来做竞选演说，\n或者夫妻俩拿邦戈鼓吵架的话，\n感觉会吵得不得了呢。哈哈哈。",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd434] Dialogue - Ranks and Medals
    /* -------------------------------- */
        //
        // By the way, have you ever
        // gotten a "Superb" rating on a game?
        //
    /* -------------------------------- */
        //
        // There are three grades, you know:
        // "Try Again", "OK" and "Superb".
        //
    /* -------------------------------- */
        //
        // If you get a "Superb",
        // you'll even get a medal.
        //
    /* -------------------------------- */
        // Collecting lots of medals will
        // unlock all sorts of prizes that
        // you can play with. Please do your
        // best to collect them all!
    /* -------------------------------- */
        //
        // Oh... but if you already knew that,
        // I'm sorry if I bored you.
        // See you later.
    /* -------------------------------- */

const char *cafe_dialogue_ranks_and_medals[] = {
    /* ------------------------------------------------ */
        "说起来，\n你有在游戏里拿过\n“高水准”这个评价吗？",
    /* ------------------------------------------------ */
        "游戏成绩一共有\n“再试一次吧”“平凡”“高水准”这三种哦。\n",
    /* ------------------------------------------------ */
        "然后呢，只要拿到“高水准”，\n就能得到奖牌哦。\n",
    /* ------------------------------------------------ */
        "收集奖牌之后，\n就能玩到各种各样的\n奖励内容，所以要加油收集哦。",
    /* ------------------------------------------------ */
        "如果你本来就知道的话，\n那我这番话可就有点无聊啦。\n不好意思哦，那下回见。\n",
    /* ------------------------------------------------ */
    END_OF_DIALOGUE
};


// [D_089cd44c] Random Dialogue Pool
const char **cafe_random_conversation_pool[] = {
    cafe_dialogue_rhythm_sense,
    cafe_dialogue_offbeats,
    cafe_dialogue_rhythm_test,
    cafe_dialogue_drum_lessons,
    cafe_dialogue_adhd,
    cafe_dialogue_coffee,
    cafe_dialogue_dog_barista,
    cafe_dialogue_healing_with_music,
    cafe_dialogue_speaking_with_music,
    cafe_dialogue_ranks_and_medals
};
