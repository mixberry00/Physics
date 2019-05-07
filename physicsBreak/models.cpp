#include "models.h"

Qt3DCore::QEntity *addObject(Qt3DCore::QEntity *entity, QString obj, QString texture)
{
      Qt3DCore::QEntity *mesh = new Qt3DCore::QEntity(entity);
      Qt3DRender::QMesh *objMesh = new Qt3DRender::QMesh(mesh);
      objMesh->setSource(QUrl::fromLocalFile(obj));

      Qt3DRender::QTextureLoader *tLoader = new Qt3DRender::QTextureLoader(mesh);
      tLoader->setSource(QUrl::fromLocalFile(texture));

      Qt3DExtras::QDiffuseSpecularMapMaterial *Mat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
      Mat->setDiffuse(tLoader);
      Mat->setShininess(8.2f);
      Mat->setAmbient(QColor::fromRgb(255, 255, 255));
      Mat->setSpecular(tLoader);
      mesh->addComponent(objMesh);
      mesh->addComponent(Mat);
      return mesh;
}

Model1::Model1()
{
    ent = new Qt3DCore::QEntity();

    addObject(ent, ":/Res/Room.obj", ":/Res/Room.png");
    addObject(ent, ":/Res/tablemetal.obj", ":/Res/tablemetal.png");
    addObject(ent, ":/Stands/Math1/base.obj", ":/Stands/Math1/full.png");
    addObject(ent, ":/Stands/Math1/base.obj", ":/Stands/Math1/full.png");
    Qt3DCore::QEntity *obj1 = addObject(ent, ":/Stands/Math1/palka.obj", ":/Stands/Math1/palka.jpg");
    Qt3DCore::QEntity *obj2 = addObject(ent, ":/Stands/Math1/shar1.obj", ":/Stands/Math1/sharik.jpg");
    Qt3DCore::QEntity *obj3 = addObject(ent, ":/Stands/Math1/shar2.obj", ":/Stands/Math1/sharik.jpg");

    tr1 = new Qt3DCore::QTransform();
    obj1->addComponent(tr1);
    obj2->addComponent(tr1);
    obj3->addComponent(tr1);
}

void Model1::Init(double A0, double beta, double omega, double r)
{
    this->A0 = A0;
    this->beta = beta;
    this->omega = omega;
    this->r = r;
    t = 0.;
}
void Model1::Compute(double dt)
{
    t+=dt;
    angle = A0 * pow(e, -beta * t) * cos(omega * t);
    x = r * cos(angle);
    y = r * sin(angle);
}

void Model1::Transform()
{
   tr1->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0, 1.0, 0.0), angle));
}

void Model1::Update(double dt)
{
    Compute(dt);
    Transform();
}

Qt3DCore::QEntity *Model1::GetEntity()
{
    return ent;
}

double Model1::GetX()
{
    return x;
}

double Model1::GetY()
{
    return y;
}

double Model1::GetA()
{
    return A0;
}

double Model1::GetBeta()
{
    return beta;
}

double Model1::GetOmega()
{
    return omega;
}

double Model1::GetAngle()
{
    return angle;
}

Model1::~Model1()
{
}

