# ZephyrOpsPlaybook

## 1. 機能概要
こちらの README は、既に公式の環境を構築済みで、アドオン形式で本リポジトリを利用したい方に向けた手順となります。
以降は公式環境が zephyrproject にある場合の説明になりますが、ディレクトリ名を変えている場合は適宜それに合わせてください。

アドオン形式で進めた場合、以下の部分的な機能が使えます。
* VS Code を使った Rebuild / Flash / Debug
* Zephyr 公式環境と分離した開発環境
* ディレクトリ構成案や CMakeList.txt の管理方法案

公式の Zephyr 環境が未構築の場合、下記 Ubuntu 向けか Windows 向けかを選んで作業を進めてください。

| 目的 | 概要 |
|------|------|
| [Ubuntu 向け](README.md) | Ubuntu ネイティブやWSLを含む仮想環境 |
| [Windows 向け](README_win.md) | コマンドプロンプトを使った Windows ネイティブ環境 |
| [Addon 向け](README_addon.md) | 公式の Zephyr 環境を既に構築済みで、それを流用したい場合(現在のページ) |
| [公式 Zephyr 手順](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) | まずは公式の Zephyr 環境を構築したい場合(約16GB) |

> [!TIP]
WSL は USB 機器の制御を理由に公式で推奨されていませんが、デバイスの管理等の知識がある方は一通り利用できます。<br>
また、そもそもターゲットをUSB経由で制御できる仕組みがない場合などは、Windows ネイティブより断然軽量な WSL を選択肢として考慮に入れて良いかもしれません。

## 2. 使い方

### 2.1.リポジトリのクローン
作業用のディレクトリ zephyrproject の中に本リポジトリをクローン(playbook は適宜変更してOK)
```
cd zephyrproject
git clone https://github.com/Corgeek/ZephyrOpsPlaybook.git playbook
```

### 2.2. west コマンドの簡略用スクリプトを準備
---
#### 2.2.1. Windows 向け

playbook\scripts\setup.bat をエディタで開き、下記ターゲットの設定を適宜変更して保存(最後のBOARD_TYPEが有効になります)。その後 setup.bat を実行
> set BOARD_TYPE=bbc_microbit_v2
```
scripts\setup.bat
```
---
#### 2.2.2. Ubuntu 向け
playbook/scripts/setup.sh をエディタで開き、下記ターゲットの設定を適宜変更して保存(最後のBOARD_TYPEが有効になります)。その後 setup.sh を実行
> BOARD_TYPE=bbc_microbit_v2
```
./scripts/setup.sh
```
---

問題がなければ、.vscode 用の設定と scripts 以下に west_env.bat, build.bat, debug.bat が生成されています。

以上で、初回の構築は完了です。

### 2.3. 最終的なディレクトリ構成

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
    │   ├── drivers/              # ドライバ関連
    │   ├── include/              # ヘッダーファイルはここに集約
    │   ├── prj.conf              # 汎用的な prj.conf
    │   ├── scripts/              # Bash / Command Prompt 用のスクリプト群
    │   ├── utils/                # shell 等の補助機能群
    │   └── west.yml              # west init -l で参照する設定
    ├── tools/                    # Test ツールやその補助設定ファイル
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

### 3.2. コマンドによる開発
playbook に移動しそれぞれ以下のコマンドを実行

| 機能 | コマンド |
|-----|----|
| Rebuild | ./scripts/build.bat /r |
| Build | ./scripts/build.bat |
| Flash | ./scripts/build.bat /f |
| Debug | ./scripts/debug.bat |

Debug 時は、port 3333 で待機しているので sdk 内にある gdb を用いてアタッチ

