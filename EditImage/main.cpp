#include <opencv2/opencv.hpp>
#include <iostream>
#include "utils/Image2Csv.h"
#include "utils/EditCsv.h"
#include "utils/Csv2Image.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//画像パスが入力されなかったら強制終了
	if (argc == 1)	return 0;
	string imagePath = argv[1];//入力画像ファイル名
	string outputCsv = argv[1];//出力CSVファイル名
	outputCsv = outputCsv.replace(outputCsv.end() - 4, outputCsv.end(), ".csv");
	string outputImagePath = argv[1];//出力画像ファイル名
	outputImagePath = outputImagePath.insert(outputImagePath.length() - 4, "_result");

	//Image2Csvクラスを用いて画像から画素地をRGB形式のCSVファイルへ変換する。
	shared_ptr<Image2Csv> image = make_shared<Image2Csv>(imagePath, outputCsv);
	
	//EditCsvクラスを用いてRGB形式の画素地からGrayscale形式へ変換する。
	shared_ptr<EditCsv> editedCsv = make_shared<EditCsv>(outputCsv);

	//画素地の平均値を取り、_csvGrayを更新する。
	bool isRgb = false;
	editedCsv->ave();
	editedCsv->writeCsv(outputCsv, isRgb);

	//閾値で分けて、Grayを割り当てる。_csvGrayを更新する。
	isRgb = true;
	editedCsv->threshold("threshold_table.csv", isRgb);
 	editedCsv->writeCsv(outputCsv, isRgb);
	
	//Csv2Imageクラスを用いてCSVファイルを画像に変換する。
	shared_ptr<Csv2Image> Csv = make_shared<Csv2Image>(editedCsv->outputCsvFile, outputImagePath);
	Csv->makeImage(isRgb);
	Csv->deleteCsv(true);
	
}