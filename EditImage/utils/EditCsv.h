#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

//CSVファイルに書かれた画素地をRGB形式からGrayScaleへ変換する。
//閾値の振り分け方は中間値で良い。（40刻みなので、プラスマイナス20）
class EditCsv
{
	//CSVファイルが正しく読み込めたか？
	bool canReadCsv = false;
	std::vector<std::string> split(std::string str, char del);
	//_csv[][]の要素をint型で受け取り、thresholdTableに対応する情報（threshold型）を返す
	struct tableCell {
		int index = -1;//表のインデックス
		int range_button = -1;//グレースケールの閾値の下限
		int range_upper = -1;//グレースケールの閾値の上限
		int rgb[3] = { 0 };//RGBの値[r,g,b}
		string label = "";//ラベルの文字列
	};
	//閾値で分けられたCSVファイルの要素をtableCell形式で管理
	vector<tableCell> Table;
	//編集履歴を保存するスタック変数
	stack<string> histEdit;
public:
	EditCsv(string inputCsvfile);
	~EditCsv() = default;
	string inputCsvFile;
	string outputCsvFile;
	//_csvGrayの更新（RGBの平均値）
	void ave();
	//_csvGrayの更新（thresholdTableの閾値で分ける）isRgbは色付けをするかどうか
	void threshold(string thresholdTable, bool isRgb);
	//GrayscaleでCSVファイルを作成する isRgbがtrueの場合_csvRgb、falseの場合_csvGrayを書き込む。
	void writeCsv(string outputCsvfile, bool isRgb);
	//graycaleの要素をint形式で管理（2次元vector）
	vector<vector<int>> _csvGray;
	//RGBの要素をstring形式で管理（2次元vector）
	vector<vector<string>> _csvRgb;
};