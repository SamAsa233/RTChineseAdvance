"""Fetch pinned open-source bitmap fonts into third_party.

汉化改动：下载固定版本的 Fusion Pixel 和 GNU Unifont，并用 SHA-256 校验文件。
固定版本和校验值可以避免不同电脑或不同日期生成出不一样的中文字模。

Example: python tools/font/fetch_fonts.py
"""

import argparse
from pathlib import Path
from urllib.request import urlopen
from zipfile import ZipFile
import gzip
import hashlib
import os
import subprocess

ROOT = Path(__file__).resolve().parent / "third_party"
SOURCES = {
    "fusion-10.zip": ("https://github.com/TakWolf/fusion-pixel-font/releases/download/2026.09.01/fusion-pixel-font-10px-proportional-bdf-v2026.09.01.zip",
                      "5aa9d46e5ddb0d11d0406426a47922d45bf119edf819cbf2dab5438006990705"),
    "fusion-12.zip": ("https://github.com/TakWolf/fusion-pixel-font/releases/download/2026.09.01/fusion-pixel-font-12px-proportional-bdf-v2026.09.01.zip",
                      "f5a2e2326857eded4159f361de7f85dffc31384c20bdeb7e4d41d91e4043c563"),
    "unifont.hex.gz": ("https://unifoundry.com/pub/unifont/unifont-17.0.05/font-builds/unifont-17.0.05.hex.gz",
                       "2ae5311c8e123e9e85f5331cd012aa99757071df23243f1487fdbf8f3acd86be"),
}


def atomic_bytes(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + ".tmp")
    temp.write_bytes(data)
    os.replace(temp, path)


def fetch_verified(path: Path, url: str, digest: str) -> None:
    if path.exists() and hashlib.sha256(path.read_bytes()).hexdigest() == digest:
        return
    try:
        with urlopen(url, timeout=120) as response:
            data = response.read()
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError('download checksum mismatch')
    except (OSError, ValueError):
        temp = path.with_name(path.name + '.download')
        try:
            subprocess.run(['curl', '--fail', '--location', '--silent', '--show-error',
                            url, '--output', str(temp)], check=True)
            data = temp.read_bytes()
        finally:
            temp.unlink(missing_ok=True)
        if hashlib.sha256(data).hexdigest() != digest:
            raise ValueError(f'checksum mismatch for {path.name}')
    atomic_bytes(path, data)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dir", type=Path, default=ROOT)
    args = parser.parse_args()
    root = args.dir
    root.mkdir(parents=True, exist_ok=True)
    for name, (url, digest) in SOURCES.items():
        path = root / name
        fetch_verified(path, url, digest)
        print(name, len(path.read_bytes()), digest)
    for pixel_size in (10, 12):
        with ZipFile(root / f"fusion-{pixel_size}.zip") as archive:
            names = archive.namelist()
            wanted = next(name for name in names if name.endswith(f"fusion-pixel-{pixel_size}px-proportional-zh_hans.bdf"))
            atomic_bytes(root / f"fusion-{pixel_size}.bdf", archive.read(wanted))
            licenses = [name for name in names if name.endswith("OFL.txt")]
            if licenses:
                atomic_bytes(root / "LICENSES" / "FusionPixel-OFL.txt", archive.read(licenses[0]))
    with gzip.open(root / "unifont.hex.gz", "rb") as source:
        atomic_bytes(root / "unifont.hex", source.read())


if __name__ == "__main__":
    main()
