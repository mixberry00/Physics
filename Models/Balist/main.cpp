#include <QGuiApplication>
#include "pendulum.h"
#include "measurer.h"
#include "bullet.h"
#include "Camera.h"
#include <Qt3DExtras>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    Qt3DExtras::Qt3DWindow w;
    w.setWindowState(Qt::WindowMaximized);

    Qt3DCore::QEntity *root = new Qt3DCore::QEntity;
    physics::object *dom = new physics::object(root),
            *doska = new physics::object(root),
            *kartina = new physics::object(root),
            *knopka = new physics::object(root),
            *lineyka = new physics::object(root),
            *osi = new physics::object(root),
            *pistol = new physics::object(root),
            *polka = new physics::object(root);
    physics::bullet *bullet  = new  physics::bullet(0.01f, QVector3D(0, 0, 0), root);
    physics::pendulum *mayatnik = new physics::pendulum(0.2f, QVector3D(0, 0, 0), *bullet, root);
    physics::measurer *izmeritel = new physics::measurer(0.01f, QVector3D(0, 0, 0), *mayatnik, root);


    dom->setMesh(":/res/dom.obj");
    dom->setTexture(":/res/dom.png");
    dom->setPosition(QVector3D(0, 0, 0));

    doska->setMesh(":/res/doska.obj");
    doska->setTexture(":/res/doska.png");
    doska->setPosition(QVector3D(0, 0, 0));

    izmeritel->setMesh(":/res/izmeritel.obj");
    izmeritel->setTexture(":/res/izmeritel.png");
    izmeritel->setPosition(QVector3D(0, 0, 0));

    kartina->setMesh(":/res/kartina.obj");
    kartina->setTexture(":/res/kartina.png");
    kartina->setPosition(QVector3D(0, 0, 0));

    knopka->setMesh(":/res/knopka.obj");
    knopka->setTexture(":/res/knopka.png");
    knopka->setPosition(QVector3D(0, 0, 0));

    lineyka->setMesh(":/res/lineyka.obj");
    lineyka->setTexture(":/res/lineyka.png");
    lineyka->setPosition(QVector3D(0, 0, 0));

    mayatnik->setMesh(":/res/mayatnik.obj");
    mayatnik->setTexture(":/res/mayatnik.png");
    mayatnik->setPosition(QVector3D(0, 0, 0));

    osi->setMesh(":/res/osi.obj");
    osi->setTexture(":/res/osi.png");
    osi->setPosition(QVector3D(0, 0, 0));

    pistol->setMesh(":/res/pistol.obj");
    pistol->setTexture(":/res/pistol.png");
    pistol->setPosition(QVector3D(0, 0, 0));

    polka->setMesh(":/res/polka.obj");
    polka->setTexture(":/res/polka.png");
    polka->setPosition(QVector3D(0, 0, 0));

    Qt3DExtras::QOrbitCameraController cam(root);
    //// камера (а точнее, контроллер камеры)
    //Camera cam(root); // контроллер
    cam.setCamera(w.camera()); // прикрепить камеру к контроллеру
    cam.camera()->setPosition(QVector3D(5, 3, 0.75f)); // начальное положение камеры
    cam.camera()->setViewCenter(QVector3D(-5, 3, 0.75f)); // точка, вокруг которой камера будет вращаться
    cam.setLookSpeed(100); // скорость вращения
    cam.setLinearSpeed(10); // скорость зума

    //Qt3DCore::QEntity *test = new Qt3DCore::QEntity(root);
    //Qt3DExtras::QCuboidMesh *cube = new Qt3DExtras::QCuboidMesh;
    //Qt3DExtras::QPhongMaterial *mat = new Qt3DExtras::QPhongMaterial;
    //Qt3DCore::QTransform *trans = new Qt3DCore::QTransform;
    //cube->setXExtent(0.1f);
    //cube->setYExtent(0.1f);
    //cube->setZExtent(1); // между пистолетом и маятником 2 единицы координат
    //trans->setScale(1);
    //trans->setTranslation(QVector3D(-4.2f, 3.2f, -0.015f));
    //mat->setDiffuse(QColor(255, 0, 0));
    //test->addComponent(cube);
    //test->addComponent(mat);
    //test->addComponent(trans);

    float scale = 1e4f;
    QPropertyAnimation *P = new QPropertyAnimation(mayatnik, "time");
    P->setDuration(int(2 * physics::PI * sqrtf(physics::l / physics::g.length()) * scale));
    qDebug() << int(2 * physics::PI * sqrtf(physics::l / physics::g.length()) * scale);
    P->setLoopCount(-1);
    P->setStartValue(0);
    P->setEndValue(2 * physics::PI * sqrtf(physics::l / physics::g.length()));
    QPropertyAnimation *M = new QPropertyAnimation(izmeritel, "time");
    M->setDuration(int(physics::PI * sqrtf(physics::l / physics::g.length()) / 2.0f * scale));
    M->setLoopCount(1);
    M->setStartValue(0);
    M->setEndValue(physics::PI * sqrtf(physics::l / physics::g.length()) / 2.0f);
    QParallelAnimationGroup *group = new QParallelAnimationGroup;
    group->addAnimation(P);
    group->addAnimation(M);

    w.setRootEntity(root);
    w.show();
    group->start();
    return app.exec();
}
