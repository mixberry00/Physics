#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "plot.h"
#include "gyroscope.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gyro = new Gyroscope(0.1, 0.05, 0.15, 300, -0.5, 1.2);

    minTheta = maxTheta = gyro->GetTheta();
    timer = new QTimer();
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));

    elapsedTimer = new QElapsedTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
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

    for (int i = 0; i < 100; i++)
        gyro->Update(0.0001);

    for (auto plot : plots)
        plot->Update();

    elapsedTimer->restart();

    if (gyro->GetTheta() < minTheta)
        minTheta = gyro->GetTheta();

    if (gyro->GetTheta() > maxTheta)
        maxTheta = gyro->GetTheta();

    ui->mintheta->setNum(minTheta);
    ui->maxtheta->setNum(maxTheta);
}

void MainWindow::DeletePlot(Plot *plot)
{
    auto iter = std::find(plots.begin(), plots.end(), plot);

    if (iter != plots.end())
        plots.erase(iter);
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
    ui->Psi_dot_value->setNum(value);
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

