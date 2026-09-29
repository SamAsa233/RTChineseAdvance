/* 中文文本：本文件采用译文包中 stage 5 的已校对条目。
 * 字符串中的 \n 是游戏画面换行；相邻引号只是方便阅读源码。
 * 未校对或未定位的条目见 text/zh_hans/TODO_未校对.md。 */
#include "global.h"
#include "text.h"


/* Game Text - Rhythm Tweezers */


const char D_0805b490[] = "要好好拔干净哦。";

const char D_0805b4ac[] = "";

const char D_0805b4b0[] = "卷毛还没拔干净。";

const char D_0805b4d0[] = "卷毛拔得挺干净！";

const char D_0805b4ec[] = "毛多那块还留了不少啊。";

const char D_0805b510[] = "毛多的那块，已经拔得溜光了！";

const char D_0805b530[] = "多余毛发检查";

const char D_0805b544[] = "欢迎光临。";

const char D_0805b550[] = "用 A 键或十字键拔毛哦！";

// 阶段 5 已校对：保留四个原版显示控制字节，只把提示词换成中文。
// TODO 未校对：提示文字的字号与毛发检查画面位置仍需实机确认。
const char D_0805b580[] = "\x05\x30" "\x01\x34" "\x03\x31" "\x01\x6d" "OK";

// TODO 未校对：为保留原版 A 键和十字键图标，将译文“按钮”改成两个图标加“或”，需实机确认语义和字距。
const char D_0805b590[] = "\x05\x34" "\x01\x38" "\x03\x30" "\x01\x73" "那些卷的毛要长按"CHAR_A_BUTTON_UTF8"或"CHAR_DPAD_UTF8"，把它拽出来哦。";

const char D_0805b5c8[] = "\x05\x34" "\x01\x38" "\x03\x30" "\x01\x73" "毛太多的时候，两只手一起上会轻松些哦。";

const char D_0805b5f4[] = "\x05\x34" "\x01\x38" "\x03\x30" "\x01\x73" "那么，正式开始。";

const char D_0805b614[] = "要好好拔干净哦。";

const char D_0805b630[] = "";

const char D_0805b634[] = "卷毛还没拔干净。";

const char D_0805b654[] = "卷毛拔得挺干净！";

const char D_0805b670[] = "毛多那块还留了不少啊。";

const char D_0805b694[] = "毛多的那块，已经拔得溜光了！";

const char D_0805b6b8[] = "拔得超快！真能干！！";

const char D_0805b6e4[] = "多余毛发检查";
