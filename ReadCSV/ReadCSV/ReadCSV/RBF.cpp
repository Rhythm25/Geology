#include "RBF.h"
void RBF::GetRBFCoef(vector<double>& x, vector<double>& y, vector<double>& z) {
	xSample.assign(x.begin(), x.end());
	ySample.assign(y.begin(), y.end());

	GetMinDis();

	Eigen::VectorXd coefMatrix(x.size()),zMatrix(z.size());
	Eigen::MatrixXd disMatrix(x.size(), x.size());

	for (int i = 0; i < x.size(); i++) {
		for (int j = 0; j < x.size(); j++) {
			disMatrix(i, j) = RadiusBase(Distance(x[i], y[i], x[j], y[j]), j);
			//cout << disMatrix(i, j) << endl;
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
		returnZ+= RadiusBase(Distance(x, y, xSample[i], ySample[i]), i)*coef[i];
		//cout << RadiusBase(Distance(x, y, xSample[i], ySample[i]), i) * coef[i] << endl;
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

double RBF::RadiusBase(double distance,int i) {
	switch (1) {
	case 1:
		return pow(pow(distance, 2) + pow(minDis[i], 2), mu);
		break;
	case 2:
		cout << pow(distance, 2) << endl;
		return pow(e,-pow(distance, 2)) ;
		break;
	default:
		break;
	}
	
}