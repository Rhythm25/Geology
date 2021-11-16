#include "RBF.h"
void RBF::GetRBFCoef(vector<double>& x, vector<double>& y, vector<double>& z) {
	xSample.assign(x.begin(), x.end());
	ySample.assign(y.begin(), y.end());

	GetMinDis();

	Eigen::VectorXd coefMatrix(x.size()),zMatrix(z.size());
	Eigen::MatrixXd disMatrix(x.size(), x.size());

	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x.size(); j++) {
			disMatrix(i, j) = pow(pow(Distance(x[i], y[i], x[j], y[j]), 2) + pow(minDis[j], 2), mu);
		}
		zMatrix[i] = z[i];
	}

	coefMatrix = disMatrix.inverse() * zMatrix;

	for (int i = 0; i < x.size(); i++)
		coef.push_back(coefMatrix[i]);

	//cout << coefMatrix << endl;
}

void RBF::GetMinDis() {
	for (int i = 0; i < xSample.size(); i++) {
		double minTmp = INFINITY;
		for (int j = 0; j < xSample.size(); j++) {
			if (j != i) {
				double disTmp = Distance(xSample[i], ySample[i], xSample[j], ySample[j]);
				if (disTmp < minTmp) {
					minTmp = disTmp;
				}
			}
			
		}
		minDis.push_back(minTmp);
	}
}

double RBF::GetRBF(double x, double y) {
	double returnZ=0.0;
	for (int i = 0; i < coef.size(); i++) {
		returnZ+= pow(pow(Distance(x, y, xSample[i], ySample[i]), 2) + pow(minDis[i], 2), mu)*coef[i];
	}
	return returnZ;
}

double RBF::GetMinDisForMesh(double x, double y) {
	double minTmp = INFINITY;
	for (int i = 0; i < xSample.size(); i++) {		
		double disTmp = Distance(xSample[i], ySample[i], x, y);
		if (disTmp > 1e-6) {
			if (disTmp < minTmp) {
				minTmp = disTmp;
			}
		}
		else
			return minDis[i];
		
	}
	return minTmp;
}

void RBF::GetXYZforMesh(double xMin, double xMax, double yMin, double yMax, double xUnit, double yUnit
	, vector<vector<vec3>>& xyz) {
	double xPos = xMin, yPos = yMin;
	while (xPos < xMax) {
		vector<vec3> oneLinePos;
		while (yPos < yMax) {
			double zPos = GetRBF(xPos, yPos);


			oneLinePos.push_back(vec3(xPos, yPos, zPos));


			yPos += yUnit;
		}
		xyz.push_back(oneLinePos);
		xPos += xUnit;
		yPos = yMin;
	}

}