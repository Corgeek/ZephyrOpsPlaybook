# ZephyrSkeleton

## 機能概要
公式の手順を簡略・軽量化して、手軽に開発を始められる環境を目的としています。
* 開発の際はターゲットが決まっていることが多く、データ削減やCIの短縮化などを想定した環境を用意
* バージョンやリビジョンを固定して足並みをそろえた開発が必要で、その固定させた環境を用意(現時点で最新のLTS v3.7.0)
* コマンドプロンプトと bash 両方で使えるようにしておき、VSCode によるデバッグ環境も用意

> 注意：Nov.2024 時点で LTS v3.7.0 と Zephyr-SDK-1.7.0 は相性が悪く一部ビルド時にエラーが出ます。エラーが発生する場合は、Zephyr-SDK-1.6.8 の使用を推奨です。

## 使い方

### 事前準備

公式の環境構築を1度も行っていない場合、事前に下記のツールをインストールしておくこと

[Getting Started Guide: Install dependencies](https://docs.zephyrproject.org/3.7.0/develop/getting_started/index.html#install-dependencies)


1. 作業用のディレクトリ zephyrproject (場所や名称は変更可)を用意し、その中に本リポジトリをクローン
```
mkdir zephyrproject
cd zephyrproject
git clone https://github.com/Corgeek/ZephyrSkeleton.git skeleton
```

2. pyenv により本プロジェクト用の python 環境を作成
```
python -m venv .venv
.venv\Scripts\activate.bat
pip install west
```

3. ターゲットを絞り、v3.7.0 に固定した設定 west.yml を参照させて、本プロジェクト専用の環境を構築
```
west init -l skeleton
west update
pip install -r zephyr-env\zephyr\scripts\requirements.txt
```

4. v3.7.0 向けに Zephyr-SDK-1.6.8 をダウンロードして適宜配置。複数の SDK が存在する場合、新しい方を自動的に利用するため、バージョンの組み合わせに注意

* [Windows 向け SDK](https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.8/zephyr-sdk-0.16.8_windows-x86_64.7z)。解凍先は %homepath% 推奨。解凍後 setup.cmd を実行
* [Linux 向け SDK](https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.8/zephyr-sdk-0.16.8_linux-x86_64.tar.xz)。解凍先は /opt 推奨。解凍後 setup.sh を実行

5. VS Code やコマンドプロンプト/bash向けのスクリプト生成
* Windows 向け

ZephyrSkeleton\scripts\setup.bat をエディタで開き、下記ターゲットの設定を適宜変更
```
set BOARD_TYPE=bbc_microbit_v2
```
* Ubuntu 向け
ZephyrSkeleton\scripts\setup.sh をエディタで開き、下記ターゲットの設定を適宜変更
```
BOARD_TYPE=bbc_microbit_v2
```
以上で、初回の構築は完了です。

ディレクトリ構成は以下のようになっており、SDK 以外はすべてこの中に内包しています。
```
.
└── zephyrproject/
    ├── .venv
    ├── .west
    ├── skeleton/
    │   ├── .vscode
    │   ├── boards
    │   ├── CMakeLists.txt
    │   ├── drivers
    │   ├── include
    │   ├── main.c
    │   ├── prj.conf
    │   ├── scripts
    │   ├── utils
    │   └── west.yml
    └── zephyr-env/
        ├── modules
        └── zephyr
```

## 開発フロー
### VS Code による開発
1. VS Code で zephyrproject、もしくは skeleton ディレクトリを開く
2. Ctrl + Shift + B で、「Rebuild」「Build」「Flash」「Debug」を適宜選択
3. 「Debug」選択時は、gdbserver で待機状態に入るため、その後 F5 を押すことでアタッチ

### コマンドによる開発
1. skeleton に移動しそれぞれ以下のコマンドを実行

| 機能 | コマンド |
|-----|----|
| Rebuild | ./scripts/build /r |
| Build | ./scripts/build.bat |
| Flash | ./scripts/build.bat /f |
| Debug | ./scripts/debug.bat |

Debug 時は、port 3333 で待機しているので sdk 内にある gdb を用いてアタッチ
