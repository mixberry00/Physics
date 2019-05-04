#include "plot.h"
#include "ui_plot.h"
#include "mainwindow.h"

Plot::Plot(std::function<double()> getarg, std::function<double()> getvalue, MainWindow *parent, QWidget *p) :
    QMainWindow(p),
    ui(new Ui::Plot),
    parent(parent),
    getarg(getarg),
    getvalue(getvalue)
{
    ui->setupUi(this);
    plot = ui->PlotSurface;

    plot->addGraph();
    plot->yAxis->setRange(-5, 5);
}


void Plot::resizeEvent(QResizeEvent *re)
{
    ui->PlotSurface->setGeometry(0, 0, re->size().width(), re->size().height() * 0.75);
}

void Plot::closeEvent(QCloseEvent *)
{
    delete ui;
    parent->DeletePlot(this);
}

void Plot::Update()
{
    double arg = getarg();
    double value = getvalue();

    args.append(arg);
    values.append(value);

    if (args.size() >= 5000)
    {
        args.removeAt(0);
        values.removeAt(0);
    }

    Draw(args.toVector(), values.toVector());
}

void Plot::Draw(QVector<double> args, QVector<double> values)
{
    plot->graph(0)->setData(args, values);
    plot->xAxis->setRange(args.last() - 5, args.last() + 1);
    plot->replot();
}

