#include "EditCsv.h"

std::vector<std::string> EditCsv::split(std::string str, char del) {
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

EditCsv::EditCsv(string _inputCsvFile)
{
	printf("\tedting a CSV(image)...\n");

	_csvRgb.clear();
	_csvGray.clear();
	inputCsvFile = _inputCsvFile;
	std::fstream inputCsv(_inputCsvFile);
	if (!inputCsv) {
		printf("cannnot open file : ");
		canReadCsv = false;
		printf(" at EditCsv");
	}
	else {
		canReadCsv = true;
	}
	
	if (canReadCsv) {
		////CSV画像の幅を調べる
		//1行ごとのデータ格納用変数data(string)
		std::string data;
		//inputCsvオブジェクトから１行目をdataに格納
		getline(inputCsv, data);
		//data（１行）を，で分割し、_csvRgbへ追加
		_csvRgb.push_back(split(data, ','));
		//inputCsvの全行数をカウント
		while (!inputCsv.eof())
		{
			inputCsv >> data;
			_csvRgb.push_back(split(data, ','));
		}
	}

	for (int i = 0; i < _csvRgb.size(); i++) {
		_csvGray.push_back({0});
		for (int j = 0; j < _csvRgb[0].size() - 1; j++) {
			_csvGray[i].push_back(0);
		}
	}
	
	inputCsv.close();
}

void EditCsv::ave()
{	
	for (int j = 0; j < _csvRgb.size(); j++) {
		for (int i = 0; i < _csvRgb[0].size(); i++) {
			unsigned short int addedRGB = atoi(split(_csvRgb[j][i], ':')[0].c_str()) + atoi(split(_csvRgb[j][i], ':')[1].c_str()) + atoi(split(_csvRgb[j][i], ':')[2].c_str());
			addedRGB /= 3;
			_csvGray[j][i] = addedRGB;
		}
	}
	histEdit.push("convert \"RGB to Grayscale\" by taking average");
	printf("\tconvert \"RGB to Grayscale\" by taking average\n");
}

void EditCsv::threshold(string thresholdTable, bool isRgb)
{
	//thresholdTableを読み込んでTableに格納する。
	ifstream readTable(thresholdTable);
	string data;
	getline(readTable, data);//1行目は表目なので使わない
	while (getline(readTable, data)) {
		tableCell cell;
		cell.index = atoi(split(data, ',')[0].c_str());
		cell.label = split(data, ',')[1];
		cell.range_button = atoi(split(split(data, ',')[2], '/')[0].erase(0, 1).c_str());
		cell.range_upper = atoi(split(split(data, ',')[2], '/')[1].c_str());
		cell.rgb[0] = atoi(split(split(data, ',')[3], '/')[0].c_str());
		cell.rgb[1] = atoi(split(split(data, ',')[3], '/')[1].c_str());
		cell.rgb[2] = atoi(split(split(data, ',')[3], '/')[2].c_str());
		Table.push_back(cell);
	}

	//_csvを閾値で分ける
	for (int j = 0; j < _csvRgb.size(); j++) {
		for (int i = 0; i < _csvRgb[0].size(); i++) {
			//_csvに相当するTableを見つける
			for (vector<tableCell>::const_iterator it = Table.begin(), e = Table.end(); it != e; ++it){
				if (it->range_button <= _csvGray[i][j] && _csvGray[i][j] <= it->range_upper) {
					if (!isRgb) {
						_csvGray[i][j] = it->index * 40;
					}
					else if (isRgb) {
						char _rgb[32];
						sprintf_s(_rgb, 32, "%d:%d:%d", it->rgb[0], it->rgb[1], it->rgb[2]);
						_csvRgb[i][j].clear();
						_csvRgb[i][j] = _rgb;
					}
					break;
				}
			}
		}
	}
	if (!isRgb) {
		histEdit.push("divide \"Grayscale to Grayscale\" by thresholding");
		printf("\tdivide \"Grayscale to Grayscale\" by thresholding\n");
	}
	else {
		histEdit.push("divide \"Grayscale to RGB\" by thresholding");
		printf("\tdivide \"Grayscale to RGB\" by thresholding\n");
	}
}

void EditCsv::writeCsv(string _outputCsv, bool isRgb)
{
	outputCsvFile = _outputCsv;
	
	ofstream writeFile(_outputCsv);

	for (int j = 0; j < _csvGray.size(); j++) {
		for (int i = 0; i < _csvGray[0].size(); i++) {
			if (!isRgb) {
				writeFile << _csvGray[j][i] << ',';
			}
			else if (isRgb) {
				writeFile << _csvRgb[j][i] << ',';
			}
		}
		writeFile << endl;
	}
	writeFile.close();

	printf("\tsaved! -> %s\n", _outputCsv.c_str());
}
