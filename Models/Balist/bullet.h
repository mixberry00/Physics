#ifndef BULLET_H
#define BULLET_H

#include "materialpoint.h"

namespace physics {

class bullet : public MaterialPoint
{
public:
    bullet(const float _m, const QVector3D &_r, Qt3DCore::QNode *parent = nullptr);
    QVector3D pos(const float t) override;
    QVector3D v(const float t)   override;
};
}
#endif // BULLET_H
