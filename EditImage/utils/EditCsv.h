#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

//CSV�t�@�C���ɏ����ꂽ��f�n��RGB�`������GrayScale�֕ϊ�����B
//臒l�̐U�蕪�����͒��Ԓl�ŗǂ��B�i40���݂Ȃ̂ŁA�v���X�}�C�i�X20�j
class EditCsv
{
	//CSV�t�@�C�����������ǂݍ��߂����H
	bool canReadCsv = false;
	std::vector<std::string> split(std::string str, char del);
	//_csv[][]�̗v�f��int�^�Ŏ󂯎��AthresholdTable�ɑΉ�������ithreshold�^�j��Ԃ�
	struct tableCell {
		int index = -1;//�\�̃C���f�b�N�X
		int range_button = -1;//�O���[�X�P�[����臒l�̉���
		int range_upper = -1;//�O���[�X�P�[����臒l�̏��
		int rgb[3] = { 0 };//RGB�̒l[r,g,b}
		string label = "";//���x���̕�����
	};
	//臒l�ŕ�����ꂽCSV�t�@�C���̗v�f��tableCell�`���ŊǗ�
	vector<tableCell> Table;
	//�ҏW������ۑ�����X�^�b�N�ϐ�
	stack<string> histEdit;
public:
	EditCsv(string inputCsvfile);
	~EditCsv() = default;
	string inputCsvFile;
	string outputCsvFile;
	//_csvGray�̍X�V�iRGB�̕��ϒl�j
	void ave();
	//_csvGray�̍X�V�ithresholdTable��臒l�ŕ�����jisRgb�͐F�t�������邩�ǂ���
	void threshold(string thresholdTable, bool isRgb);
	//Grayscale��CSV�t�@�C�����쐬���� isRgb��true�̏ꍇ_csvRgb�Afalse�̏ꍇ_csvGray���������ށB
	void writeCsv(string outputCsvfile, bool isRgb);
	//graycale�̗v�f��int�`���ŊǗ��i2����vector�j
	vector<vector<int>> _csvGray;
	//RGB�̗v�f��string�`���ŊǗ��i2����vector�j
	vector<vector<string>> _csvRgb;
};