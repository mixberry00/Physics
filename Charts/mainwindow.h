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
    void on_pushButton_clicked();

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;

    QList<Plot *> plots;

    int plotID = 0;

    Gyroscope *gyro;

    QTimer *timer;

};

#endif // MAINWINDOW_H
