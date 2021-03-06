#include "Image2Csv.h"

Image2Csv::Image2Csv(string _inputImage, string _outputFilePath)
{
	cv::Mat _imageSrc = cv::imread(_inputImage);
	
	outputFilePath = _outputFilePath;
	FILE* stream;
	fopen_s(&stream, _outputFilePath.c_str(), "w");
	printf("converting image to csv file... ");
	for (int y = 0; y < _imageSrc.rows; ++y) {
		for (int x = 0; x < _imageSrc.cols; ++x) {
			fprintf(stream, "");
			/*
			for (int c = 0; c < _imageSrc.channels(); ++c) {
				fprintf(stream, "%hhu:", _imageSrc.data[y * _imageSrc.step + x * _imageSrc.elemSize() + c]);
			}
			*/
			//RGBの順番で書き込む
			fprintf(stream, "%hhu:", _imageSrc.data[y * _imageSrc.step + x * _imageSrc.elemSize() + 2]);//red
			fprintf(stream, "%hhu:", _imageSrc.data[y * _imageSrc.step + x * _imageSrc.elemSize() + 1]);//greeen
			fprintf(stream, "%hhu:", _imageSrc.data[y * _imageSrc.step + x * _imageSrc.elemSize() + 0]);//blue
			fprintf(stream, ",");
		}
		if (y != _imageSrc.rows - 1) {
			fprintf(stream, "\n");
		}
	}
	fclose(stream);
	printf("finished! -> %s\n", _outputFilePath.c_str());
}
