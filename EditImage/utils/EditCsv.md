# class EditCsv
# 目的
　このクラスは[Image2Csvクラス](https://github.com/mimuro-lab/EditImage/blob/master/EditImage/utils/Image2Csv.md)から生成された画像の画素地を示すCSVファイルを編集する為に作られたものである。
 また、このクラスではあらかじめ[threshold_table.csv](https://github.com/mimuro-lab/EditImage/blob/master/EditImage/threshold_table.csv)の様なファイルを用意する必要がある。
 
 # 説明
 まず、インスタンス生成時は以下のように記述する。
 
 `shared_ptr<EditCsv> editCsv = make_shared<EditCsv>([inputCsv]);`
 
 [inputCsv]は編集されるCSVファイルのパスを示している。このクラスでは、インスタンスを生成したのみでは編集をしない。以下のメンバ変数・メンバ変数を参考にしてほしい。
 
 ## メンバ変数
 #### publicな変数
 ・*inputCsvFile*
 
 &emsp;編集されるCSVファイルのパス。string型の変数である。
 
 ・*outputCsvFile*
 
 &emsp;出力されるCSVファイルのパス。string型の変数であり、メンバ関数writeCsv()を実行した時に更新される。一番最近のパスしか保持しない事に注意。
 
 ・*_csvGray*
 
 &emsp;メンバ関数ave()やthreshold()で編集されたグレースケール形式の画素地を格納するための変数。Vectorで宣言された２次元変数であり、各要素はint形式である。
 
・*_csvRgb*

 &emsp;メンバ関数threshold()で編集されたRGB形式の画素地を格納するための変数。Vectorで宣言された２次元変数であり、各要素はstring形式である。
 各要素は、編集後のCSVのような形で以下のようになっている。
 
 _csvRgb[i][j] ---> "210:50:8"
 
 これは、Redが210・Greenが50・Blueが8の色を示している。
 
 ### privateな変数
 
 ・*canReadCsv*
 
  &emsp;bool型の変数。fstreamによって編集されるCSVファイルが正しく読み込めたかを示している。trueなら正常に読み込めた・falseなら読み込めなかった。
 
 ・*Table*
 
  &emsp;tableCell型（クラス内で宣言）の変数。Vector型で宣言されており、[threshold_table.csv](https://github.com/mimuro-lab/EditImage/blob/master/EditImage/threshold_table.csv)の各行成分を格納している。
 
 
 ・*histEdit*
 
   &emsp;string型の変数。stackが型で宣言されており、ave()やthreshold()などを実行した履歴をほ存する。
 
 ### publicな関数
 ・*void ave(void)*
 
  &emsp; _csvRgbに格納されている画素地の平均値を取って_csvGrayに格納する関数。返り値はなし。
  
  ・*void threshold([thesholdTable], [isRGB])*
   
   &emsp;_csvRgbに格納されている画素地をthresholdingTableに指定された[threshold_table.csv](https://github.com/mimuro-lab/EditImage/blob/master/EditImage/threshold_table.csv)を参考に閾値で分ける。
   isRgbをfalseにした場合、indexの40倍の値が_csvGrayに格納される。isRgbをtrueにした場合、表のr/g/bの値が格納される。
   
 ### privateな関数
 
 ・*vector<string>split([string], [splitChar])*
 
 &emsp;文字列[string]を文字[splitChar]で区切る。区切った各要素をvector形式にして返す。
