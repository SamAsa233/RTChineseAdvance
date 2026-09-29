# 字库生成与检查

正文三档字体使用 Unicode U+4E00–U+9FFF 槽位，不改变 UTF-8 编码。每次从固定版本和 SHA-256 校验的 Fusion Pixel v2026.09.01 与 GNU Unifont 17.0.05 生成。压缩包与解压后的字体文件保存在忽略的 tools/font/third_party/；Fusion Pixel 的 OFL 许可文本保存在 third_party/LICENSES/。Unifont 的许可应随发行包一同核对。

## 实际用了哪些字体

当前 ROM 确实采用混合字库，没有把原游戏字体整套替换掉：

- 原游戏已有的英文、数字、假名、按钮图标和许多标点继续使用原生字模，以免改变按钮尺寸、界面风格和旧文本宽度。
- 简体中文汉字主要由 Fusion Pixel 生成，缺字时回退到 GNU Unifont；“蹑”另有手工 9×9 点阵修正。
- 外部字体只在制作 ROM 时由 fetch_fonts.py 下载、校验并转换成 GBA 点阵。生成后的字模会编译进 ROM，游戏运行时不联网，也不会读取电脑字体。

因此中英文在笔画粗细和造型上可能略有差异。这是补充原版缺少的中文字形后的真实效果。原游戏没有一套可直接复用的简体中文原生字库；若要进一步统一风格，需要继续逐字调整生成规则或手工字模。

## “标题 CJK 描边字体”和“稀疏字形缓存”

标题使用 16×16、4bpp 的字模。build_outline_font.py 先从开源字体取得汉字骨架，再生成字身、深色描边和阴影，使中文尽量接近原版标题的立体效果。“CJK”在这里指中日韩统一表意文字范围，本项目实际主要使用简体中文汉字。

“稀疏”表示只保存当前译文真正用到的码点和字模。例如译文用了“节、奏、天、国”，就记录这四个码点；不会为 U+4E00–U+9FFF 的两万多个位置全部塞入空字模。运行时先用码点表找到对应字形，再把当前要显示的 16×16 字模复制到 GBA 的图块显存。这里的“缓存”是 ROM/内存/显存中的字形复用表，不是网络缓存。

旧缓存只用 8 位字形序号，超过 255 个字后不同字可能得到相同编号。现在缓存键同时记录字号、字库区段和字形序号，所以扩展中文字库后仍能区分每个字。这样既节省 ROM 和显存，也避免标题显示成别的字。

依次运行：

1. python tools/font/fetch_fonts.py
2. python tools/text/pipeline.py extract
3. python tools/font/build_text_font.py --size all --charset build/text_report/charset.txt
4. python tools/font/build_outline_font.py
5. python tools/font/test_tengoku_font.py
6. python tools/text/check_text.py

正文字库覆盖 GB2312 与全部已提供译文的汉字，并补齐 U+2014 破折号。小号缺字优先用 12px Fusion Pixel 的点采样，再用 Unifont；中号缺字用 Unifont 点采样，避免旧版 OR 合并笔画造成“蹑”一类复杂字糊成实块。小号“蹑”另有 9×9 手工点阵，保留左右部件间的空列。明细见 build/font_report/{small,medium,large}.report.txt。build_text_font.py 产生的 bin/font/ 文件为构建输入。标题字体按译文用字生成稀疏码点表、4bpp 纹理及可选 PNG 预览，缺字和人工修图入口见 build_outline_font.py、outline_manual.txt。PNG 预览需要 Pillow，ROM 构建本身不需要。

每次更改译文后重跑提取、字库生成和校验，再构建 ROM。字距以代码为准：小号 1 像素，中/大号 2 像素；旧方案写的三档均 1 像素与当前源码不符。
