#include "materialpoint.h"

physics::MaterialPoint::MaterialPoint(const float _m, const QVector3D &_r, Qt3DCore::QNode *parent) :
    object(parent), m(_m), r(_r)
{
}

void physics::MaterialPoint::setTime(const float t)
{
    _time = t;
    setPosition(pos(t));
    qDebug() << t;
}


float physics::MaterialPoint::getTime() const
{
    return _time;
}
