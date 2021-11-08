#pragma once
#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  
#include <CString>
#include <map>

using namespace std;
using std::string;

static class ReadCSV
{
public:
	static void ReadFile(string fileName, map<string, vector<string>>& finalStrings);
	static vector<double> ConvertToDouble(vector<string>& str);//convert string to double 
private:
	static void ReadALine(string oneLine,vector<string> &oneLineString);
	static void ReArrangeLines(vector<string>& keywordString, map<string, vector<string>> &finalStrings);

};

