#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Csv2Image
{

	bool canReadCsv = false;
	std::vector<std::string> split(std::string str, char del);
public:
	Csv2Image(string _inputCsvFile, string _outputImage);
	string outputImagePath = "";//出力用の画像パス
	string inputCsvPath = "";//入力されたCSVファイルパス
	int width = 0;
	int height = 0;
	vector<vector<string>> _csv;
	//画像を生成する
	void makeImage(bool isRgb);
	void deleteCsv(bool isDelete = false);

};

