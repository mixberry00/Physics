#include "mainwindow.h"


const float coordR[]={-8.0, -5.0, 0.0, 3.0, 8.0, 11.0, 17.0};
const bool sideR[]={true, false, true, false, true, false, true};
float st, kx, kz;
bool flag = true;
QTimer *timer2 = new QTimer();

void MainWindow::cameraMoveTo()
{
    if (flag)
    {
        timer2->setInterval(2);
        connect(timer2, SIGNAL(timeout()), this, SLOT(moveToRoom()));
        flag = false;
    }

    float delta = camera->position().x() - coordR[curC];
    float fdeltz = camera->viewCenter().z() - 5.0f * (sideR[curC] ? 1.0f : -1.0f);
    float fdeltx = camera->viewCenter().x() - coordR[curC];
    if (delta < 0) st = 0.03f;
    else st = -0.03f;
    int stepR = int(delta / st);

    kz = fdeltz / float(stepR);
    kx = fdeltx / float(stepR);
    /*if (fdeltx < 0) kx = 0.05;
    else kx = -0.05;
    int stepR = int(fdeltx / kx);
    st = delta / float(stepR);
    kz = fdeltz / float(stepR);*/


    //camera->setViewCenter(QVector3D(coordR[s], 3.0, 5.0f * (sideR[c] ? 1.0f : -1.0f)));
    //k = delrot / stepR;
    timer2->stop();
    timer2->start();
}

void MainWindow::moveToRoom()
{
    static int steps = 0;
    ++steps;
    if (fabs(double(camera->position().x() - coordR[curC])) > 1e-1 && steps % 4 == 0)
    {
        camera->setPosition(QVector3D(camera->position().x() + st, camera->position().y(), camera->position().z()));
    }
    else if (fabs(double(camera->viewCenter().x() - coordR[curC])) > 1e-1)
    {
       camera->setViewCenter(QVector3D(camera->viewCenter().x() + kx, camera->position().y(), camera->viewCenter().z() + kz));
    }
    else if (fabs(double(camera->position().x() - coordR[curC])) <= 1e-1){
        timer2->stop();
        steps = 0;
    }


}
