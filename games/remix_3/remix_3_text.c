/* 中文文本：本文件采用译文包中 stage 5 的已校对条目。
 * 字符串中的 \n 是游戏画面换行；相邻引号只是方便阅读源码。
 * 未校对或未定位的条目见 text/zh_hans/TODO_未校对.md。 */
#include "global.h"
#include "text.h"


/* Game Text - Remix 3 */


const char D_0806a010[] = "还得继续努力。";

const char D_0806a020[] = "简直太棒啦！！";

const char D_0806a03c[] = "判断还差点火候。";

const char D_0806a060[] = "判断真漂亮！";

const char D_0806a084[] = "再好好磨练一下吧。";

const char D_0806a0a0[] = "技术不错啊！";

const char D_0806a0b8[] = "来自神秘节奏组织的通告";

// 阶段 5 已校对：保留每行的显示控制字节和原有前导空格；末行的 \n 与居中码同样保留。
// TODO 未校对：歌名及署名在画面里的对齐、换行仍需模拟器或实机复核。
const char D_0806a0d4[] =
    "\x05\x31" "\x01\x35" " ♪　恋爱的Honey Sweet〜Angel";

const char D_0806a0fc[] =
    "\x05\x31" "\x01\x35" " 演唱　　時東　ぁみ";

const char D_0806a118[] =
    "\x05\x31" "\x01\x35" " 作词　作曲　　淳君♂";

const char D_0806a134[] =
    "\x05\x31" "\x01\x35" " 编曲　　鈴木Daichi秀行";

const char D_0806a154[] =
    "\n"
    "\x05\x31" "\x01\x35" "\x01\x43" "歌曲提供　　J.P.ROOM";
