# ZephyrOpsPlaybook

## 1. 概要

このページでは Linux 向け(WSL含む)の環境構築手順を示しています。

## 2. 環境構築

### 2.1. 事前準備
**Ubuntu 22.04 より古い Ubuntu の場合**、下記コマンドで apt 用リポジトリの追加を行います。

```
wget https://apt.kitware.com/kitware-archive.sh
sudo bash kitware-archive.sh
```

### 2.2. 必要なツールのインストール

下記コマンドで必要なツールをインストール(公式の手順と同じ)
```
sudo apt install --no-install-recommends git cmake ninja-build gperf \
  ccache dfu-util device-tree-compiler wget \
  python3-dev python3-pip python3-setuptools python3-tk python3-wheel xz-utils file \
  make gcc gcc-multilib g++-multilib libsdl2-dev libmagic1
```

うまく行かなかった場合は、下記公式ページを参照<br>
[Getting Started Guide: Install dependencies](https://docs.zephyrproject.org/4.0.0/develop/getting_started/index.html#install-dependencies)

### 2.3.リポジトリのクローン
作業用のディレクトリ zephyrproject を用意し、その中にこのリポジトリをクローン (zephyrproject と playbook は適宜変更してOK)
```
mkdir zephyrproject
cd zephyrproject
git clone https://github.com/Corgeek/ZephyrOpsPlaybook.git playbook
```

### 2.4. Zephyr 環境用の python 環境を構築
venv によりこのプロジェクト用の python 環境を作成

> [!IMPORTANT]
ここで行っている source .venv/bin/activate は、これを実行した Terminal 内でしか効果がありません。別の Terminal で以降の作業を行いたい場合は、その Terminal でも同じフォルダに移動して source .venv/bin/activate を実行する必要があります。
```
python3 -m venv .venv
source .venv/bin/activate
pip install west
```

### 2.5. Zephyr 専用の West 環境を構築
下記コマンドでこのプロジェクト専用の環境を構築

```
west init -l playbook
west update
pip install -r zephyr/scripts/requirements.txt
```

### 2.6. SDK のダウンロードと設定
Zephyr v4.0.0 から下記コマンドで SDK をインストールできるようになりました。インストール先はデフォルトだと` ${HOME}` 直下です。を指定する場合は `-b 任意の親ディレクトリ` で可能です。

```
west sdk install -t arm-zephyr-eabi -b ${HOME}
```

> [!NOTE]
今の所本リポジトリでは ARM 系向けに絞っているため、ツールチェインも ARM 向けに絞っています。`-t arm-zephyr-eabi` を無くせば全アーキテクチャ向けをインストールできます(約9.2GB)

### 2.7. west コマンドの簡略用スクリプトを準備

playbook/scripts/setup.sh をエディタで開き、下記ターゲットの設定を適宜変更して保存(最後のBOARD_TYPEが有効になります)。その後 setup.sh を実行
> BOARD_TYPE=bbc_microbit_v2
```
./scripts/setup.sh
```

問題がなければ、.vscode 用の設定と scripts 以下に west_env.bat, build.bat, debug.bat, stop.bat が生成されています。

以上で、初回の構築は完了です。

### 2.7. 最終的なディレクトリ構成

ディレクトリ構成(一部)は以下のようになっており、SDK 以外はすべてこの中に内包しています。
```
.
└── zephyrproject/
    ├── .venv/                    # venv 環境のファイル群
    ├── .vscode/                  # vscode 用のファイル群
    ├── .west/                    # このリポジトリ用の west 設定
    ├── bootloader/               # 特定のボードで使用するブートローダー
    ├── modules/                  # 各ベンダーの HAL 等
    ├── playbook/                 # 本リポジトリ
    │   ├── CMakeLists.txt        # CMake の先頭
    │   ├── README.md             # このドキュメント
    │   ├── .vscode/              # vscode 用のファイル群
    │   ├── boards/               # ターゲット依存のファイル群
    │   ├── core/                 # main.c やスレッドや共有メモリ関連
    │   ├── docs/                 # このドキュメントや補助的な資料
    │   ├── drivers/              # ドライバ関連
    │   ├── include/              # ヘッダーファイルはここに集約
    │   ├── prj.conf              # 汎用的な prj.conf
    │   ├── scripts/              # Bash / Command Prompt 用のスクリプト群
    │   └── west.yml              # west init -l で参照する設定
    └── zephyr/                   # 公式の Zephyr リポジトリ
```

## 3. 開発フロー
### 3.1. VS Code による開発
1. VS Code で zephyrproject ディレクトリを開く
   ```
   cd zephyrproject
   code .
   ```
2. Ctrl + Shift + B で、「Rebuild」もしくは「Build」を選びビルドを実施
3. 正常にビルドが完了したら Ctrl + Shift + B で出てくる「Flash」を選択し、実機に書き込む
4. gdb デバッガを用いたデバッグを行う場合は、Ctrl + Shift + B で出てくる「Debug」を選び gdbserver で待機状態に入る。その状態のまま F5 を押すことでアタッチ
   1. (VSCode のバージョンによっては、デバッグを終了後も gdbserver が待機状態のままになります。適宜画面右下の debug プロセスを終了(ゴミ箱アイコン)してください)

### 3.2. コマンドによる開発
playbook に移動しそれぞれ以下のコマンドを実行

| 機能 | コマンド |
|-----|----|
| Rebuild | ./scripts/build.bat /r |
| Build | ./scripts/build.bat |
| Flash | ./scripts/build.bat /f |
| Debug | ./scripts/debug.bat |

Debug 時は、port 3333 で待機しているので sdk 内にある gdb を用いてアタッチ

