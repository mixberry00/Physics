#include "MathModel.h"
#include <cmath>



MathModel::MathModel(double A0, double beta, double omega, double dt, double r)
{
	this->A0 = A0;
	this->beta = beta;
	this->omega = omega;
	this->dt = dt;
	this->r = r;
}
void MathModel::Compute()
{
	angle = A0 * pow(e, -beta * dt) * cos(omega * dt);
	x = r * cos(angle);
	y = r * sin(angle);
}
double MathModel::GetX()
{
	return x;
}


double MathModel::GetY()
{
	return y;
}

double MathModel::GetA()
{
	return A0;
}

double MathModel::GetBeta()
{
	return beta;
}

double MathModel::GetOmega()
{
	return omega;
}

double MathModel::GetAngle()
{
	return angle;
}



MathModel::~MathModel()
{
}
