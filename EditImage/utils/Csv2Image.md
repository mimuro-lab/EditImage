# class Csv2Image
##　目的
　このクラスは[Image2Csvクラス](https://github.com/mimuro-lab/EditImage/blob/master/EditImage/utils/Image2Csv.md)や[EditCsvクラス](https://github.com/mimuro-lab/EditImage/blob/master/EditImage/utils/EditCsv.md)で作成されたCSV形式のファイルを画像にする為に作られたクラスである。
 
##　説明
まず、インスタンス生成時には以下のように記述する。

`shared_ptr<Csv2Image> csv2im = make_shared<Csv2Image>([csvFile], [imageFile]);`

[csvFile]は画像にしたいCSVファイルパスを示しており、[imageFile]は作成する画像のファイルパスを示している。また、インスタンスを生成しただけでは画像を生成しない事に注意してほしい。

## メンバ
### publicな関数
・*void makeImage([isRGB])*

&emsp;メンバ変数_csvから画像生成する関数。isRGBは_csvがRGB形式かGrayscale形式かを示す。trueならRGB形式・falseならGrayscale形式。

・*void deleteCsv([isDelete])*

&emsp;メンバ変数inputCsvPathが示すCSVファイルを消去する関数。引数[isDelete]にもtrueを代入しないと消去しないのに注意。

### publicな変数

・*outputImagePath*

&emsp;出力される画像ファイル名。インスタンス生成時に設定される。

・*inputCsvPath*

&emsp;編集されるCSVファイル名。インスタンス生成時に設定される。

・*width*

&emsp;編集されるCSVファイルの一行目の要素数。（行と列の要素数が同じ事が前提とされている）

・*height*

&emsp;編集されるCSVファイルの全行数。（行と列の要素数が同じ事が前提とされている）

### privateな関数

・*vector<string> split([string], [splitChar])*

&emsp;文字列[string]を文字[splitChar]で区切る。区切った各要素をvector形式にして返す。

### privateな変数

・*canReadCsv*

&emsp;bool型の変数。fstreamによって編集されるCSVファイルが正しく読み込めたかを示している。trueなら正常に読み込めた・falseなら読み込めなかった。
