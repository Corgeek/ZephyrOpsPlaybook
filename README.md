# ZephyrOpsPlaybook (minimal)

## 1. 機能概要
公式の手順を簡略・軽量化して、手軽に開発を始められる環境を提供することを目的としています。
* 開発の際はターゲットが決まっていることが多く、大部分が未使用になる公式環境を削減
* バージョンやリビジョンを固定して足並みをそろえた開発が必要で、その固定させる方法を提供
* コマンドプロンプトと bash 両方で使えるようにしておき、VSCode によるデバッグ環境を提供

作業ミスを減らすため、README.md を目的ごとに分割しました。

| 目的 | 概要 |
|------|------|
| [Ubuntu 向け](docs/README_lnx.md) | Ubuntu ネイティブやWSLを含む仮想環境 |
| [Windows 向け](docs/README_win.md) | コマンドプロンプトを使った Windows ネイティブ環境 |
| [Addon 向け](docs/README_addon.md) | 公式の Zephyr 環境を既に構築済みで、それを流用したい場合 |

> [!TIP]
WSL は USB 機器の制御を理由に公式で推奨されていませんが、デバイスの管理等の知識がある方は一通り利用できます。<br>
また、そもそもターゲットをUSB経由で制御できる仕組みがない場合などは、Windows ネイティブより断然軽量な WSL を選択肢として考慮に入れて良いかもしれません。

本リポジトリの簡単な解説と、広く Zephyr についても触れていますので、よろしければ以下の記事も参考にしていただければ幸いです。

1. [【Qiita記事】 Zephyr RTOS 〜 Lチカのその先へ 〜](https://qiita.com/Corgeek/items/ca4c515ccf556551562f)
2. [【Qiita記事】 Zephyr RTOS 〜 GPIO を叩く！ 〜](https://qiita.com/Corgeek/items/122a00e430ad0d9c297a)
3. [【Qiita記事】 Zephyr RTOS 〜 I2CでIC制御 〜](https://qiita.com/Corgeek/items/ac211cd48a54971d9b17)
4. [【Qiita記事】Zephyr RTOS 〜 チーム開発を見据えた管理方法 〜](https://qiita.com/Corgeek/items/b879637a6c25027af318)
5. [【Qiita記事】Zephyr RTOS 〜 pico2 の開発環境を整えてみる 〜](https://qiita.com/Corgeek/items/3bfc0bee8e2eeeb0b646)
