# 简体中文译文流水线

输入为 text/zh_hans/source/utf8/ 下的键控 JSON。2026-09-19 的译文包共 1,908 条；阶段 5 为 1,773 条。JSON 仅作译文数据。流水线将可定位的条目整理到 text/zh_hans/translations.tsv；默认只把 final 写回 C/Beatscript 源码，草稿保留在 TSV。

依次运行：

1. python tools/text/pipeline.py extract
2. python tools/text/pipeline.py resolve-controls
3. python tools/text/pipeline.py check
4. python tools/text/check_text.py
5. python tools/text/pipeline.py import

编辑 TSV 的 target 与 status 后，先运行 check 和 check_text.py。只有审核过的内容才改为 final。再次导入应输出 would import=0, problems=0。--include-draft 可在测试构建中导入草稿，正式构建不使用。

报告在 build/text_report/：unresolved.txt 是找不到安全源码位置的条目；import_problems.txt 是源文或数组结构变更；validation.txt 是缺字和控制码错误；layout_warnings.txt 列出待人工检查的控制码与可能超宽文本。报告为空或无错误不代表剩余条目已完成。条件编译分支、Haiku 共用正文以及嵌入式调色/字号控制码不能仅按位置机械替换。

导入时保留源代码的条件编译和注释；不确定的条目留在 unresolved.txt 或标记 control codes need review。若英文源文更新，人工核对 source 与目标源码，再重新提取，不要覆盖旧译文。
