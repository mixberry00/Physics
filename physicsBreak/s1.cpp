#include "help.h"

QVBoxLayout *s1Rect ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    QLabel* lab1 = new QLabel("Вот здесь текст");



    QPixmap im1(":/Res/1.jpg");
    QLabel* lab2 = new QLabel();
    lab2->setPixmap(im1);




    QLabel *lab3 = new QLabel("Ещё текст");

    QPixmap im4(":/Res/2.jpg");
    QLabel *lab4 = new QLabel();
    lab4->setPixmap(im4);
    Lay->addWidget(lab1);
    Lay->addWidget(lab2);
    Lay->addWidget(lab3);
    Lay->addWidget(lab4);


    return Lay;
}
