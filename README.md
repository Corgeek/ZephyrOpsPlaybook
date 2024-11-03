# ZephyrSkeleton

## 機能概要
Zephyr のアプリケーション開発を始める際に、汎用的に使うファイル群をスケルトンとしてまとめておく。<br>
* コマンドプロンプトとBash両方の環境を用意
* Visual Studio Code との連携
  * Ctrl + SHIFT + B で、"Rebuild and Flash", "Build", "Debug" を用意
  * Debug 選択時は、west debugserver で待機に入るので、その後 F5 によりアタッチ可能

## 使い方
### for Windows
1. scripts\setup.bat 3, 4行目の編集
  - ZEPHYR_ROOT 変数に west init したパスを設定
  - BOARD_TYPE 変数にターゲットのボード名を設定
2. scripts\setup.bat を実行
```
cd ZephyrSkeleton
scripts\setup.bat
```

### for Linux
1. scripts/setup.sh 3, 4行目の編集
  - ZEPHYR_ROOT 変数に west init したパスを設定
  - BOARD_TYPE 変数にターゲットのボード名を設定
2. scripts/setup.sh を実行
```
cd ZephyrSkeleton
scripts\setup.sh
```

## 大まかな方針
* コマンドによるビルドやデバッグ方法も確保しつつ、それを vscode からも利用する方針
  * どちらかだけを優先すればもっとキレイでシンプルなつくりはできるし、たくさん提供されているので
* よく使う基本的な機能などはskeletonレベルで実装しておき、取捨選択できるようにしておきたい

## 要検討
* よくよく考えると git を入れた時点で git-bash が使えるので、コマンドプロンプトにこだわる必要がないかも

## Todo
* 今は Getting Started Guide の通りに構築した環境のみ対応
  * /opt などのパスに zephyrproject や zephyr-sdk-x.y.z を配置した環境は微修正が必要
* ARM 以外のアーキテクチャも考慮
* 一部の board で west のオプションなどが異なるため、その差異も吸収できるように
* ソース側の機能充実
