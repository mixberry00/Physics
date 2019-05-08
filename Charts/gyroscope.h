#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <QtCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>

const double g = 9.81;

class Gyroscope
{
public:
    Gyroscope(class MainWindow *parent, double mass, double radius, double length, double psi_dot, double phi_dot, double theta);

    void Update(double dt);

    double GetPsi() { return psi; }
    double GetPhi() { return phi; }
    double GetTheta() { return theta; }
    double GetTime() { return time; }

    void SetMass(double mass);
    void SetRadius(double radius);
    void SetLength(double length);
    void SetTheta(double theta);
    void SetPsiDot(double psi_dot);
    void SetPhiDot(double phi_dot);
    void SetPhi(double phi);
    void SetPsi(double psi);
    void SetThetaDot(double theta_dot);

private:
    double I_psi, I0;
    double mass, radius, length;
    double psi, psi_dot;
    double phi, phi_dot;
    double theta, theta_dot;
    double L_psi, L_phi;
    double time;

    void CalculateConstants();
    void CalculateValues(double dt);
    void Transform();

    void LoadModel();
    void SetTransform();

    double dy1(double arg);
    double dy2(double arg);
    double dy3(double arg);
    double dy4(double arg);

    class MainWindow *parent;
    Qt3DCore::QEntity *disk;
    Qt3DCore::QEntity *axis;
    Qt3DCore::QEntity *stand;
    Qt3DCore::QEntity *box;

    Qt3DCore::QTransform *diskTransform;
    Qt3DCore::QTransform *axisTransform;
    Qt3DCore::QTransform *boxTransform;

    QQuaternion rotation;
    QQuaternion precession;
    QQuaternion nutation;
};

#endif
