/* 中文文本：本文件采用译文包中 stage 5 的已校对条目。
 * 字符串中的 \n 是游戏画面换行；相邻引号只是方便阅读源码。
 * 未校对或未定位的条目见 text/zh_hans/TODO_未校对.md。 */
#include "global.h"
#include "text.h"


/* Game Text - Night Walk */


const char D_0805b158[] = "掉下去啦…";

const char D_0805b174[] = "顺利到终点啦！！";

const char D_0805b18c[] = "节奏有点乱了啊…";

const char D_0805b1a4[] = "节奏保持得不错！";

const char D_0805b1bc[] = "有几处关键节拍没踩准呢。";

const char D_0805b1dc[] = "关键节拍踩得真准！";

const char D_0805b1f4[] = "星星的声音";

// 阶段 5 已校对：前面的 05 31 / 01 35 是显示控制字节，不是英文；保留它们，只替换玩家看到的提示。
// TODO 未校对：中文在气泡内的字号与换行仍需模拟器或实机确认。
const char D_0805b1fc[] = "\x05\x31" "\x01\x35" "跟着音乐跳起来哦！";

const char D_0805b220[] = "\x05\x31" "\x01\x35" "要在音乐结束前，让画面铺满星星哦！";

const char D_0805b250[] = "\x05\x31" "\x01\x35" "快结束啦！";

const char D_0805b26c[] = "掉下去啦…";

const char D_0805b288[] = "顺利到终点啦！！";

const char D_0805b2a0[] = "节奏有点乱了啊…";

const char D_0805b2b8[] = "节奏保持得不错！";

const char D_0805b2d0[] = "有几处关键节拍没踩准呢。";

const char D_0805b2f0[] = "关键节拍踩得真准！";

const char D_0805b308[] = "星星的声音";

// 夜间漫步 2 复用同样的提示与控制字节；译文包中的阶段 5 文字分别接入。
const char D_0805b310[] = "\x05\x31" "\x01\x35" "跟着音乐跳起来哦！";

const char D_0805b334[] = "\x05\x31" "\x01\x35" "别撞到电击鱼哦！";

// TODO 未校对：译文包没有 D_0805b335，先保留英文，避免擅自把相邻提示的译文套到这句。
const char D_0805b335[] = "\x05\x31" "\x01\x35" "Don't jump when you're under them!";

const char D_0805b35c[] = "\x05\x31" "\x01\x35" "要在音乐结束前，让画面铺满星星哦！";

const char D_0805b38c[] = "\x05\x31" "\x01\x35" "快结束啦！";
