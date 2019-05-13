#include "pendulum.h"

physics::pendulum::pendulum(const float _m, const QVector3D &_r, bullet &_B, Qt3DCore::QNode *parent) :
    MaterialPoint(_m, _r, parent), B(_B)
{
    float v0 = B.v(0).x() * m / (B.m + m);
    float _g = g.length();
    A = v0 * sqrtf(l / _g);
    float Al = A / l;
    h = v0 * v0 / _g / 2;
    C1 = A * (1 - _g / l);
    C2 = (h - _g * (asinf(Al) * asinf(Al) / 2 - cosf(asinf(Al)) + 1)) / asinf(Al);
}

QVector3D physics::pendulum::pos(const float t)
{
    float x = A / l * sinf(omega * t);
    float alpha = asinf(x);
    return {
             g.length() * x + C1 * alpha,
             g.length() * (alpha * alpha / 2 - cosf(alpha) + 1) + C2 * alpha,
             0
           };
}

QVector3D physics::pendulum::v(const float t)
{
    float alpha = asinf(A / l * sinf(omega * t));
    return {
             g.length() * cosf(alpha),
             g.length() * (alpha + sinf(alpha)),
             0
           };
}
