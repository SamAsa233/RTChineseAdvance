/* 中文文本：本文件采用译文包中 stage 5 的已校对条目。
 * 字符串中的 \n 是游戏画面换行；相邻引号只是方便阅读源码。
 * 未校对或未定位的条目见 text/zh_hans/TODO_未校对.md。 */
#include "global.h"
#include "text.h"


/* Game Text - Toss Boys */


#ifdef PARADISE
const char D_0805d618[] = "看来还没练出成果啊。";

const char D_0805d634[] = "基本功很扎实！";
#else
const char D_0805d618[] = "You need to practice tossing more.";

const char D_0805d634[] = "Your tossing was impressive!";
#endif

const char D_0805d64c[] = "是不是有点着急了？";

const char D_0805d660[] = "挺沉着的嘛！";

const char D_0805d678[] = "跟上这个速度。";

const char D_0805d694[] = "这速度你已经跟得很稳啦！！";

const char D_0805d6b0[] = "教练的话";

#ifdef PARADISE
const char D_0805d6c4[] =
    "要上咯——！";
#else
const char D_0805d6c4[] =
    "\n"
    "Time to toss our best!";
#endif

const char D_0805d6d4[] =
    "结束啦。";

#ifdef PARADISE
const char D_0805d6e0[] = "看来还没练出成果啊。";

const char D_0805d6fc[] = "基本功很扎实！";
#else
const char D_0805d6e0[] = "You need to practice tossing more.";

const char D_0805d6fc[] = "Your tossing was impressive!";
#endif

const char D_0805d714[] = "是不是有点着急了？";

const char D_0805d728[] = "挺沉着的嘛！";

const char D_0805d740[] = "跟上这个速度。";

const char D_0805d75c[] = "这速度你已经跟得很稳啦！！";

const char D_0805d778[] = "教练的话";

const char D_0805d78c[] =
    "正式来咯——！";

const char D_0805d7a8[] =
    "结束啦。";

const char D_0805d7b4[] =
    "好伙伴一起练习中";

// 阶段 5 已校对：标题的画面换行与第二行前后八个显示控制字节都保留。
// TODO 未校对：三种必杀技名称在练习画面的第二行宽度仍需实机检查。
const char D_0805d7cc[] =
    "必杀技 1\n"
    "\x03\x31" "\x01\x6d" "\x05\x30" "\x01\x34" "AB 来回传球" "\x03\x30" "\x01\x73" "\x05\x34" "\x01\x38";

const char D_0805d7fc[] =
    "再来一次";

#ifdef PARADISE
const char D_0805d80c[] =
    "不错哦！";
#else
const char D_0805d80c[] =
    "\n"
    "Great tossing!";
#endif

const char D_0805d818[] =
    "必杀技 2\n"
    "\x03\x31" "\x01\x6d" "\x05\x30" "\x01\x34" "蓝色自传球" "\x03\x30" "\x01\x73" "\x05\x34" "\x01\x38";

const char D_0805d848[] =
    "再来一次〜";

const char D_0805d85c[] =
    "对对对！！";

const char D_0805d86c[] =
    "必杀技 3\n"
    "\x03\x31" "\x01\x6d" "\x05\x30" "\x01\x34" "黄色快传" "\x03\x30" "\x01\x73" "\x05\x34" "\x01\x38";

const char D_0805d8a0[] =
    "再来一次";

const char D_0805d8b0[] =
    "OK";

const char D_0805d8bc[] =
    "感觉已经挺不错了，";
