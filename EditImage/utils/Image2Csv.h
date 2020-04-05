#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

//cv::Mat形式から画像の画素地をテキストファイルへ変換する
class Image2Csv
{
public:
	Image2Csv(string _inputImage, string _outputFilePath);
	~Image2Csv() = default;
	//出力のテキストファイル名
	string outputFilePath;
};

