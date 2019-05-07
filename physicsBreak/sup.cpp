#include "help.h"

QVBoxLayout *sRect ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    QLabel* lab1 = new QLabel("Авторы: Такие-то такие-то бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла "
                              "бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла "
                              "бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла бла "
                              "бла бла бла бла бла бла бла бла бла бла бла");
    lab1->setWordWrap(true);
    QPixmap im1(":/Res/1.jpg");
    QLabel* lab2 = new QLabel();
    lab2->setPixmap(im1);


    Lay->addWidget(lab1);



    return Lay;
}
