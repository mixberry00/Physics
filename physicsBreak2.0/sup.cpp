#include "help.h"

QVBoxLayout *sRect ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    QLabel* lab1 = new QLabel("<center><big><b>Главная справка</b></big></center>");
    lab1->setWordWrap(true);
    QPixmap im1(":/Res/1.jpg");
    QLabel* lab2 = new QLabel();
    lab2->setPixmap(im1);


    Lay->addWidget(lab1);



    return Lay;
}

QVBoxLayout *sRect3 ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    QLabel* lab1 = new QLabel("<center><big><b>Колебания жесткого математического маятника с большими амплитудами</b></big></center>");
    QLabel* lab2 = new QLabel("<big><b>Физическая и математическая составляющие проекта</b></big>");
    QLabel* lab3 = new QLabel("Математический маятник — модель осциллятора, представляющая собой механическую систему, состоящую из материальной "
                              "точки на конце невесомого стержня и "
                              "находящуюся в однородном поле сил тяготения. \n\n В данном проекте реализуется модель математического маятника без учета силы трения в точке подвеса. "
                              "Данная модель позволяет моделировать колебания при любых (в том числе достаточно больших) углах отклонения от положения равновесия. ");
    QPixmap im1(":/Sup/Math3/1.png");
    QLabel* lab4 = new QLabel();
    lab4->setPixmap(im1);
    QLabel* lab5 = new QLabel("Движение маятника описывается основным уравнением динамики вращательного движения.");
    QPixmap im2(":/Sup/Math3/2.png");
    QLabel* lab6 = new QLabel();
    lab6->setPixmap(im2);
    QLabel* lab7 = new QLabel("На маятник действует момент силы:");
    QPixmap im3(":/Sup/Math3/3.png");
    QLabel* lab8 = new QLabel();
    lab8->setPixmap(im3);
    QLabel* lab9 = new QLabel("В проекции на Ох:");



    lab1->setWordWrap(true);
    lab2->setWordWrap(true);
    lab3->setWordWrap(true);
    lab5->setWordWrap(true);
    lab7->setWordWrap(true);
    lab9->setWordWrap(true);
    Lay->addWidget(lab1);
    Lay->addWidget(lab2);
    Lay->addWidget(lab3);
    Lay->addWidget(lab4);
    Lay->addWidget(lab5);
    Lay->addWidget(lab6);
    Lay->addWidget(lab7);
    Lay->addWidget(lab8);



    return Lay;
}
