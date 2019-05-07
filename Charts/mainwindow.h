#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plot.h"
#include <vector>
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

    void DeletePlot(Plot *);

private slots:
    void Update();
    void on_Draw_clicked();
    void on_comboBox_activated(int index);
    void on_length_valueChanged(int value);
    void on_mass_valueChanged(int value);
    void on_radius_valueChanged(int value);
    void on_psi_dot_valueChanged(int value);
    void on_phi_dot_valueChanged(int value);
    void on_theta_valueChanged(int value);
    void on_stop_clicked();
    void on_start_clicked();

private:
    Ui::MainWindow *ui;

    QList<Plot *> plots;
    int plotID = 0;

    Gyroscope *gyro;

    QTimer *timer;  
    QElapsedTimer *elapsedTimer;


    double minTheta;
    double maxTheta;
};

#endif
