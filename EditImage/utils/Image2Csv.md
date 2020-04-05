# class Image2Csv
## 目的
　このクラスは画像ファイル（jpg,jpeg,png,gif...）の全画素地をCSVファイルに変換する為に作られたクラスである。
 
## 説明
 まず、インスタンス生成時には以下のように記述する。
 
 `shared_ptr<Image2Csv> im2csv = make_shared<Image2Csv>([ImageFile], [CsvFile]);`
  
 [ImageFile]は変換される画像のパスで、[CsvFile]は変換後のCSVファイルのパスを示している。
 このクラスはインスタンス生成時に画像ファイルをCSVファイルへ変換する。
 
## メンバ
 *outputFilePath*
  string型の変数。出力先のCSVファイルのパスが格納されている。
