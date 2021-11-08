#pragma once
#include <iostream>   
#include <vector> 

using namespace std;

class IDWCoef
{
public:
	IDWCoef() {
		mu = 1.0;
	}
	double GetIDW(vector<double>& xSample, vector<double>& ySample, vector<double>& zSample, double x,double y);
	void setMu(double muValue) {
		mu = muValue;
	}
private:
	vector<double> DistanceVec(vector<double>& xSample, vector<double>& ySample, double x, double y);
	double mu;
};

