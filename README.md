# ZephyrOpsPlaybook

## 1. 機能概要
公式の手順を簡略・軽量化して、手軽に開発を始められる環境を提供することを目的としています。
* コマンドプロンプトと bash 両方で使えるようにしておき、VSCode によるデバッグ環境を提供
* ボード間の差異を減らし、移植性を維持した実装例の提案
* サンプルドライバ群も用意し、すぐにアプリケーション開発に注力できる環境を提供
* 開発の際はターゲットが決まっていることが多く、ターゲットを絞り込んだ環境構築の例示
* バージョンやリビジョンを固定して足並みをそろえた開発が必要で、その固定させる方法を提供

各ブランチの説明は以下の通り。

| ブランチ名 | 概要 | 対象 | Zephyr のリビジョン |
|---|---|---|---|
| [master](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/master) | サンプルをすべて盛り込んだ環境 | とりあえず動かしてみたい方向け | v4.1.0 |
| [dev/newest](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/dev/newest) | master をベースに Zephyr 最新リビジョン | Zephyr の最新機能を試したい方向け | 最新 |
| [dev/basic](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/dev/basic) | サンプルを取り除いたシンプルな基本構成 | 基本構成を使って開発を進めたい方向け | v4.1.0 |
| [dev/minimal](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/dev/minimal) | Zephyr 最新リビジョンで、main 関数のみの最小構成の環境 | vscode 連携など最小限の機能を流用したい方向け | 最新 |
| [dev/v3.7-branch](https://github.com/Corgeek/ZephyrOpsPlaybook/tree/dev/v3.7-branch) | master をベースに Zephyr の LTS 版である v3.7.0 環境 | Zephyr の LTS を採用したい場合 | v3.7.0 |

また、作業ミスを減らすため、README.md を環境ごとに分割していますので、環境に合わせて参照してください。

| 環境 | 概要 |
|------|------|
| [Ubuntu 向け](docs/README_lnx.md) | Ubuntu ネイティブやWSLを含む仮想環境 |
| [Windows 向け](docs/README_win.md) | コマンドプロンプトを使った Windows ネイティブ環境 |
| [Addon 向け](docs/README_addon.md) | 公式の Zephyr 環境を既に構築済みで、それを流用したい場合 |

> [!TIP]
WSL は USB 機器の制御を理由に公式で推奨されていませんが、デバイスの管理等の知識がある方は一通り利用できます。<br>
また、そもそもターゲットをUSB経由で制御できる仕組みがない場合などは、Windows ネイティブより断然軽量な WSL を選択肢として考慮に入れて良いかもしれません。

本リポジトリの簡単な解説と、広く Zephyr についても触れていますので、よろしければ以下の記事も参考にしていただければ幸いです。

1. [【Qiita記事】 Zephyr RTOS 〜 Lチカのその先へ 〜](https://qiita.com/Corgeek/items/ca4c515ccf556551562f)
2. [【Qiita記事】 Zephyr RTOS 〜 ターゲット毎の設定や選定基準 〜](https://qiita.com/Corgeek/items/f91831de947f8dde1d39)
3. [【Qiita記事】 Zephyr RTOS 〜 GPIO を叩く！ 〜](https://qiita.com/Corgeek/items/122a00e430ad0d9c297a)
4. [【Qiita記事】 Zephyr RTOS 〜 I2C 通信の方法と VL53L4CD の移植 〜](https://qiita.com/Corgeek/items/ac211cd48a54971d9b17)
5. [【Qiita記事】 Zephyr RTOS 〜 チーム開発を見据えた管理方法 〜](https://qiita.com/Corgeek/items/b879637a6c25027af318)
6. [【Qiita記事】 Zephyr RTOS 〜 pico2 の開発環境を整えてみる 〜](https://qiita.com/Corgeek/items/3bfc0bee8e2eeeb0b646)
7. [【Qiita記事】 Zephyr RTOS 〜 起動シーケンスと任意処理の追加 〜](https://qiita.com/Corgeek/items/e2052879113102eb2ad7)
8. [【Qiita記事】 Zephyr RTOS 〜 LVGL 描画ライブラリによるGUI開発 〜](https://qiita.com/Corgeek/items/7150ac01a8a87b59ac1d)
9. [【Qiita記事】 Zephyr RTOS 〜 Devicetree 序章 〜](https://qiita.com/Corgeek/items/5ce62af68dd7b5300608)
10. [【Qiita記事】 Zephyr RTOS 〜 Devicetree 深淵 其の壱 〜](https://qiita.com/Corgeek/items/79135546b129b1aaf42b)
11. [【Qiita記事】 Zephyr RTOS 〜 Devicetree 深淵 其の弐 〜](https://qiita.com/Corgeek/items/570b02e8cc5491902eb9)
