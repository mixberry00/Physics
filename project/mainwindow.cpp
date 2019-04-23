#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->w->setGeometry(0, 0, width() * 0.75, height());

    sceneWindow = new Qt3DExtras::Qt3DWindow();

    ev = new MouseEv(this);
    sceneWindow->installEventFilter(ev);
    sceneWindow->defaultFrameGraph()->setClearColor(QColor(QRgb(0x888888)));

    scene = QWidget::createWindowContainer(sceneWindow, ui->w);
    scene->setGeometry(ui->w->geometry());
    sceneEntity = new Qt3DCore::QEntity();
    sceneWindow->setRootEntity(sceneEntity);

    /*Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(sceneEntity);
    Qt3DRender::QSpotLight *light = new Qt3DRender::QSpotLight(lightEntity);
    light->setColor("white");
    light->setIntensity(1);
    light->setCutOffAngle(120);
    light->setLocalDirection(QVector3D(0.0, -1.0, 0.0));
    light->setLinearAttenuation(0.1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(0.0, 1.0, 0.0));
    lightEntity->addComponent(lightTransform);*/

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(sceneEntity);
    Qt3DRender::QPointLight *light = new Qt3DRender::QPointLight(lightEntity);
    light->setColor("white");
    light->setIntensity(0.6);
    light->setLinearAttenuation(0.1);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(10.0, 10.0, 0.0));
    lightEntity->addComponent(lightTransform);

    camera = sceneWindow->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(-radius, 0.0, 0));
    camera->setUpVector(QVector3D(0, 1, 0));
    camera->setViewCenter(QVector3D(0.0, 0.0, 0.0));


    timer = new QTimer();
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start();

    CreateEntity();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    ui->w->setGeometry(0, 0, width() * 0.75, height());
    scene->setGeometry(ui->w->geometry());
}

void MainWindow::mousePress(QMouseEvent *me)
{
    mouse_x = me->x();
    mouse_y = me->y();
}

void MainWindow::mouseMove(QMouseEvent *me)
{
    Qt::MouseButtons b = me->buttons();

    if (b & Qt::LeftButton)
    {
        beta += -(mouse_y - me->y());
        alpha += (mouse_x - me->x());
        mouse_x = me->x();
        mouse_y = me->y();

        if (beta > 80) beta = 80;
        if (beta < -80) beta = -80;
        QVector3D pos(-cos(beta * 3.1415 / 360)*cos(alpha * 3.1415 / 360)*radius,
                    sin(beta * 3.1415 / 360)*radius,
                    cos(beta * 3.1415 / 360)*sin(alpha * 3.1415 / 360)*radius);
        camera->setPosition(pos);
    }
}

void MainWindow::mouseWheel(QWheelEvent *ev)
{

    if (ev->delta() > 0)
        radius -= 0.5;
    else
        radius += 0.5;

    if (radius < 4)
        radius = 4;

    if (radius > 30)
        radius = 30;

    QVector3D pos(-cos(beta * 3.1415 / 360)*cos(alpha * 3.1415 / 360)*radius,
                sin(beta * 3.1415 / 360)*radius,
                cos(beta * 3.1415 / 360)*sin(alpha * 3.1415 / 360)*radius);
    camera->setPosition(pos);
}

