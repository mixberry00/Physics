#ifndef RUNGE_H
#define RUNGE_H

#include <QtCore>

const double I_psi = 0.00125;
const double I0 = 0.00233;
const double m = 0.1;
const double r = 0.05;
const double l = 0.15;
const double g = 9.81;
const double psi_dot0 = 628;
const double phi_dot0 = -3;
const double theta0 = 0.4;
const double theta_dot0 = 0;

class Runge
{
public:
    Runge();
    void Calculate(double dt);
    double GetPhiDot() { return phi_dot; }
    double GetPsiDot() { return psi_dot; }
    double GetThetaDot() { return theta_dot; }
    double GetTheta() { return theta; }


private:
    double p_psi;
    double p_phi;
    double phi_dot;
    double psi_dot;
    double theta_dot;
    double theta;

    double K[2][4];

    double dy1(double y2)
    {
        double fun1 = -(p_phi - p_psi * cos(y2)) * p_psi;
        double fun2 = cos(y2) * (p_phi - p_psi * cos(y2)) * (p_phi - p_psi * cos(y2));
        double fun3 = m * l * g * sin(y2);

        fun1 = fun1 /  I0;
        fun1 = fun1 / sin(y2);

        fun2 = fun2 / I0;
        fun2 = fun2 / sin(y2);
        fun2 = fun2 / sin(y2);
        fun2 = fun2 / sin(y2);

        return fun1 + fun2 + fun3;
    }

    double dy2(double y1)
    {
        return y1;
    }
};

#endif // RUNGE_H
