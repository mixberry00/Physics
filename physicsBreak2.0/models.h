#ifndef MODELS_H
#define MODELS_H
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <cmath>
#include "plot.h"

Qt3DCore::QEntity *addObject(Qt3DCore::QEntity *, QString, QString);

const double PI = std::asin(1.);
const double e = std::exp(1.);
const double g = 9.8066;

class Model
{
public:
    virtual void Init() = 0;
    virtual void Update(double) = 0;
    virtual Qt3DCore::QEntity *GetEntity() = 0;
    virtual QVBoxLayout *GetSet() = 0;
    virtual QVBoxLayout *GetInf() = 0;
};


class Model1 : public virtual Model, QObject
{
private:
    double A0, beta, omega, angle, t;
    Qt3DCore::QEntity *ent;
    QVBoxLayout *set, *inf;
    QLabel *i1, *i2, *k1, *k2, *k3;
    QSlider *s1, *s2, *s3;
    Qt3DCore::QTransform *tr1, *tr2, *tr3;
    QList<Plot *> plots;
public:
    Model1();
    void Init();
    void Compute();
    void Transform();
    void Update(double);
    void CreatePlot(int);
    double GetA();
    double GetBeta();
    double GetOmega();
    double GetAngle();
    double GetTime();
    Qt3DCore::QEntity *GetEntity();
    QVBoxLayout *GetSet();
    QVBoxLayout *GetInf();
    ~Model1();
};


class Model2 : public virtual Model, QObject
{
private:
    double I_psi, I0;
    double mass, radius, length;
    double psi, psi_dot;
    double phi, phi_dot;
    double theta, theta_dot;
    double L_psi, L_phi;
    double time;
    void CalculateConstants();
    void Transform();
    void LoadModel();
    Qt3DCore::QEntity *ent;
    QVBoxLayout *set, *inf;
    QLabel *i1, *i2, *k1, *k2, *k3;
    QSlider *s1, *s2, *s3;
    Qt3DCore::QTransform *tr1, *tr2, *tr3;
    QList<Plot *> plots;
    double dy1(double arg);
    double dy2(double arg);
    double dy3(double arg);
    double dy4(double arg);
    QQuaternion rotation, nutation, precession;
    QElapsedTimer *t;
public:
    Model2();
    void Init();
    void Compute(double);
    void Update(double);
    void CreatePlot(int);
    double GetPsi() { return psi; }
    double GetPhi() { return phi; }
    double GetTheta() { return theta; }
    double GetTime() { return time; }
    Qt3DCore::QEntity *GetEntity(){return ent; }
    QVBoxLayout *GetSet(){return set; }
    QVBoxLayout *GetInf() {return inf; }
    ~Model2(){}
};





#endif // MODELS_H