void MainWindow::CreateEntity()
{
    box = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QMesh *boxMesh = new Qt3DRender::QMesh(box);
    boxMesh->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/box.obj"));

    Qt3DRender::QTextureLoader *boxLoader = new Qt3DRender::QTextureLoader(box);
    boxLoader->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/boxMat.jpg"));

    Qt3DExtras::QDiffuseSpecularMapMaterial *boxMat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    boxMat->setDiffuse(boxLoader);
    boxMat->setShininess(1.2);
    boxMat->setAmbient(QColor::fromRgb(255, 255, 255));
    boxMat->setSpecular(boxLoader);

    box->addComponent(boxMesh);
    box->addComponent(boxMat);


    stand = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QMesh *standMesh = new Qt3DRender::QMesh(stand);
    standMesh->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/stand.obj"));

    Qt3DRender::QTextureLoader *standLoader = new Qt3DRender::QTextureLoader(stand);
    standLoader->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/standMat.png"));

    Qt3DExtras::QDiffuseSpecularMapMaterial *standMat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    standMat->setDiffuse(standLoader);
    standMat->setShininess(2);
    standMat->setAmbient(QColor::fromRgb(255, 255, 255));
    standMat->setSpecular(standLoader);

    stand->addComponent(standMesh);
    stand->addComponent(standMat);



    disk = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QMesh *diskMesh = new Qt3DRender::QMesh(disk);
    diskMesh->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/disk.obj"));

    Qt3DRender::QTextureLoader *diskLoader = new Qt3DRender::QTextureLoader(disk);
    diskLoader->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/diskMat.png"));

    Qt3DExtras::QDiffuseSpecularMapMaterial *diskMat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    diskMat->setDiffuse(diskLoader);
    diskMat->setShininess(5);
    diskMat->setAmbient(QColor::fromRgb(255, 255, 255));
    diskMat->setSpecular(diskLoader);

    disk->addComponent(diskMesh);
    disk->addComponent(diskMat);



    axis = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QMesh *axisMesh = new Qt3DRender::QMesh(axis);
    axisMesh->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/axis.obj"));

    Qt3DRender::QTextureLoader *axisLoader = new Qt3DRender::QTextureLoader(axis);
    axisLoader->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/axisMat.png"));

    Qt3DExtras::QDiffuseSpecularMapMaterial *axisMat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    axisMat->setDiffuse(axisLoader);
    axisMat->setShininess(2);
    axisMat->setAmbient(QColor::fromRgb(255, 255, 255));
    axisMat->setSpecular(axisLoader);

    axis->addComponent(axisMesh);
    axis->addComponent(axisMat);



    load1 = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QMesh *load1Mesh = new Qt3DRender::QMesh(load1);
    load1Mesh->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/load1.obj"));

    Qt3DRender::QTextureLoader *load1Loader = new Qt3DRender::QTextureLoader(load1);
    load1Loader->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/load1Mat.png"));

    Qt3DExtras::QDiffuseSpecularMapMaterial *load1Mat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    load1Mat->setDiffuse(load1Loader);
    load1Mat->setShininess(5);
    load1Mat->setAmbient(QColor::fromRgb(255, 255, 255));
    load1Mat->setSpecular(load1Loader);

    load1->addComponent(load1Mesh);
    load1->addComponent(load1Mat);



    load2 = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QMesh *load2Mesh = new Qt3DRender::QMesh(load2);
    load2Mesh->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/load2.obj"));

    Qt3DRender::QTextureLoader *load2Loader = new Qt3DRender::QTextureLoader(load2);
    load2Loader->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/load1Mat.png"));

    Qt3DExtras::QDiffuseSpecularMapMaterial *load2Mat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    load2Mat->setDiffuse(load2Loader);
    load2Mat->setShininess(5);
    load2Mat->setAmbient(QColor::fromRgb(255, 255, 255));
    load2Mat->setSpecular(load2Loader);

    load2->addComponent(load2Mesh);
    load2->addComponent(load2Mat);



    load3 = new Qt3DCore::QEntity(sceneEntity);

    Qt3DRender::QMesh *load3Mesh = new Qt3DRender::QMesh(load3);
    load3Mesh->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/load3.obj"));

    Qt3DRender::QTextureLoader *load3Loader = new Qt3DRender::QTextureLoader(load3);
    load3Loader->setSource(QUrl::fromLocalFile("D:/QtProjects/project/Res/load1Mat.png"));

    Qt3DExtras::QDiffuseSpecularMapMaterial *load3Mat = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    load3Mat->setDiffuse(load3Loader);
    load3Mat->setShininess(5);
    load3Mat->setAmbient(QColor::fromRgb(255, 255, 255));
    load3Mat->setSpecular(load3Loader);

    load3->addComponent(load3Mesh);
    load3->addComponent(load3Mat);

    t = new Qt3DCore::QTransform();
    t1 = new Qt3DCore::QTransform();

    disk->addComponent(t1);
    axis->addComponent(t);
    box->addComponent(t);
    load1->addComponent(t);
    load2->addComponent(t);
    load3->addComponent(t);
}

void MainWindow::Update()
{
    angle += 0.1;
    angle1 += 5;
    t->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0, 1.0, 0.0), angle));
    t1->setRotation(QQuaternion::fromAxisAndAngle(QVector3D(0.0, 1.0, 0.0), angle) * QQuaternion::fromAxisAndAngle(QVector3D(0.0, 0.0, 1.0), angle1));
}
