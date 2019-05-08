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


class Model1 : QObject
{
private:
    const double PI = std::asin(1.);
    const double e = std::exp(1.);
    double A0, beta, omega, angle, t;
    Qt3DCore::QEntity *ent;
    QVBoxLayout *set, *inf;
    QLabel *i1, *i2, *k1, *k2, *k3;
    QSlider *s1, *s2, *s3;
    Qt3DCore::QTransform *tr1;
    Plot *pl;
public:
    Model1();
    void Init();
    void Compute(double);
    void Transform();
    void Update(double);
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


#endif // MODELS_H
