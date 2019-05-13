#pragma once
#include <math.h>
using namespace std;
class MathModel
{
private:
	const double PI = asin(1.);
	const double e = exp(1.);
	double A0, beta, omega, dt, x = 1., y = 0., angle = 0, r;
public:
	MathModel(double, double, double, double, double);
	void Compute();
	double GetX();
	double GetY();
	double GetA();
	double GetBeta();
	double GetOmega();
	double GetAngle();
	double GetRadius();
	~MathModel();
};

