#include "measurer.h"

physics::measurer::measurer(const float _m, const QVector3D &_r, pendulum &_P, Qt3DCore::QNode *parent) :
    MaterialPoint(_m, _r, parent), P(_P)
{
}

QVector3D physics::measurer::pos(const float t)
{
    QVector3D p = P.pos(t);
    if (r.x() < p.x()) {
        r = p;
    }
    return r;
}

QVector3D physics::measurer::v(const float t)
{
    QVector3D p = P.pos(t);
    return r.x() < p.x() ? P.v(t) : QVector3D(0, 0, 0);
}
