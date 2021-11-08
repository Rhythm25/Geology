#include "ReadCSV.h"

vector<vector<string>> readAllFile;

void ReadCSV::ReadFile(string fileName, map<string, vector<string>>& finalStrings) {
	readAllFile.clear();

	ifstream inFile(fileName);
	if (inFile.fail()) { 
		cout << "File not found" << endl; 
		return; 
	}

	string line;
	getline(inFile, line);

	vector<string> keyWord;
	ReadALine(line, keyWord);//read key words i.e. the first row

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

	ReArrangeLines(keyWord, finalStrings);
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