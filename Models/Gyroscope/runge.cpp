#include "runge.h"

Runge::Runge()
{
    phi_dot = phi_dot0;
    psi_dot = psi_dot0;
    theta = theta0;
    theta_dot = theta_dot0;
    p_psi = I_psi * (psi_dot0 + phi_dot0 * cos(theta0));
    p_phi = p_psi * cos(theta0) + I0 * phi_dot0 * sin(theta0) * sin(theta0);
}

void Runge::Calculate(double dt)
{
    K[0][0] = dt * dy1(theta);
    K[0][1] = dt * dy1(theta + K[0][0] / 2);
    K[0][2] = dt * dy1(theta + K[0][1] / 2);
    K[0][3] = dt * dy1(theta + K[0][2]);

    theta_dot = theta_dot + (K[0][0] + 2 * K[0][1] + 2 * K[0][2] + K[0][3]) / 6;

    K[1][0] = dt * dy2(theta_dot);
    K[1][1] = dt * dy2(theta_dot + K[1][0] / 2);
    K[1][2] = dt * dy2(theta_dot + K[1][1] / 2);
    K[1][3] = dt * dy2(theta_dot + K[1][2]);

    theta = theta + (K[1][0] + 2 * K[1][1] + 2 * K[1][2] + K[1][3]) / 6;

    phi_dot = p_phi - p_psi * cos(theta);
    phi_dot /= I0;
    phi_dot /= sin(theta);
    phi_dot /= sin(theta);

    psi_dot = p_psi / I_psi;
    psi_dot -= phi_dot * cos(theta);
}
