"""Report unmatched C preprocessor branches in edited files.

汉化改动：检查翻译时碰到的 #if、#else 和 #endif 是否仍然成对。
PARADISE 与默认地区经常各有一份文本，少一个分支符号会导致某个版本无法编译或显示错误文字。

Example: python tools/text/check_preprocessor.py
"""

from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[2]
OPEN = re.compile(r'^\s*#\s*(?:if|ifdef|ifndef)\b')
CLOSE = re.compile(r'^\s*#\s*endif\b')
MIDDLE = re.compile(r'^\s*#\s*(?:else|elif)\b')


def check(path):
    depth = 0
    issues = []
    for line_number, line in enumerate(path.read_text(encoding='utf-8').splitlines(), 1):
        if OPEN.match(line):
            depth += 1
        elif CLOSE.match(line):
            if not depth:
                issues.append(f'{line_number}: unmatched endif')
            else:
                depth -= 1
        elif MIDDLE.match(line) and not depth:
            issues.append(f'{line_number}: unmatched else/elif')
    if depth:
        issues.append(f'EOF: {depth} unterminated if')
    return issues


def main():
    result = subprocess.run(['git', 'diff', '--name-only', 'text_utf8', '--', '*.c', '*.h', '*.bs'], cwd=ROOT, capture_output=True, text=True, check=True)
    bad = []
    for name in result.stdout.splitlines():
        path = ROOT / name
        if path.exists():
            issues = check(path)
            if issues:
                print(name, '; '.join(issues))
                bad.append(name)
    print(f'{len(bad)} files with unmatched preprocessor branches')
    raise SystemExit(bool(bad))


if __name__ == '__main__':
    main()
