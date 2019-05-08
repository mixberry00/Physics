#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
}

help::~help()
{
    delete ui;
}

void help::updspr(int c)
{    
    QVBoxLayout *l = sRect();


    l->addStretch();
    QWidget* widget = new QWidget;
    widget->setLayout(l);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    widget->setAutoFillBackground(true);
    widget->setPalette(Pal);

    ui->scrollArea->setWidget(widget);
}

void help::on_pushButton_clicked()
{
    this->close();

}


