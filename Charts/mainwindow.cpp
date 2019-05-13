#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plot.h"
#include "gyroscope.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sceneWindow = new Qt3DExtras::Qt3DWindow();
    ev = new MouseEv(this);

    sceneWindow->defaultFrameGraph()->setClearColor(QColor(QRgb(0x3c0b77)));
    sceneWindow->installEventFilter(ev);

    scene = QWidget::createWindowContainer(sceneWindow, ui->scene);
    scene->setGeometry(0, 0, 600, 600);
    sceneEntity = new Qt3DCore::QEntity();
    sceneWindow->setRootEntity(sceneEntity);

    camera = sceneWindow->camera();
    camera->lens()->setPerspectiveProjection(45.0, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(-radius, 0.0, 0.0));
    camera->setUpVector(QVector3D(0, 1, 0));
    camera->setViewCenter(QVector3D(0.0, 0.0, 0.0));

    gyro = new Gyroscope(this,
                         ui->mass->value() * 0.1,
                         ui->radius->value() * 0.01,
                         ui->length->value() * 0.01,
                         ui->psi_dot->value(),
                         ui->phi_dot->value() * 0.1,
                         ui->theta->value() * 0.001);

    ui->mass_value->setNum(ui->mass->value() * 0.1);
    ui->radius_value->setNum(ui->radius->value() * 0.01);
    ui->length_value->setNum(ui->length->value() * 0.01);
    ui->phi_dot_value->setNum(ui->phi_dot->value() * 0.1);
    ui->psi_dot_value->setNum(ui->psi_dot->value());
    ui->theta_value->setNum(ui->theta->value() * 0.001);

    minTheta = maxTheta = gyro->GetTheta();
    timer = new QTimer();
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));

    elapsedTimer = new QElapsedTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
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

        beta -= (mouse_y - me->y());
        alpha -= (mouse_x - me->x());
        mouse_x = me->x();
        mouse_y = me->y();

        if (beta > 80) beta = 80;
        if (beta < -80) beta = -80;
        QVector3D pos(cos(beta * 3.1415 / 180)*cos(alpha * 3.1415 / 180)*radius,
                      sin(beta * 3.1415 / 180)*radius,
                      cos(beta * 3.1415 / 180)*sin(alpha * 3.1415 / 180)*radius);
        camera->setPosition(pos);
   }
}

void MainWindow::mouseWheel(QWheelEvent *ev)
{
    if (ev->delta() > 0)
        radius -= 0.3;
    else
        radius += 0.3;

    if (radius < 2)
        radius = 2;

    if (radius > 20)
        radius = 20;

        QVector3D pos(cos(beta * 3.1415 / 180)*cos(alpha * 3.1415 / 180)*radius,
                    sin(beta * 3.1415 / 180)*radius,
                    cos(beta * 3.1415 / 180)*sin(alpha * 3.1415 / 180)*radius);

        camera->setPosition(pos);
}

void MainWindow::on_comboBox_activated(int index)
{
    plotID = index;
}

void MainWindow::on_Draw_clicked()
{
    Plot *plot = nullptr;
    switch(plotID)
    {
        case 0:
            plot = new Plot([this]()->double{ return gyro->GetPhi(); },
                            [this]()->double{ return gyro->GetTheta(); },
                            this);
        break;

        case 1:
        plot = new Plot([this]()->double{ return gyro->GetTime(); },
                        [this]()->double{ return gyro->GetTheta(); },
                        this);
        break;
    }

    if (plot)
    {
        plot->show();
        plots.append(plot);
    }
}

void MainWindow::Update()
{
    double dt = elapsedTimer->elapsed() * 0.001;

    int i = 0;
    while (i * 0.0001 < dt / 4)
    {
        gyro->Update(0.0001);
        i++;
    }

    for (auto plot : plots)
        plot->Update();

    elapsedTimer->restart();

    ui->mintheta->setNum(i);
    ui->maxtheta->setNum(dt);
}

void MainWindow::DeletePlot(Plot *plot)
{
    auto iter = std::find(plots.begin(), plots.end(), plot);

    if (iter != plots.end())
        plots.erase(iter);
}

Qt3DCore::QEntity* MainWindow::addObject(QString obj, QString texture)
{
    Qt3DCore::QEntity *entity = new Qt3DCore::QEntity(sceneEntity);
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
    mesh->setSource(QUrl::fromLocalFile(obj));

    Qt3DRender::QTextureLoader *texLoader = new Qt3DRender::QTextureLoader();
    texLoader->setSource(QUrl::fromLocalFile(texture));

    Qt3DExtras::QDiffuseSpecularMapMaterial *material = new Qt3DExtras::QDiffuseSpecularMapMaterial();
    material->setDiffuse(texLoader);
    material->setShininess(8.2f);
    material->setAmbient(QColor::fromRgb(255, 255, 255));
    material->setSpecular(texLoader);
    entity->addComponent(mesh);
    entity->addComponent(material);
    return entity;
}

void MainWindow::on_length_valueChanged(int value)
{
    gyro->SetLength(value * 0.01);
    ui->length_value->setNum(value * 0.01);
}

void MainWindow::on_mass_valueChanged(int value)
{
    gyro->SetMass(value * 0.1);
    ui->mass_value->setNum(value * 0.1);
}

void MainWindow::on_radius_valueChanged(int value)
{
    gyro->SetRadius(value * 0.01);
    ui->radius_value->setNum(value * 0.01);
}

void MainWindow::on_psi_dot_valueChanged(int value)
{
    gyro->SetPsiDot(value);
    ui->psi_dot_value->setNum(value);
}

void MainWindow::on_phi_dot_valueChanged(int value)
{
    gyro->SetPhiDot(value * 0.1);
    ui->phi_dot_value->setNum(value * 0.1);
}

void MainWindow::on_theta_valueChanged(int value)
{
    gyro->SetTheta(value * 0.001);
    ui->theta_value->setNum(value * 0.001);
}

void MainWindow::on_start_clicked()
{
    gyro->SetMass(ui->mass->value() * 0.1);
    gyro->SetTheta(ui->theta->value() * 0.001);
    gyro->SetLength(ui->length->value() * 0.01);
    gyro->SetPhiDot(-ui->phi_dot->value() * 0.1);
    gyro->SetPsiDot(ui->psi_dot->value());
    gyro->SetRadius(ui->radius->value() * 0.01);
    gyro->SetPhi(0);
    gyro->SetPsi(0);
    gyro->SetThetaDot(0);

    minTheta = maxTheta = gyro->GetTheta();
    timer->start();
    elapsedTimer->restart();
    for (auto plot : plots)
        plot->Restart();
}

void MainWindow::on_stop_clicked()
{
    timer->stop();
}

