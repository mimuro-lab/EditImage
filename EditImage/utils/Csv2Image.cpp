#include "Csv2Image.h"

std::vector<std::string> Csv2Image::split(std::string str, char del) {
	int first = 0;
	int last = str.find_first_of(del);

	std::vector<std::string> result;

	while (first < str.size()) {
		std::string subStr(str, first, last - first);
		result.push_back(subStr);
		first = last + 1;
		last = str.find_first_of(del, first);
		if (last == std::string::npos) {
			last = str.size();
		}
	}
	return result;
}

Csv2Image::Csv2Image(string _inputCsvFile, string _outputImage)
{
	outputImagePath = _outputImage;
	inputCsvPath = _inputCsvFile;
	std::fstream inputCsv(_inputCsvFile);
	if (!inputCsv) {
		printf("cannnot open file : ");
		canReadCsv = false;
	}
	else {
		canReadCsv = true;
	}
	
	if (canReadCsv) {
		////CSV�摜�̕��𒲂ׂ�
		//1�s���Ƃ̃f�[�^�i�[�p�ϐ�data(string)
		std::string data;
		//inputCsv�I�u�W�F�N�g����P�s�ڂ�data�Ɋi�[
		getline(inputCsv, data);
		//data�i�P�s�j���C�ŕ������A_csv�֒ǉ�
		_csv.push_back(split(data, ','));
		//height���P��J�E���g
		height++;
		//inputCsv�̂P�s�ڂ�","���J�E���g
		width = std::count(data.cbegin(), data.cend(), ',');
		//inputCsv�̑S�s�����J�E���g
		while (!inputCsv.eof())
		{
			inputCsv >> data;
			_csv.push_back(split(data, ','));
			height++;
		}
		inputCsv.close();
	}
}

void Csv2Image::makeImage(bool isRgb)
{
	//�摜�𐶐�����B
	
	printf("\making a image...");
	cv::Mat image;
	if (!isRgb)
		image = cv::Mat::zeros(height - 1, width, CV_8UC1);
	else
		image = cv::Mat::zeros(height - 1, width, CV_8UC3);

	//�f�[�^�̈ړ�
	for (int j = 0; j < height - 1; j++) {
		for (int i = 0; i < width; i++) {
			//_csv��cv::Mat�`���̔z��֊i�[����B
			if (!isRgb)
				image.at<uchar>(j, i) = atoi(_csv[j][i].c_str());
			else {
				image.at<cv::Vec3b>(j, i)[0] = atoi(split(_csv[j][i].c_str(), ':')[2].c_str()); //Blue
				image.at<cv::Vec3b>(j, i)[1] = atoi(split(_csv[j][i].c_str(), ':')[1].c_str()); //Green
				image.at<cv::Vec3b>(j, i)[2] = atoi(split(_csv[j][i].c_str(), ':')[0].c_str()); //Red
			}
		}
		//printf(" : %d \n", j);
	}
	//�摜�̏o��
	cv::imwrite(outputImagePath, image);
	printf("finished! -> %s\n", outputImagePath.c_str());
}

void Csv2Image::deleteCsv(bool isDelete)
{
	if (!isDelete)
		return ;
	remove(inputCsvPath.c_str());
	printf("\tremoved Csv File \"%s\"", inputCsvPath.c_str());
}