#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>
#include "plot.h"
#include "gyroscope.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mouseMove(QMouseEvent *);
    void mousePress(QMouseEvent *);
    void mouseWheel(QWheelEvent *);

    void DeletePlot(Plot *);

    Qt3DCore::QEntity* addObject(QString obj, QString texture);

private slots:
    void Update();
    void on_Draw_clicked();
    void on_comboBox_activated(int index);
    void on_length_valueChanged(int value);
    void on_radius_valueChanged(int value);
    void on_psi_dot_valueChanged(int value);
    void on_phi_dot_valueChanged(int value);
    void on_theta_valueChanged(int value);
    void on_stop_clicked();
    void on_start_clicked();

    void on_mass_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    QList<Plot *> plots;
    int plotID = 0;

    Gyroscope *gyro;

    QTimer *timer;  
    QElapsedTimer *elapsedTimer;

    double minTheta;
    double maxTheta;

    QWidget *scene;

    Qt3DExtras::Qt3DWindow *sceneWindow;
    Qt3DCore::QEntity *sceneEntity;
    Qt3DRender::QCamera *camera;
    class MouseEv *ev;

    int mouse_x, mouse_y;
    double alpha = 180.0, beta = 0.0;
    float radius = 10.0f;
};

class MouseEv : public QObject
{
    Q_OBJECT

public:
    MouseEv(MainWindow *window) : window(window)
    {}

private:
    MainWindow *window;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override
    {
        if (event->type() == QEvent::MouseMove)
        {
            window->mouseMove((QMouseEvent*)event);
            return true;
        }

        if (event->type() == QEvent::MouseButtonPress)
        {
            window->mousePress((QMouseEvent*)event);
            return true;
        }

        if (event->type() == QEvent::Wheel)
        {
            window->mouseWheel((QWheelEvent *)event);
        }
    }
};

#endif
