#pragma once
#include <cmath>
#include <vector>
using namespace std;
/*class Pend
{
public:
	const double PI = M_PI;
	virtual void Func() = 0;
	// Вычисление нового состояния модели, обновление данных
	virtual GetCoord() = 0;
	// Получить текущее положение
	virtual vector <double> GetSpeed() = 0;
	// Получить текущую скорость
	virtual vector <double> GetAссel() = 0;
	// Получить текущее ускорение
	virtual double GetEk() = 0;
	// Получить текущую кинетическую энергию
	virtual double GetEp() = 0;
	// Получить текущую потенинциальную энергию
	double GetE();
	// Получить текущую энергию


};
*/
class MathPend
{
private:
	const double PI = asin(1.);
	const double convGtoR = PI / 180.;
	const double g = 9.817;
	const double pl = 1.;
	const double Cx = 0.3;
	double M, L, A, W, E, S, Ek, Ep, Dt;
	/*
	M - масса
	L - длинна от крепления до центра шара
	Cx - коэффициент лобового сопротивления
	A - угловое положение
	W - угловая скорость
	E - угловое ускорение
	S - сечение сферы
	Ek - энергия кинетическая
	Ep - энергия потенциальная
	Dt - частота обновления
	*/
public:
	MathPend(double mass, double length, double radius, double start_axis,double start_speed, double dt);
	void Func();
	double GetCoord();
	double GetSpeed();
	double GetAссel();
	double GetEk();
	double GetEp();
	~MathPend();
};