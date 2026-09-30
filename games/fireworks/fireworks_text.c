/* 中文文本：本文件采用译文包中 stage 5 的已校对条目。
 * 字符串中的 \n 是游戏画面换行；相邻引号只是方便阅读源码。
 * 未校对或未定位的条目见 text/zh_hans/TODO_未校对.md。 */
#include "global.h"
#include "text.h"


/* Game Text - Fireworks */


const char D_0805cd60[] = "再放得华丽一点吧！";

const char D_0805cd7c[] = "这烟火放得真漂亮！！";

// 阶段 5 已校对 D_0805cda0：原版英美地区措辞不同；两个分支都要接入同一句中文，不能只校第一侧。
#ifdef PARADISE
const char D_0805cda0[] = "反应太慢啦！";
#else
const char D_0805cda0[] = "反应太慢啦！";
#endif

const char D_0805cdb4[] = "反应不错嘛！";

const char D_0805cdc8[] = "师傅的话";

const char D_0805cde0[] = "・・・　祭典之前　・・・";

const char D_0805ce00[] = "特训开始！";

const char D_0805ce10[] = "听到“嘿！”这个信号时就按 A 键"CHAR_A_BUTTON_UTF8;

const char D_0805ce34[] = "首先是“普通的烟火”";

// 阶段 5 已校对：保留四个逐拍变色控制码，按“一、二、三、嘿”对应拆开中文；只换可见文字。
// TODO 未校对：颜色变化和字距仍需在烟火教学画面核验。
const char D_0805ce5c[] =
    ".b" "一 "
    ".b" "二 "
    ".b" "三  "
    ".b" "嘿!";

const char D_0805ce80[] =
    ".b" "一 "
    ".b" "二 "
    ".b" "三  "
    ".b" "嘿!";

const char D_0805cea4[] =
    ".b" "一 "
    ".b" "二 "
    ".b" "三  "
    ".b" "嘿!";

const char D_0805cec8[] =
    ".b" "一 "
    ".b" "二 "
    ".b" "三  "
    ".b" "嘿!";

const char D_0805ceec[] =
    ".b" "一 "
    ".b" "二 "
    ".b" "三  "
    ".b" "嘿!";

const char D_0805cf10[] = "“有气势的烟火”";

// 阶段 5 已校对：五个控制码分别对应“嘿、咿、！、间隔、嘿！”，不移动原有变色节拍。
// TODO 未校对：中文感叹词的逐拍显示位置仍需实机复核。
const char D_0805cf2c[] =
    ".b" "嘿"
    ".b" "咿"
    ".b" "!"
    ".b" "  "
    ".b" "嘿!";

const char D_0805cf4c[] =
    ".d" "嘿"
    ".b" "咿"
    ".b" "!"
    ".b" "  "
    ".b" "嘿！";

const char D_0805cf6c[] =
    ".b" "嘿"
    ".b" "咿"
    ".b" "!"
    ".b" "  "
    ".b" "嘿!";

const char D_0805cf8c[] =
    ".b" "嘿"
    ".b" "咿"
    ".b" "!"
    ".b" "  "
    ".b" "嘿!";

const char D_0805cfac[] =
    ".b" "嘿"
    ".b" "咿"
    ".b" "!"
    ".b" "  "
    ".b" "嘿!";

const char D_0805cfcc[] =
    ".b" "嘿"
    ".b" "咿"
    ".b" "!"
    ".b" "  "
    ".b" "嘿!";

const char D_0805cfec[] = "“压轴的太鼓爆破”";

// 阶段 5 已校对：“玉屋〜”按原有四段或五段控制码切开，结尾“嘿！”仍在原位置。
// TODO 未校对：长音与结尾间隔的画面效果仍需实机复核。
const char D_0805d010[] =
    ".b" "玉"
    ".b" "屋"
    ".b" "~  "
    ".b" "嘿!";

const char D_0805d030[] =
    ".b" "玉"
    ".b" "屋"
    ".b" "~  "
    ".b" "嘿!";

const char D_0805d050[] =
    ".b" "玉"
    ".b" "屋"
    ".b" "~  "
    ".b" "嘿!";

const char D_0805d070[] =
    ".b" "玉"
    ".b" "屋"
    ".b" "~  "
    ".b" "嘿!";

const char D_0805d090[] =
    ".b" "玉"
    ".b" "屋"
    ".b" "~  "
    ".b" "嘿!";

const char D_0805d0b0[] =
    ".b" "玉"
    ".b" "屋"
    ".b" "~  "
    ".b" "嘿!";

const char D_0805d0d0[] = "好,那就正式开始!";

const char D_0805d0e8[] = "这次可没有信号哦…";
