# ZephyrOpsPlaybook

## 1. 概要

このページでは Windows 向けの環境構築手順を示しています。

## 2. 環境構築

### 2.1. 事前準備
開発に必要なツール群のインストールを行います。

### 2.2. 必要なツールのインストール
1. chocolatery のインストール ([公式参照](https://chocolatey.org/install))
2. **管理者権限**でコマンドプロンプトを開き、下記実行により必要なツールをインストール。
(公式手順に加えて openocd も指定してあります。書き込みやデバッグに於いて数多くのボードをサポートしており、追加インストール推奨です)

> [!IMPORTANT]
**管理者権限**は、「コマンドプロンプトを右クリック」から「管理者として実行」、もしくは「スタートキーを押しながら + X」 で出てくるコンテキストメニューから、「ターミナル(管理者)」でも開けます。また、**管理者権限**で行う作業はここで終わりです。ミスを避けるため閉じておきましょう。

```
choco feature enable -n allowGlobalConfirmation
choco install cmake --installargs 'ADD_CMAKE_TO_PATH=System'
choco install ninja gperf python311 git dtc-msys2 wget 7zip
choco install openocd
```

うまく行かなかった場合は、下記公式ページを参照。<br>
[Getting Started Guide: Install dependencies](https://docs.zephyrproject.org/4.0.0/develop/getting_started/index.html#install-dependencies)

### 2.3.リポジトリのクローン
> [!IMPORTANT]
ここからは通常のコマンドプロンプトを開いて作業をします。

作業用のディレクトリ zephyrproject を用意し、その中にこのリポジトリをクローン。<br>(zephyrproject と playbook は適宜変更してOK)
```
mkdir zephyrproject
cd zephyrproject
git clone https://github.com/Corgeek/ZephyrOpsPlaybook.git playbook -b stm32
```

### 2.4. Zephyr 環境用の python 環境を構築
venv によりこのプロジェクト用の python 環境を作成

> [!IMPORTANT]
ここで行っている .venv\Scripts\activate は、これを実行したコマンドプロンプト内でしか効果がありません。<br>別のウィンドウで以降の作業を行いたい場合は、そのウィンドウでも同じフォルダに移動して .venv\Scripts\activate を実行する必要があります。
```
python -m venv .venv
.venv\Scripts\activate
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
Zephyr v4.0.0 から下記コマンドで SDK をインストールできるようになりました。

```
west sdk install -t arm-zephyr-eabi -b %SystemDrive%
```

> [!CAUTION]
インストール先未指定だとユーザーフォルダ直下にインストールされますが、ユーザー名にスペース文字を含んでいるとビルド時にエラーが発生します(e.g. ユーザー名：Yamada Taro)。無難な回避策は `-b C:\` でC:ドライブ直下にインストールです。(`-b C:\Program Files\` でもOKですが管理者権限が必要)

> [!NOTE]
今の所本リポジトリでは ARM 系向けに絞っているため、ツールチェインも ARM 向けに絞っています。`-t arm-zephyr-eabi` を無くせば全アーキテクチャ向けをインストールできます(約9.2GB)

### 2.7. west コマンドの簡略用スクリプトを準備

playbook\scripts\setup.bat をエディタで開き、下記ターゲットの設定を適宜変更して保存(最後のBOARD_TYPEが有効になります)。その後 setup.bat を実行
> set BOARD_TYPE=nucleo_f401re
```
scripts\setup.bat
```

問題がなければ、.vscode 用の設定と scripts 以下に west_env.bat, build.bat, debug.bat, stop.bat が生成されています。

以上で、初回の構築は完了です。

### 2.8. 最終的なディレクトリ構成

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
    │   ├── modules/              # MCUよりも広範囲なベンダー固有機能を使った関数群
    │   ├── include/              # ヘッダーファイルはここに集約
    │   ├── prj.conf              # 汎用的な prj.conf
    │   ├── scripts/              # Bash / Command Prompt 用のスクリプト群
    │   ├── utils/                # 汎用・便利機能、ユーティリティ
    │   └── west.yml              # west init -l で参照する設定
    └── zephyr/                    # 公式の Zephyr リポジトリ
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

<img width=90% alt="Image" src="https://github.com/user-attachments/assets/f3828f7d-cd9e-4650-a645-6fb811e70a29" />
