#include "IDWCoef.h"

double IDWCoef::GetIDW(vector<double>& xSample, vector<double>& ySample, vector<double>& zSample, double x, double y, double r) {
	vector<double> distanceVec = DistanceVec(xSample, ySample, x, y,r);
	double z=0.0;
	double disSum = 0.0;
	//if (distanceVec.size() != 0) {
		for (int i = 0; i < distanceVec.size(); i++) {
			z += zSample[i] / pow(distanceVec[i], mu);
			disSum += 1 / pow(distanceVec[i], mu);
		}
		z /= disSum;
	/*}
	else {
		distanceVec.clear();
		distanceVec = DistanceVec(xSample, ySample, x, y, 1e8);
		for (int i = 0; i < distanceVec.size(); i++) {
			z += zSample[i] / pow(distanceVec[i], mu);
			disSum += 1 / pow(distanceVec[i], mu);
		}
		z /= disSum;
	}*/
	
	return z;
}

vector<double> IDWCoef::DistanceVec(vector<double>& xSample, vector<double>& ySample, double x, double y, double r) {
	vector<double> distanceVec;
	for (int i = 0; i < xSample.size(); i++) {
		double length = sqrt((x - xSample[i]) * (x - xSample[i]) + (y - ySample[i]) * (y - ySample[i]));
		if(length<r)
		 distanceVec.push_back(length);
	}
	return distanceVec;
}