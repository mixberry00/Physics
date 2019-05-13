#include "bullet.h"

physics::bullet::bullet(const float _m, const QVector3D &_r, Qt3DCore::QNode *parent) :
    MaterialPoint(_m, _r, parent)
{
}

QVector3D physics::bullet::pos(const float t)
{
    return r + v(t) * t;
}

QVector3D physics::bullet::v(const float t)
{
    // пуля движется с постоянной скоростью. Скорость определяется из
    // закона сохранения энергии: потенциальная энергия упругой
    // деформации пружины переходит в кинетическую энергию пули
    return { b * sqrtf(k / m), 0, 0 };
}
