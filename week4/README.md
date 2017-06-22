# Week4: Wikipediaグラフの最大クリークを求めた。

* クリークとは，その要素の点が互いにパス1つでたどれるような点の集合。
* 最大クリークとは，そのような集合のうち要素数が最大のもの。
* 結果，最大クリークの要素数は*716*と求まった。構成要素の一部を末尾に示す。(残りはresult.txtを参照)

## 実装について

* 予め双方向でないパスおよび双方向エッジを持たないノードをデータから除外した(<https://github.com/keink/stephw4/blob/master/mutuallinks.cpp> を少し改変して使わせていただきました)ところ，全体のノードの半分ほど(763995)が残った。今回はこのノードたちのみを使っているが，扱いやすくするため，ノードに振られている番号を前から詰めて新しく振り直した。
* R. CarraghanとP.M. Pardalosが1990年に発表したアルゴリズムを用いた。
* 参考にした資料など:

R. Carraghan, P.M. Pardalos, An exact algorithm for the maximum clique problem (1990)

Patric R. J. Ostergard, A fast algorithm for the maximum clique problem (2002)
(この論文で紹介されている1990年のアルゴリズムの擬似コードがわかりやすかったです)

<http://www.tani.cs.chs.nihon-u.ac.jp/g-2006/s5402031hide/maxclq_last.pdf>


## ファイルの説明

### maxClique.cpp
最大クリークを求めた。

### confirmAdjacency.cpp
2つのノードの題名を入力したら，それが双方向エッジ1本でつながっているかどうかを確認してくれる。maxClique.cppの結果が合っているかどうか確認したかったので作った。

### result.txt
最大クリーク問題を解いた時の結果。クリークの最大要素数を更新していく形のアルゴリズムだったので，最後以外のMax Clique Componentsは，Wikipediaグラフ全体での最大クリークの要素ではない。
途中の"暫定最大クリーク"を見てみると，文字関連のページから，言語関連，地球科学(?)関連，社会科学関連，相撲関連，日本の文学史関連と続き，最後に宝塚関連となるのが興味深い。

### pageRank
未完成。授業スライドであったpageRankを実装してみようとした。(あまり関係ない)

## maxClique.cppの出力の一部
    Max Clique Components:
    純名里沙
    阪急電鉄
    扇千景
    宝塚歌劇団
    小林一三
    宝塚音楽学校
    東宝
    一路真輝
    黒木瞳
    浜木綿子
    涼風真世
    新珠三千代
    越路吹雪
    紫吹淳
    大地真央
    杜けあき
    (...中略...)
    星風まどか
    音くり寿
    輝生かなで
    星那由貴
    小春乃さよ
    穂稀せり
    潤奈すばる
    美里夢乃
    宝塚歌劇団101期生
    夢乃花舞
    周旺真広

    Max Clique Size: 716
