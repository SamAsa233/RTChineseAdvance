# 字库生成与检查

正文三档字体使用 Unicode U+4E00–U+9FFF 槽位，不改变 UTF-8 编码。每次从固定版本和 SHA-256 校验的 Fusion Pixel v2026.09.01 与 GNU Unifont 17.0.05 生成。压缩包与解压后的字体文件保存在忽略的 tools/font/third_party/；Fusion Pixel 的 OFL 许可文本保存在 third_party/LICENSES/。Unifont 的许可应随发行包一同核对。

依次运行：

1. python tools/font/fetch_fonts.py
2. python tools/text/pipeline.py extract
3. python tools/font/build_text_font.py --size all --charset build/text_report/charset.txt
4. python tools/font/build_outline_font.py
5. python tools/font/test_tengoku_font.py
6. python tools/text/check_text.py

正文字库覆盖 GB2312 与全部已提供译文的汉字，并补齐 U+2014 破折号。小号缺字优先用 12px Fusion Pixel 的点采样，再用 Unifont；中号缺字用 Unifont 点采样，避免旧版 OR 合并笔画造成“蹑”一类复杂字糊成实块。小号“蹑”另有 9×9 手工点阵，保留左右部件间的空列。明细见 build/font_report/{small,medium,large}.report.txt。build_text_font.py 产生的 bin/font/ 文件为构建输入。标题字体按译文用字生成稀疏码点表、4bpp 纹理及可选 PNG 预览，缺字和人工修图入口见 build_outline_font.py、outline_manual.txt。PNG 预览需要 Pillow，ROM 构建本身不需要。

每次更改译文后重跑提取、字库生成和校验，再构建 ROM。字距以代码为准：小号 1 像素，中/大号 2 像素；旧方案写的三档均 1 像素与当前源码不符。
