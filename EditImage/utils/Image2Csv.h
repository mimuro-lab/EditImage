#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

//cv::Mat�`������摜�̉�f�n���e�L�X�g�t�@�C���֕ϊ�����
class Image2Csv
{
public:
	Image2Csv(string _inputImage, string _outputFilePath);
	~Image2Csv() = default;
	//�o�͂̃e�L�X�g�t�@�C����
	string outputFilePath;
};

