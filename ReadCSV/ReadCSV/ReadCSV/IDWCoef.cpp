#include "IDWCoef.h"

double IDWCoef::GetIDW(vector<double>& xSample, vector<double>& ySample, vector<double>& zSample, double x, double y) {
	vector<double> distanceVec = DistanceVec(xSample, ySample, x, y);
	double z=0.0;
	double disSum = 0.0;
	for (int i = 0; i < xSample.size(); i++) {
		z += zSample[i] / pow(distanceVec[i], mu);
		disSum+=1 / pow(distanceVec[i], mu);
	}
	z /= disSum;
	return z;
}

vector<double> IDWCoef::DistanceVec(vector<double>& xSample, vector<double>& ySample, double x, double y) {
	vector<double> distanceVec;
	for (int i = 0; i < xSample.size(); i++) {
		distanceVec.push_back(sqrt((x - xSample[i]) * (x - xSample[i]) + (y - ySample[i]) * (y - ySample[i])));
	}
	return distanceVec;
}