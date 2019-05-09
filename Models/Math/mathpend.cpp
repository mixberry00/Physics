#include "mathpend.h"


MathPend::MathPend(double m, double l, double r, double sa, double ss, double dt)
{
	M = m;
	L = l;
	S = PI * r * r;
	A = sa * convGtoR;
	W = ss * convGtoR;
	Dt = dt;
}

void MathPend::Func()
{
	E = -g * sin(A) / L;
	if (W > 0)
		E -= Cx * pl * W * W * S / (2 * M);
	else
		E += Cx * pl * W * W * S / (2 * M);
	W += E * Dt;
	A += W * Dt;

	Ek = M * W * W * L * L / 2;
	Ep = M * g * L * (1 - cos(A));
}

double MathPend::GetCoord()
{
	return A;
}

double MathPend::GetSpeed()
{
	return W;
}

double MathPend::GetAññel()
{
	return E;
}

double MathPend::GetEk()
{
	return Ek;
}

double MathPend::GetEp()
{
	return Ep;
}

MathPend::~MathPend() {}
