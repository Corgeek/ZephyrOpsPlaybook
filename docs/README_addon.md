# ZephyrOpsPlaybook (minimal)

## 1. 機能概要
公式の手順を簡略・軽量化して、手軽に開発を始められる環境を提供することを目的としています。
* コマンドプロンプトと bash 両方で使えるようにしておき、VSCode によるデバッグ環境を提供
* ボード間の差異を減らし、移植性を維持した実装例の提案
* サンプルドライバ群も用意し、すぐにアプリケーション開発に注力できる環境を提供
* 開発の際はターゲットが決まっていることが多く、ターゲットを絞り込んだ環境構築の例示
* バージョンやリビジョンを固定して足並みをそろえた開発が必要で、その固定させる方法を提供

master ブランチは現在 v4.0.0 で固定していますが、LTS 版や最新環境で利用したい方向けに、下記ブランチも用意しています。

| ブランチ名 | 概要 |
|---|---|
| [dev/newest](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/dev/newest) | Zephyr 最新リビジョンベースの環境を構築 |
| [dev/minimal](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/dev/minimal) | Zephyr 最新リビジョンで、main 関数のみの最小構成の環境 |
| [dev/v3.7-branch](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/dev/v3.7-branch) | Zephyr の LTS 版である v3.7.0 ベースの環境 |

公式の Zephyr 環境が未構築の場合、下記 Ubuntu 向けか Windows 向けか、公式手順かを選んで作業を進めてください。

| 環境 | 概要 |
|------|------|
| [Ubuntu 向け](README.md) | Ubuntu ネイティブやWSLを含む仮想環境 |
| [Windows 向け](README_win.md) | コマンドプロンプトを使った Windows ネイティブ環境 |
| [Addon 向け](README_addon.md) | 公式の Zephyr 環境を既に構築済みで、それを流用したい場合(現在のページ) |
| [公式 Zephyr 手順](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) | まずは公式の Zephyr 環境を構築したい場合(約16GB) |

> [!TIP]
WSL は USB 機器の制御を理由に公式で推奨されていませんが、デバイスの管理等の知識がある方は一通り利用できます。<br>
また、そもそもターゲットをUSB経由で制御できる仕組みがない場合などは、Windows ネイティブより断然軽量な WSL を選択肢として考慮に入れて良いかもしれません。

## 2. 使い方

### 2.1. 事前の追加インストール

Zephyr の開発で利用する west flash / west debug では、かなりのボードが openocd で利用可能となっており、
こちらのインストールをしておくだけで数多くのボードの開発が容易になります。

#### 2.2.1. Windows 向け
**管理者権限**でコマンドプロンプトを開き、下記実行により openocd をインストール。

> [!IMPORTANT]
**管理者権限**は、「コマンドプロンプトを右クリック」から「管理者として実行」、もしくは「スタートキーを押しながら + X」 で出てくるコンテキストメニューから、「ターミナル(管理者)」でも開けます。また、**管理者権限**で行う作業はここで終わりです。ミスを避けるため閉じておきましょう。

```
choco install openocd
```

#### 2.3.2. Ubuntu 向け
下記コマンドで追加インストール
```
sudo apt-get install openocd
```

### 2.2.リポジトリのクローン
作業用のディレクトリ zephyrproject の中に本リポジトリをクローン(playbook は適宜変更してOK)
```
cd zephyrproject
git clone https://github.com/Corgeek/ZephyrOpsPlaybook.git playbook
git checkout origin/dev/minimal -b dev/minimal
```

### 2.3. west コマンドの簡略用スクリプトを準備
---
#### 2.3.1. Windows 向け

playbook\scripts\setup.bat をエディタで開き、下記ターゲットの設定を適宜変更して保存(最後のBOARD_TYPEが有効になります)。その後 setup.bat を実行
> set BOARD_TYPE=rpi_pico
```
scripts\setup.bat
```
---
#### 2.3.2. Ubuntu 向け
playbook/scripts/setup.sh をエディタで開き、下記ターゲットの設定を適宜変更して保存(最後のBOARD_TYPEが有効になります)。その後 setup.sh を実行
> BOARD_TYPE=rpi_pico
```
./scripts/setup.sh
```
---

問題がなければ、.vscode 用の設定と scripts 以下に west_env.bat, build.bat, debug.bat, stop.bat が生成されています。

以上で、初回の構築は完了です。

### 2.4. 最終的なディレクトリ構成

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
    │   ├── global/               # スレッド間で共有するバッファ
    │   ├── prj.conf              # 汎用的な prj.conf
    │   ├── scripts/              # Bash / Command Prompt 用のスクリプト群
    │   ├── utils/                # shell 等の補助機能群
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

