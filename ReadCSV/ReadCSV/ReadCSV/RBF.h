#pragma once
#include <iostream>   
#include <vector> 
#include <Eigen/Dense>
#include "vec3.h"
#define e 2.71828
using namespace std;
class RBF
{
public:
	RBF() {
		mu = -0.5;
		xSample.clear();
		ySample.clear();
		coef.clear();
		minDis.clear();
		//yCoef.clear();
	}
	double GetRBF(double x, double y);
	void setMu(double muValue) {
		mu = muValue;
	}
	void GetRBFCoef(vector<double> &x, vector<double>& y, vector<double>& z);

	void GetXYZforMesh(double xMin, double xMax, double yMin, double yMax, double xUnit, double yUnit
		, vector<vector<vec3>>& xyz);

private:
	void GetMinDis();
	double GetMinDisForMesh(double x, double y);

	double RadiusBase(double distance,int i);

	inline double Distance(double x1, double y1, double x2, double y2) {
		return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	}
	double mu;
	vector<double> xSample, ySample,coef,minDis;
};

