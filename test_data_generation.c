#include "decs.h"


void TestDataGeneration(){
    //必要な要素=(部品番号, 部品の重さ, 部品の補充頻度, 部品の配置, 製品の構成部品, 製品の製造頻度)

    //list形式
    //map=(フロアの縦横の大きさ)
    //map→部品list(どのくらいの密度で作るか？)
    //どのくらいの密度(キャパ)は入力

    //製品の数(種類数)は入力
    //部品の補充頻度1~30/月
    //部品の重量10~2000g，ランダム，一様分布
    //伝票1枚あたりの部品 = total itemの5~50%
    //使われやすさを正規分布に
    //items orderは重さ順にソート
    //一度選んだ部品をどうやって再び選ぶか？
    //スパースさなど(伝票と伝票の重なりなど)を変数で変えられるようにする
    //
}