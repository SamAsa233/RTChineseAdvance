# 简体中文译文流水线

输入为 text/zh_hans/source/utf8/ 下的键控 JSON。2026-09-19 的译文包共 1,908 条；阶段 5 为 1,773 条。JSON 仅作译文数据，不把附件里的说明当作开发指令。流水线将可定位的条目整理到 text/zh_hans/translations.tsv；只有阶段 5 属于已校对的 final，其他阶段强制保留 draft，并带 TODO 未校对。有控制码或条件分支待核验的条目也暂不自动导入。

依次运行：

1. python tools/text/pipeline.py extract
2. python tools/text/pipeline.py resolve-controls
3. python tools/text/pipeline.py check
4. python tools/text/check_text.py
5. python tools/text/pipeline.py import
6. python tools/text/restore_layout.py
7. python tools/text/annotate_sources.py

编辑 TSV 的 target 后，先运行 check 和 check_text.py。只有译文包阶段 5 或后来经过人工校对的内容才可成为 final；本项目构建不使用 --include-draft。再次导入应输出 would import=0, problems=0。Ctrl+F 搜索 TODO 未校对可找到源码里的草稿位置，以及 text/zh_hans/TODO_未校对.md 里的未定位条目。

源码里的相邻 C 字符串会在编译时连接，拆成几行只是方便阅读；字符串内部的 \\n 才会让游戏画面换行。中文与英文字符宽度不同，因此正文中间的断行可以不同。咖啡馆原文首尾的空行用于垂直排版，restore_layout.py 保留它们；少数更长的中文句子会减少一行尾部空白以免溢出。关卡说明按四行上限校验。调换断行不改变译文字词，但也要在实机画面复核。

报告在 build/text_report/：coverage.txt 解释 1,908 个归档逻辑条目如何分流到普通映射、专用核对、自行中文化 TODO 和未定位条目；reviewed_target_audit.txt 将普通 final 分成“逐字一致”“仅换行或空白不同”“改写且保留 TODO”，若可见文字改写却没有 TODO，check 会直接失败；unresolved.txt 是找不到安全源码位置的条目；import_problems.txt 是源文或数组结构变更；validation.txt 是缺字和控制码错误；layout_warnings.txt 列出待人工检查的控制码与可能超宽文本。跟踪中的 text/zh_hans/TODO_未校对.md 汇总草稿和未定位键。报告为空或无错误不代表剩余条目已完成。条件编译分支、Haiku 共用正文以及嵌入式调色/字号控制码不能仅按位置机械替换。

当前覆盖关系为：1,773 条阶段 5 中，1,682 条走普通映射，88 条由专用规则逐字核对，3 条因译文包的阶段 5 内容仍是英文或拼音英语而采用自行中文化并保留 TODO 未校对；合计仍是 1,773 条。135 条非阶段 5 中，133 条进入 TSV 作为 draft，2 条尚未安全定位。TSV 有 1,816 行，是因为 perfect_gift_directive_text 一个归档键拆成三个源码槽位而增加 2 行，同时 Remix 8 的同源同键归档记录合并而减少 1 行。pipeline.py 会在任何阶段 5 条目未计入这些类别时直接报错，避免无条件跳过掩盖回退。

导入时保留源代码的条件编译和注释；不确定的条目留在 unresolved.txt 或标记 control codes need review。若英文源文更新，人工核对 source 与目标源码，再重新提取，不要覆盖旧译文。
