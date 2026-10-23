/* 中文文本：本文件采用译文包中 stage 5 的已校对条目。
 * 字符串中的 \n 是游戏画面换行；相邻引号只是方便阅读源码。
 * 未校对或未定位的条目见 text/zh_hans/TODO_未校对.md。 */
#include "global.h"
#include "text.h"


/* Game Text - Rap Men */


const char D_0805e914[] = "“……吗？”这段节奏还没跟上。";

const char D_0805e938[] = "“……吗？”这段节奏跟得真准！";

const char D_0805e960[] = "“……吧”这段还有点生硬。";

const char D_0805e988[] = "“……吧”这段真有感觉！";

const char D_0805e9ac[] = "“最棒啦！”这段还不够棒啊。";

const char D_0805e9d8[] = "“最棒啦！”这段简直棒极啦！";

const char D_0805ea04[] = "那两位的点评";

const char D_0805ea18[] = "那就正式上吧";

const char D_0805ea34[] = "下次再一起玩啊";

const char D_0805ea44[] = "哟!";

const char D_0805ea50[] = "来,跟我们一起嗨吧";

const char D_0805ea6c[] = "我们来教你怎么跟上节奏";

const char D_0805ea84[] = "听到“嗯”那一下就按 A 键";

const char D_0805eaac[] = "先听一遍吧";

const char D_0805eac4[] = "懂了吗？";

const char D_0805ead0[] = "来，试试看";

const char D_0805eae8[] = "加把劲啊";

const char D_0805eaf8[] = "就是“嗯”那一下哦〜";

// 阶段 5 已校对 D_0805eb14：原地区分支措辞不同，中文译文相同；两侧都要更新，避免默认版仍显示英文。
#ifdef BRIT
const char D_0805eb14[] = "都说了是“嗯”那一下啦";
#else
const char D_0805eb14[] = "都说了是“嗯”那一下啦";
#endif

const char D_0805eb34[] = "OK！";

// 阶段 5 已校对：把原版变色码留在引号内的节奏名两侧，仅替换可见文字。
// TODO 未校对：中文提示中彩色词的高亮范围仍需在 Rap Men 教学画面核验。
const char D_0805eb3c[] = "刚才练的，就是“" ".b……吗？.8" "”这种节奏。";

const char D_0805eb6c[] = "接下来是“" ".9……吧.8" "”这种节奏。";

const char D_0805eb94[] = "先听一遍吧";

const char D_0805ebac[] = "那就，来吧";

const char D_0805ebc4[] = "最后一种，是“" ".a……最棒啦！.8" "”的节奏";

const char D_0805ebf4[] = "这个也先听一遍吧";

const char D_0805ec0c[] = "好，来吧";

const char D_0805ec24[] = "OK！真是" ".a棒极啦！.8";
