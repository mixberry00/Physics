#include "MathModel.h"
#include <cmath>
#include <stdio.h>
#include <conio.h>


void main() 
{
	//ввод данных с интерфейса
    double m; // масса шариков 
	double k; //коэф упр
	double c;//коэф сопротивления среды
	double r;//расстояние шариков от центра(радиус)
	double fi0;// начальный угол
	double beta = (с/(2*sqrt(m*k)))/(4*m*r*r);
	double omega = sqrt((k)/(2*m*r*r))
	MathModel* mm = new MathModel(1., beta, omega, 0.1);
	if(mm->GetBeta() < nm->GetOmega())
	{
		//расчет
	 printf_s("%f\n%f",mm->GetA(), mm->GetBeta(), mm->GetOmega());
	}
	else
	{
		//некорректные данные
	}
	_getch();
}