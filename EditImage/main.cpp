#include <opencv2/opencv.hpp>
#include <iostream>
#include "utils/Image2Csv.h"
#include "utils/EditCsv.h"
#include "utils/Csv2Image.h"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//�摜�p�X�����͂���Ȃ������狭���I��
	if (argc == 1)	return 0;
	string imagePath = argv[1];//���͉摜�t�@�C����
	string outputCsv = argv[1];//�o��CSV�t�@�C����
	outputCsv = outputCsv.replace(outputCsv.end() - 4, outputCsv.end(), ".csv");
	string outputImagePath = argv[1];//�o�͉摜�t�@�C����
	outputImagePath = outputImagePath.insert(outputImagePath.length() - 4, "_result");

	//Image2Csv�N���X��p���ĉ摜�����f�n��RGB�`����CSV�t�@�C���֕ϊ�����B
	shared_ptr<Image2Csv> image = make_shared<Image2Csv>(imagePath, outputCsv);
	
	//EditCsv�N���X��p����RGB�`���̉�f�n����Grayscale�`���֕ϊ�����B
	shared_ptr<EditCsv> editedCsv = make_shared<EditCsv>(outputCsv);

	//��f�n�̕��ϒl�����A_csvGray���X�V����B
	bool isRgb = false;
	editedCsv->ave();
	editedCsv->writeCsv(outputCsv, isRgb);

	//臒l�ŕ����āAGray�����蓖�Ă�B_csvGray���X�V����B
	isRgb = true;
	editedCsv->threshold("threshold_table.csv", isRgb);
 	editedCsv->writeCsv(outputCsv, isRgb);
	
	//Csv2Image�N���X��p����CSV�t�@�C�����摜�ɕϊ�����B
	shared_ptr<Csv2Image> Csv = make_shared<Csv2Image>(editedCsv->outputCsvFile, outputImagePath);
	Csv->makeImage(isRgb);
	Csv->deleteCsv(true);
	
}