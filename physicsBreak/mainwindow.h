#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <Qt3DCore>

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void resizeEvent(QResizeEvent *) override;
    void mouseMove(QMouseEvent *);
    void mousePress(QMouseEvent *);
    void mouseWheel(QWheelEvent *);
    Qt3DRender::QCamera *getCamera();
    Qt3DCore::QEntity *addObject(Qt3DCore::QEntity *, QString, QString);
    void CreateEntity();

private slots:
    void Update();

    void Repaint();

    void on_room1_clicked();

    void on_room2_clicked();

    void on_room3_clicked();

    void on_room4_clicked();

    void on_room5_clicked();

    void on_room6_clicked();

    void on_room7_clicked();

    void moveToRoom();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QWidget *scene;

    Qt3DExtras::Qt3DWindow *sceneWindow;
    Qt3DCore::QEntity *sceneEntity;
    Qt3DCore::QEntity *sceneEntityRoom;
    Qt3DRender::QCamera *camera;
    Qt3DCore::QEntity *lightEntity;
    Qt3DRender::QDirectionalLight *light;

    int mouse_x, mouse_y;
    double alpha = 0, beta = 0;
    float radius = 5.0f;
    float angle = 0;
    float angle1 = 0;
    int curC = -1;

    class MouseEv *ev;

    QTimer *timer, *uprend, *timer2;


    /*Qt3DCore::QTransform *t;
    Qt3DCore::QTransform *t1;*/
    QMap <QString, Qt3DCore::QEntity *> objects;

    void cameraMoveTo();



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
