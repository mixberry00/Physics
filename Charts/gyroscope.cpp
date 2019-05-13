#include "gyroscope.h"
#include "mainwindow.h"

Gyroscope::Gyroscope(MainWindow *parent, double mass, double radius, double length, double psi_dot, double phi_dot, double theta)
{
    this->parent = parent;
    this->mass = mass;
    this->radius = radius;
    this->length = length;
    this->psi_dot = psi_dot;
    this->phi_dot = phi_dot;
    this->theta = theta;

    theta_dot = 0;
    phi = 0;
    psi = 0;
    time = 0;

    CalculateConstants();
    LoadModel();

    diskTransform = new Qt3DCore::QTransform();
    axisTransform = new Qt3DCore::QTransform();
    boxTransform = new  Qt3DCore::QTransform();

    disk->addComponent(diskTransform);
    axis->addComponent(axisTransform);
    box->addComponent(boxTransform);

    SetTransform();
}

void Gyroscope::Update(double dt)
{
    CalculateValues(dt);
    Transform();
}

void Gyroscope::SetMass(double mass)
{
    this->mass = mass;
    CalculateConstants();
}

void Gyroscope::SetRadius(double radius)
{
    this->radius = radius;
    CalculateConstants();
    SetTransform();
}

void Gyroscope::SetLength(double length)
{
    this->length = length;
    CalculateConstants();
    SetTransform();
}

void Gyroscope::SetTheta(double theta)
{
    this->theta = theta;
    CalculateConstants();
    SetTransform();
}

void Gyroscope::SetPsiDot(double psi_dot)
{
    this->psi_dot = psi_dot;
    CalculateConstants();
}

void Gyroscope::SetPhiDot(double phi_dot)
{
    this->phi_dot = phi_dot;
    CalculateConstants();
}

void Gyroscope::SetPhi(double phi)
{
    this->phi = phi;
}

void Gyroscope::SetPsi(double psi)
{
    this->psi = psi;
}

void Gyroscope::SetThetaDot(double theta_dot)
{
    this->theta_dot = theta_dot;
}

void Gyroscope::CalculateConstants()
{
    I_psi = 0.5 * mass * radius * radius;
    I0 = mass * length * length + I_psi * 0.5;
    L_psi = I_psi * (phi_dot * cos(theta) + psi_dot);
    L_phi = I0 * phi_dot * sin(theta) * sin(theta) + L_psi * cos(theta);

}

void Gyroscope::CalculateValues(double dt)
{
    time += dt;

    double K[4][4];

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

    phi_dot = L_phi - L_psi * cos(theta);
    phi_dot /= I0;
    phi_dot /= sin(theta);
    phi_dot /= sin(theta);

    psi_dot = L_psi / I_psi;
    psi_dot -= phi_dot * cos(theta);

    K[2][0] = dt * dy3(theta);
    K[2][1] = dt * dy3(theta + K[2][0] / 2);
    K[2][2] = dt * dy3(theta + K[2][1] / 2);
    K[2][3] = dt * dy3(theta + K[2][2]);

    phi = phi + (K[2][0] + 2 * K[2][1] + 2 * K[2][2] + K[2][3]) / 6;

    K[3][0] = dt * dy4(theta);
    K[3][1] = dt * dy4(theta + K[3][0] / 2);
    K[3][2] = dt * dy4(theta + K[3][1] / 2);
    K[3][3] = dt * dy4(theta + K[3][2]);

    psi = psi + (K[3][0] + 2 * K[3][1] + 2 * K[3][2] + K[3][3]) / 6;
}

void Gyroscope::Transform()
{
    rotation = QQuaternion::fromAxisAndAngle(QVector3D(0.0, 0.0, 1.0),  radToDeg * psi);
    precession = QQuaternion::fromAxisAndAngle(QVector3D(0.0, 1.0, 0.0), radToDeg * phi);
    nutation = QQuaternion::fromAxisAndAngle(QVector3D(1.0, 0.0, 0.0), radToDeg * theta - 90);

    diskTransform->setRotation(precession * nutation * rotation);
    axisTransform->setRotation(precession * nutation);
    boxTransform->setRotation(precession);

    diskPos = QVector3D(cos(pi / 2 - theta)*sin(phi)*(0.56 + 10 * length),
               sin(pi / 2 - theta)*(0.56 + 10 * length),
               cos(pi / 2 - theta)*cos(phi)*(0.56 + 10 * length));

    diskTransform->setTranslation(diskPos);
}

void Gyroscope::LoadModel()
{
    disk = parent->addObject(":/Res/disk.obj", ":/Res/DiskMat.png");
    axis = parent->addObject(":/Res/axis.obj", ":/Res/AxisMat.png");
    box = parent->addObject(":/Res/box.obj", ":/Res/boxMat.png");
    stand = parent->addObject(":/Res/stand.obj", ":/Res/standMat.png");
}

void Gyroscope::SetTransform()
{
    diskPos = QVector3D(cos(pi / 2 - theta)*sin(phi)*(0.56 + 10 * length),
               sin(pi / 2 - theta)*(0.56 + 10 * length),
               cos(pi / 2 - theta)*cos(phi)*(0.56 + 10 * length));

    nutation = QQuaternion::fromAxisAndAngle(QVector3D(1.0, 0.0, 0.0), 57.2957795131 * theta - 90);
    diskTransform->setRotation(precession * nutation * rotation);
    axisTransform->setRotation(precession * nutation);

    diskTransform->setScale3D(QVector3D(10 * radius,  10 * radius, 1.0));
    diskTransform->setTranslation(diskPos * length / 0.2);
}

double Gyroscope::dy1(double arg)
{
    double fun1 = -(L_phi - L_psi * cos(arg)) * L_psi;
    double fun2 = cos(arg) * (L_phi - L_psi * cos(arg)) * (L_phi - L_psi * cos(arg));
    double fun3 = mass * length * g * sin(arg);

    fun1 /= I0 * I0 * sin(arg);

    fun2 /= I0 * I0 * sin(arg) * sin(arg) * sin(arg);

    fun3 /= I0;

    return fun1 + fun2 + fun3;
}

double Gyroscope::dy2(double arg)
{
    return arg;
}

double Gyroscope::dy3(double arg)
{
    double fun1 = L_phi - L_psi * cos(arg);
    double fun2 = I0 * sin(arg) * sin(arg);

    return fun1 / fun2;
}

double Gyroscope::dy4(double arg)
{
    double fun1 = L_psi / I_psi;
    double fun2 = phi_dot * cos(arg);

    return fun1 - fun2;
}
