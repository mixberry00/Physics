#ifndef PENDULUM_H
#define PENDULUM_H

#include "materialpoint.h"
#include "bullet.h"

namespace physics {

class pendulum : public MaterialPoint
{
public:
    float omega; // циклическая частота
    float A    ; // амплитуда колебаний по оси x
    float h    ; // амплитуда колебаний по оси y
    float C1   ; // константа из решения диффура по оси x
    float C2   ; // константа из решения диффура по оси y
    bullet &B  ; // пуля, с которой произошло столкновение
    pendulum(const float _m, const QVector3D &_r, bullet &_B, Qt3DCore::QNode *parent = nullptr);
    QVector3D pos(const float t) override;
    QVector3D v(const float t)   override;
};

}
#endif // PENDULUM_H
