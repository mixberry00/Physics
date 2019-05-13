#include "object.h"

physics::object::object(Qt3DCore::QNode *parent) :
    QObject (parent)
{
    _entity = new Qt3DCore::QEntity(parent);
    _mesh = new Qt3DRender::QMesh;
    _texture = new Qt3DExtras::QDiffuseMapMaterial;
    _transform = new Qt3DCore::QTransform;
    _entity->addComponent(_mesh);
    _entity->addComponent(_texture);
    _entity->addComponent(_transform);
}

void physics::object::setMesh(const QString &src)
{
    _mesh->setSource(QUrl::fromLocalFile(src));
}

void physics::object::setTexture(const QString &src)
{
    Qt3DRender::QTextureLoader *loader = new Qt3DRender::QTextureLoader(_entity);
    loader->setSource(QUrl::fromLocalFile(src));
    _texture->setDiffuse(loader);
    _texture->setShininess(.0f);
}

void physics::object::setPosition(const QVector3D &pos)
{
    _transform->setTranslation(pos);
}

void physics::object::setScale(const float scale)
{
    _transform->setScale(scale);
}
