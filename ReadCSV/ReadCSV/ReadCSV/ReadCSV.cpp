#include "ReadCSV.h"

vector<vector<string>> readAllFile;

vector<vector<string>> ReadCSV::ReadFile(string fileName) {
	readAllFile.clear();

	ifstream inFile(fileName);
	if (inFile.fail()) { 
		cout << "File not found" << endl; 
		return readAllFile;
	}

	string line;
	//getline(inFile, line);

	//vector<string> keyWord;
	//ReadALine(line, keyWord);//read key words i.e. the first row

	while (getline(inFile, line))//read all lines in readAllFile except the first line
	{
		istringstream lineStream(line);
		vector<string> lineWords;
		string word;
		while (getline(lineStream, word, ','))
		{
			lineWords.push_back(word);
		}
		readAllFile.push_back(lineWords);
	}
	return readAllFile;
	//ReArrangeLines(keyWord, finalStrings);
}

void ReadCSV::ReadALine(string oneLine, vector<string>& oneLineString) {
	istringstream oneLineStream(oneLine);
	string oneWord;
	while (getline(oneLineStream, oneWord, ','))
	{
		oneLineString.push_back(oneWord);
	}
}

void ReadCSV::ReArrangeLines(vector<string>& keywordString, map<string, vector<string>>& finalStrings) {
	vector<string> oneMapStrings;
	int rowNum = readAllFile.size();

	for (int i = 0; i < keywordString.size(); i++) {
		oneMapStrings.clear();
		for (int j = 0; j < rowNum; j++) {
			oneMapStrings.push_back(readAllFile[j][i]);
		}
		finalStrings[keywordString[i]] = oneMapStrings;
	}
}

vector<double> ReadCSV::ConvertToDouble(vector<string>& str) {
	vector<double> strToDouble;
	for (int i = 0; i < str.size(); i++) {
		strToDouble.push_back(atof(str[i].c_str()));
	}
	return strToDouble;
}

void ReadCSV::FindXYZForSeam(vector<vector<string>>& allStringGeo, vector<vector<string>>& allStringPos, vector<vector<string>>& allStringAngle, int seam,
	vector<double>& x, vector<double>& y, vector<double>& z) {
	int seamStringPos = FindStringPos(allStringGeo,"seam");
	int fromStringPos = FindStringPos(allStringGeo, "from");
	int dhidStringPos = FindStringPos(allStringGeo, "dhid");

	vector<string> dhidHasSeam;//stores dhids which has seam
	vector<double> fromDistanceSeam;//stores from distances instead of height
	for (int i = 0; i < allStringGeo.size(); i++) {
		//cout << atoi(allStringGeo[i][seamStringPos].c_str()) << endl;
		if ((atoi(allStringGeo[i][seamStringPos].c_str()) == seam)){
			if (dhidHasSeam.size() != 0 && allStringGeo[i][dhidStringPos].compare(dhidHasSeam[dhidHasSeam.size() - 1]) != 0) {
			fromDistanceSeam.push_back(atof(allStringGeo[i][fromStringPos].c_str()));
			dhidHasSeam.push_back(allStringGeo[i][dhidStringPos]);
			}
			else if (dhidHasSeam.size() == 0) {
				fromDistanceSeam.push_back(atof(allStringGeo[i][fromStringPos].c_str()));
				dhidHasSeam.push_back(allStringGeo[i][dhidStringPos]);
			}
		}
	}

	//for (int i = 0; i < dhidHasSeam.size(); i++) cout << dhidHasSeam[i] << endl;
}

int ReadCSV::FindStringPos(vector<vector<string>>& allStringGeo, string keyWord) {
	vector<string> keyWordString = allStringGeo[0];
	for (int i = 0; i < keyWordString.size(); i++) {
		if (keyWordString[i].compare(keyWord) == 0) return i;
	}
	cout << "Error: Cannot find "+keyWord+" keyword!" << endl;
	return -1;
}

vector<double> ReadCSV::LengthConvertToHeight(vector<double>& distance, vector<string>& dhid, vector<vector<string>>& allStringAngle) {
	
}

map<string, vector<string>> ConvertToMap(vector<vector<string>>& allStrings) {
	for (int i = 0; i < allStrings.size(); i++) {
		vector<string> oneLine;

	}
}