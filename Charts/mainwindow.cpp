#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plot.h"
#include "gyroscope.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gyro = new Gyroscope();

    timer = new QTimer();
    timer->setInterval(16);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Plot *plot = nullptr;
    switch(plotID)
    {
        case 0:
            plot = new Plot([this]()->double{ return gyro->GetArg(); },
                            [this]()->double{ return gyro->GetValue1(); },
                            this);
        break;

        case 1:
        plot = new Plot([this]()->double{ return gyro->GetArg(); },
                        [this]()->double{ return gyro->GetValue2(); },
                        this);
        break;

        case 2:
            plot = new Plot([this]()->double{ return gyro->GetArg(); },
                            [this]()->double{ return gyro->GetValue3(); },
                            this);
        break;
    }


    if (plot)
    {
        plot->show();
        plots.append(plot);
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    plotID = index;
}


void MainWindow::Update()
{
    gyro->Update();
    for (auto plot : plots)
        plot->Update();
}

void MainWindow::DeletePlot(Plot *plot)
{
    auto iter = std::find(plots.begin(), plots.end(), plot);

    if (iter != plots.end())
        plots.erase(iter);
}
