#ifndef MODELS_H
#define MODELS_H
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>
#include <cmath>

Qt3DCore::QEntity *addObject(Qt3DCore::QEntity *, QString, QString);

class Model1
{
private:
    const double PI = std::asin(1.);
    const double e = std::exp(1.);
    double A0, beta, omega, x = 1., y = 0., angle = 0., r, t;
    Qt3DCore::QEntity *ent;
    Qt3DCore::QTransform *tr1;
public:
    Model1();
    void Init(double, double, double, double);
    void Compute(double);
    void Transform();
    void Update(double);
    double GetX();
    double GetY();
    double GetA();
    double GetBeta();
    double GetOmega();
    double GetAngle();
    double GetRadius();
    Qt3DCore::QEntity *GetEntity();
    ~Model1();
};


#endif // MODELS_H
