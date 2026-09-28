"""Fetch pinned open-source bitmap fonts into third_party.

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
    "fusion-10.zip": "https://github.com/TakWolf/fusion-pixel-font/releases/download/2026.09.01/fusion-pixel-font-10px-proportional-bdf-v2026.09.01.zip",
    "fusion-12.zip": "https://github.com/TakWolf/fusion-pixel-font/releases/download/2026.09.01/fusion-pixel-font-12px-proportional-bdf-v2026.09.01.zip",
    "unifont.hex.gz": "https://unifoundry.com/pub/unifont/unifont-17.0.05/font-builds/unifont-17.0.05.hex.gz",
}


def atomic_bytes(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temp = path.with_name(path.name + ".tmp")
    temp.write_bytes(data)
    os.replace(temp, path)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--dir", type=Path, default=ROOT)
    args = parser.parse_args()
    root = args.dir
    root.mkdir(parents=True, exist_ok=True)
    for name, url in SOURCES.items():
        path = root / name
        if not path.exists() or (name.endswith('.gz') and path.read_bytes()[:2] != b'\x1f\x8b'):
            with urlopen(url, timeout=120) as response:
                atomic_bytes(path, response.read())
        if name.endswith('.gz') and path.read_bytes()[:2] != b'\x1f\x8b':
            subprocess.run(["curl", "--fail", "--location", "--silent", "--show-error", url, "--output", str(path)], check=True)
            if path.read_bytes()[:2] != b'\x1f\x8b':
                raise ValueError(f"invalid gzip download: {url}")
        print(name, len(path.read_bytes()), hashlib.sha256(path.read_bytes()).hexdigest())
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
