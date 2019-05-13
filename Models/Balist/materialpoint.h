#ifndef MATERIALPOINT_H
#define MATERIALPOINT_H

#include <QtMath>
#include <Qt3DCore>
#include "object.h"

namespace physics {

static const float PI = float(M_PI); // число пи ~ 3.1415...
// параметры системы
static const QVector3D g(0, -9.81f, 0); // ускорение свободного падения
static float k = 1.0f ; // жёсткость пружины
static float l = 0.4f ; // длина маятника
static float b = 0.01f; // деформация пружины

class MaterialPoint : public object
{
    Q_OBJECT
    Q_PROPERTY(float time READ getTime WRITE setTime)
public:
    MaterialPoint(const float _m, const QVector3D &_r, Qt3DCore::QNode *parent = nullptr);
    //virtual ~MaterialPoint();
    float     m; // масса
    QVector3D r; // начальное положение, радиус-вектор
    float  _time;
    virtual QVector3D pos(const float t) = 0; // текущее положение, радиус-вектор
    virtual QVector3D v(const float t) = 0;   // мгновенная скорость
    void setTime(const float t);
    float getTime() const;
};

}
#endif // MATERIALPOINT_H
