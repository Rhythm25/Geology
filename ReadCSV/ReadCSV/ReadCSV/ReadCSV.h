#pragma once
#include <iostream>  
#include <string>  
#include <vector>  
#include <fstream>  
#include <sstream>  
#include <CString>
#include <map>
#include "vec3.h"
#define PI 3.1415926

using namespace std;
using std::string;


static class ReadCSV
{
public:
	
	static vector<vector<string>> ReadFile(string fileName);
	static vector<double> ConvertToDouble(vector<string>& str);//convert string to double 
	static void FindXYZForSeam(vector<vector<string>>& allStringGeo, vector<vector<string>>& allStringPos, vector<vector<string>>& allStringAngle,int seam,
		vector<double>& x,vector<double>& y,vector<double>& z);
private:
	static void ReadALine(string oneLine,vector<string> &oneLineString);
	static void ReArrangeLines(vector<string>& keywordString, map<string, vector<string>> &finalStrings);

	static int FindStringPos(vector<string>& vecString, string keyWord);
	static int FindStringPos(vector<vector<string>>& allStringGeo,string keyWord);//find the num col of keyword in geology.csv
	//static vector<double> LengthConvertToHeight(vector<double>& distance,vector<string>& dhid, vector<vector<string>>& allStringAngle);

	static map<string, vector<vector<string>>> ConvertToMap(vector<vector<string>>& allStrings);
	static vec3 CalPosForOneDhid(string dhid, double distance,double xSurface,double ySurface,double zSurface
		, map<string, vector<vector<string>>> &mapAngle);
};

