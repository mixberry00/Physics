#ifndef OBJECT_H
#define OBJECT_H

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DExtras>

namespace physics {

class object : public QObject
{
private:
    Qt3DCore::QEntity *_entity;
    Qt3DRender::QMesh *_mesh;
    Qt3DExtras::QDiffuseMapMaterial *_texture;
    Qt3DCore::QTransform *_transform;

public:
    object(Qt3DCore::QNode *parent = nullptr);
    void setMesh(const QString &src);
    void setTexture(const QString &src);
    void setPosition(const QVector3D &pos);
    void setScale(const float scale);
};
}
#endif // OBJECT_H
