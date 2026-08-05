# 编译指南

### 前置要求

在开始编译前，你需要先准备这些东西：
- 一份 **Rev 0版** 的节奏天国 (CRC32: `349D7025`)
- Git
- Python 3

### 平台设置

#### Windows

你需要先安装WSL，你可以参考这篇[教程](https://learn.microsoft.com/zh-cn/windows/wsl/install)进行安装，我们推荐您使用Ubuntu或Debian这两个发行版。

接下来请按照Linux的设置步骤完成

#### Linux

安装所需软件包 (Ubuntu/Debian):
```bash
sudo apt update
sudo apt install build-essential binutils-arm-none-eabi git libpng-dev ffmpeg python3
```

安装devkitPro:
```bash
wget https://www.shaffy.fr/install-devkitpro-pacman
chmod +x ./install-devkitpro-pacman
sudo ./install-devkitpro-pacman
```

#### macOS

请先安装[Homebrew](https://brew.sh/)，然后安装所需的软件包：
```bash
xcode-select --install
brew install libpng ffmpeg python
```

从[devkitPro/pacman releases](https://github.com/devkitPro/pacman/releases)里下载`devkitpro-pacman-installer.pkg`，然后执行这个命令安装：
```bash
sudo installer -pkg /path/to/devkitpro-pacman-installer.pkg -target /
```

安装 devkitPro pacman 后打开一个新终端，或将其添加到当前 shell：
```bash
export PATH=/opt/devkitpro/pacman/bin:$PATH
```

### 编译步骤

#### 设置环境变量

设置devkitPro的环境变量:
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=/opt/devkitpro/devkitARM
export DEVKITPPC=/opt/devkitpro/devkitPPC
```

若要在今后的终端中保留这些设置，请将它们添加到你的 shell 配置文件中。macOS默认的终端请使用以下命令：
```bash
echo 'export DEVKITPRO=/opt/devkitpro' >> ~/.zshrc
echo 'export DEVKITARM=/opt/devkitpro/devkitARM' >> ~/.zshrc
echo 'export DEVKITPPC=/opt/devkitpro/devkitPPC' >> ~/.zshrc
echo 'export PATH=/opt/devkitpro/pacman/bin:$PATH' >> ~/.zshrc
```

如果你的终端是bash，请把`~/.zshrc`替换成`~/.bashrc`。

#### 安装GBA开发套件

```bash
sudo dkp-pacman -Sy
sudo dkp-pacman -S gba-dev
```

#### 克隆仓库并编译

1. **克隆此仓库：**
   ```bash
   git clone https://github.com/SamAsa233/RTChineseAdvance.git
   ```

2. **设置agbcc：**
   ```bash
   git clone https://github.com/pret/agbcc.git
   cd agbcc
   ./build.sh
   ./install.sh ../RTChineseAdvance
   cd ../RTChineseAdvance
   ```

3. **放置你的ROM：**
   - 把*节奏天国*的ROM复制到项目根目录里
   - 把它重命名为`baserom.gba`

4. **编译项目：**
   
   Linux：
   ```bash
   make -j$(nproc)
   ```

   macOS：
   ```bash
   make -j$(sysctl -n hw.logicalcpu)
   ```

编译生成的 ROM 将输出在`build/rhythmtianguo.gba`。