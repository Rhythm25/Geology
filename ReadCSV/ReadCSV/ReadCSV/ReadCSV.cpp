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
	
	//At first, we convert vector<vector> to map<vector<vector>> for allStringAngle and allStringPos
	map<string, vector<vector<string>>> allMapAngle= ConvertToMap(allStringAngle);
	map<string, vector<vector<string>>> allMapPos = ConvertToMap(allStringPos);

	/*here findstringpos runs for three times, which can be reduced to one time*/
	vector<string> keyWord = allMapPos["dhid"][0];
	int eastNum = FindStringPos(keyWord, "east");
	int northNum= FindStringPos(keyWord, "north");
	int elNum = FindStringPos(keyWord, "el");

	//Now we have x,y,z and distances for seam on the surface, we need to convert to real position
	//We calculate pos

	/*here we only need map<string,vector<string>> instead of map<string,vector<vector<string>>>*/
	for (int i = 0; i < dhidHasSeam.size(); i++) {
		//vec3 onePos= CalPosForOneDhid
		double xSurface = atof(allMapPos[dhidHasSeam[i]][0][eastNum].c_str());
		double ySurface = atof(allMapPos[dhidHasSeam[i]][0][northNum].c_str());
		double zSurface = atof(allMapPos[dhidHasSeam[i]][0][elNum].c_str());
		
		vec3 onePos = CalPosForOneDhid(dhidHasSeam[i], fromDistanceSeam[i], xSurface, ySurface, zSurface, allMapAngle);
		//cout << onePos[0] - xSurface <<" "<< onePos[1] - ySurface << endl;

		x.push_back(onePos[0]); y.push_back(onePos[1]); z.push_back(onePos[2]);
	}
	
}

int ReadCSV::FindStringPos(vector<string>& vecString, string keyWord) {
	for (int i = 0; i < vecString.size(); i++) {
		if (vecString[i].compare(keyWord) == 0) return i;
	}

	cout << "Error: Cannot find " + keyWord + " keyword!" << endl;
	return -1;
}

int ReadCSV::FindStringPos(vector<vector<string>>& allStringGeo, string keyWord) {
	vector<string> keyWordString = allStringGeo[0];
	for (int i = 0; i < keyWordString.size(); i++) {
		if (keyWordString[i].compare(keyWord) == 0) return i;
	}
	cout << "Error: Cannot find "+keyWord+" keyword!" << endl;
	return -1;
}

map<string, vector<vector<string>>> ReadCSV::ConvertToMap(vector<vector<string>>& allStrings) {
	map<string, vector<vector<string>>> stringToMap;

	for (int i = 0; i < allStrings.size(); i++) {
		vector<string> oneLine=allStrings[i];
		vector<string> oneLineMap;

		for (int j = 1; j < oneLine.size(); j++) {
			oneLineMap.push_back(oneLine[j]);
		}
		stringToMap[oneLine[0]].push_back(oneLineMap);
	}

	return stringToMap;
}

vec3 ReadCSV::CalPosForOneDhid(string dhid, double distance, double xSurface, double ySurface, double zSurface,
	map<string, vector<vector<string>>> &mapAngle) {
	vec3 posSurface(xSurface, ySurface, zSurface);
	vec3 pos = posSurface;

	vector<string> keyWord = mapAngle["dhid"][0];
	int depthNum = FindStringPos(keyWord, "depth");
	int azimthNum = FindStringPos(keyWord, "azimth");
	int dipNum = FindStringPos(keyWord, "dip");
	//vector<double> depthString, azimthString, dipString;

	double height = 0.0,disTmp=distance;

	for (int i = 0; i < mapAngle[dhid].size(); i++) {
		vector<string> oneLine = mapAngle[dhid][i];

		double depth=atof(oneLine[depthNum].c_str());
		double azimth=atof(oneLine[azimthNum].c_str());
		double dip=atof(oneLine[dipNum].c_str());

		if (i + 1 < mapAngle[dhid].size()) {
			double sectionLength = atof(mapAngle[dhid][i + 1][depthNum].c_str())-depth;
			if (sectionLength < disTmp) {
				//cout << "0" << endl;
				vec3 sectionVec(sectionLength*cos(dip / 180 * PI) * cos(1.5 * PI - azimth / 180 * PI),
					sectionLength * cos(dip / 180 * PI) * sin(1.5 * PI - azimth / 180 * PI),
					sectionLength * sin(dip / 180 * PI));
				//cout << sectionVec[2] << " " << sectionLength << " " << dip << endl;
				pos += sectionVec;
				disTmp -= sectionLength;
			}
			else {
				//cout << "1" << endl;
				vec3 sectionVec(disTmp * cos(dip / 180 * PI) * cos(1.5 * PI - azimth / 180 * PI),
					disTmp * cos(dip / 180 * PI) * sin(1.5 * PI - azimth / 180 * PI),
					disTmp * sin(dip / 180 * PI));
				//cout << sectionVec[2] << " " << disTmp << " " << dip << endl;
				pos += sectionVec;
				return pos;
			}
		}
		else {
			//cout << "2" << endl;
			double sectionLength = 500 - depth;
			if (sectionLength < disTmp) {
				vec3 sectionVec(sectionLength * cos(dip / 180 * PI) * cos(1.5 * PI - azimth / 180 * PI),
					sectionLength * cos(dip / 180 * PI) * sin(1.5 * PI - azimth / 180 * PI),
					sectionLength * sin( dip / 180 * PI));
				pos += sectionVec;
				disTmp -= sectionLength;
				pos[2] = INFINITY;
				return pos;
			}
			else {
				
				vec3 sectionVec(disTmp * cos(dip / 180 * PI) * cos(1.5 * PI - azimth / 180 * PI),
					disTmp * cos(dip / 180 * PI) * sin(1.5 * PI - azimth / 180 * PI),
					disTmp * sin( dip / 180 * PI));
				//cout << sectionVec[2]<<" "<< disTmp <<" "<< dip << endl;
				pos += sectionVec;
				return pos;
			}
		}

	}

	return pos;
}

void ReadCSV::GetXYZforMesh(vector<double>& x, vector<double>& y, vector<double>& z, double xMin, double xMax, double yMin, double yMax, double xUnit, double yUnit
	, double r, vector<vector<vec3>>& xyz) {
	IDWCoef* idwSolver = new IDWCoef();
	double xPos = xMin, yPos = yMin;
	while (xPos < xMax) {
		vector<vec3> oneLinePos;
		while (yPos < yMax) {			
			double zPos = idwSolver->GetIDW(x, y, z, xPos, yPos,r);

			
			 oneLinePos.push_back(vec3(xPos, yPos, zPos));
			

			yPos += yUnit;
		}
		xyz.push_back(oneLinePos);
		xPos += xUnit;
		yPos = yMin;
	}
	delete idwSolver;
}