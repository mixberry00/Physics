#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->w->setGeometry(0, 0, width() * 0.75, height());

    sceneWindow = new Qt3DExtras::Qt3DWindow();


    ev = new MouseEv(this);
    sceneWindow->defaultFrameGraph()->setClearColor(QColor(QRgb(0x888888)));
    sceneWindow->installEventFilter(ev);

    scene = QWidget::createWindowContainer(sceneWindow, ui->dvid);
    scene->setGeometry(ui->dvid->geometry());
    sceneEntity = new Qt3DCore::QEntity();
    sceneEntityRoom = new Qt3DCore::QEntity();
    sceneWindow->setRootEntity(sceneEntity);

    uprend = new QTimer();
    uprend->setInterval(100);
    connect(uprend, SIGNAL(timeout()), this, SLOT(Repaint()));



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
    light->setIntensity(0.6f);
    light->setLinearAttenuation(0.1f);
    lightEntity->addComponent(light);
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(lightEntity);
    lightTransform->setTranslation(QVector3D(10.0, 10.0, 0.0));
    lightEntity->addComponent(lightTransform);

    camera = sceneWindow->camera();
    camera->lens()->setPerspectiveProjection(100.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(20.0, 3.0, 0.0));
    camera->setUpVector(QVector3D(0, 1, 0));
    camera->setViewCenter(QVector3D(19.0, 3.0, 0.0));

    timer2 = new QTimer();
    timer2->setInterval(2);
    connect(timer2, SIGNAL(timeout()), this, SLOT(moveToRoom()));


    timer = new QTimer();
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));

    hwind = new help();
    hwind->setAttribute(Qt::WA_ShowModal);

    lTime = new QLabel();


    ui->startBut->setHidden(true);

    CreateEntity();
    initModels();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initModels()
{
    m1 = new Model1();
    m2 = new Model2();
}

Qt3DRender::QCamera * MainWindow::getCamera()
{
    return camera;
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    scene->setGeometry(ui->dvid->geometry());
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
        if (curC==-2)
        {
            beta += -(mouse_y - me->y()) * (PI / 360.);
            alpha += (mouse_x - me->x()) * (PI / 360.);
            mouse_x = me->x();
            mouse_y = me->y();


            if (beta > 80) beta = 80;
            if (beta < -80) beta = -80;
            QVector3D pos(-float(cos(beta)*cos(alpha))*radius,
                        float(sin(beta))*radius,
                        float(cos(beta)*sin(alpha))*radius);
            camera->setPosition(pos);
        }
        else
        {
            camera->tilt((mouse_y - me->y()) * 0.1f);
            camera->pan(-(mouse_x - me->x()) * 0.1f);
            camera->setUpVector(QVector3D(0, 1, 0));
            mouse_y = me->y();
            mouse_x = me->x();
        }
   }
}

void MainWindow::mouseWheel(QWheelEvent *ev)
{
    if (curC == -2)
    {
        if (ev->delta() > 0)
            radius -= 0.1f;
        else
            radius += 0.1f;

        if (radius < 2)
            radius = 2.f;

        if (radius > 6)
            radius = 6.f;

        QVector3D pos(-float(cos(beta)*cos(alpha))*radius,
                    float(sin(beta))*radius,
                    float(cos(beta)*sin(alpha))*radius);
        camera->setPosition(pos);
    }
}

void MainWindow::CreateEntity()
{
    addObject(sceneEntity, ":/Res/Corridor.obj", ":/Res/Corridor.png");
    addObject(sceneEntity, ":/Res/ceiling.obj", ":/Res/ceiling.jpg");
}

void MainWindow::Update()
{
    m->Update(0.05);
    time += 1;
    lTime->setText(QString("Время: %1:%2:%3").arg(time / 100 / 60, 2, 10,
                                                  QLatin1Char('0')).arg(time / 100 % 60, 2, 10,
                                                                        QLatin1Char('0')).arg(time % 100, 2, 10, QLatin1Char('0')));
}

void MainWindow::Repaint()
{
    camera->pan(1.0f);
    camera->pan(-1.0f);
    uprend->stop();
}

void MainWindow::on_room1_clicked()
{
    curC = 0;
    cameraMoveTo();
}

void MainWindow::on_room2_clicked()
{
    curC = 1;
    cameraMoveTo();
}

void MainWindow::on_room3_clicked()
{
    curC = 2;
    cameraMoveTo();
}

void MainWindow::on_room4_clicked()
{
    curC = 3;
    cameraMoveTo();
}

void MainWindow::on_room5_clicked()
{
    curC = 4;
    cameraMoveTo();
}

void MainWindow::on_room6_clicked()
{
    curC = 5;
    cameraMoveTo();
}

void MainWindow::on_room7_clicked()
{
    curC = 6;
    cameraMoveTo();
}

void MainWindow::on_pushButton_clicked()
{
    if (curC == -1)
        qDebug()<< "Error!";
    else if (curC != -2)
    {
        beta = 0.0;
        alpha = PI / 2.;
        time = 0;
        lTime->setText("Время: 00:00:00");


        switch (curC)
        {
        case 0:
            m = m1;
            break;
        case 1:
            m = m2;
            break;

        default:
            m = m1;
        }

        sceneWindow->setRootEntity(m->GetEntity());
        QVBoxLayout *l = m->GetInf();
        l->addWidget(lTime);
        ui->status->setLayout(l);
        ui->setup->setLayout(m->GetSet());
        timer2->stop();
        ui->pushButton->setText("Выход из комнаты");
        ui->numbers->setHidden(true);
        ui->startBut->setVisible(true);
        ui->status->setVisible(true);
        ui->setup->setVisible(true);

        curC = -2;

        camera->setFieldOfView(60.0f);
        QVector3D pos(-float(cos(beta)*cos(alpha))*radius,
                    float(sin(beta))*radius,
                    float(cos(beta)*sin(alpha))*radius);
        camera->setPosition(pos);
        camera->setViewCenter(QVector3D(0.0, 0.0, 0.0));
        uprend->start();
    }
    else
    {
        sceneWindow->setRootEntity(sceneEntity);
        camera->setFieldOfView(100.0f);
        camera->setPosition(QVector3D(20.0, 3.0, 0.0));
        camera->setViewCenter(QVector3D(19.0, 3.0, 0.0));
        ui->numbers->setVisible(true);
        curC = -1;
        ui->pushButton->setText("Перейти в комнату");
        ui->startBut->setVisible(false);
        ui->status->setHidden(true);
        ui->setup->setHidden(true);

        timer->stop();        
        uprend->start();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    hwind->updspr(1);
    hwind->show();
}

void MainWindow::on_startBut_clicked()
{
    //sections//
    if (!timer->isActive())
    {
        m->Init();
        time = 0;
        lTime->setText("Время: 00:00:00");
        ui->startBut->setText("Остановить");
        timer->start();
    }
    else
    {
        timer->stop();
        ui->startBut->setText("Запуск маятника");
    }
}

