#include "help.h"
void addLabel(QVBoxLayout *L, QString s)
{
    QLabel* lab = new QLabel(s);
    lab->setWordWrap(true);
    QFont f("Times New Roman", 10);
    lab->setFont(f);
    L->addWidget(lab);
}
void addImage(QVBoxLayout *L, QString s, bool transform = false)
{
    QPixmap im(s);
    QLabel* lab = new QLabel();
    if (transform)
        lab->setScaledContents(true);
    lab->setPixmap(im);
    L->addWidget(lab);
}

void addLabel1(QHBoxLayout *L, QString s)
{
    QLabel* lab = new QLabel(s);
    QFont f("Times New Roman", 10);
    lab->setFont(f);
    lab->setWordWrap(true);
    lab->setAlignment(Qt::AlignLeft);
    lab->setAlignment(Qt::AlignVCenter);
    L->addWidget(lab,15);
}
void addImage1(QHBoxLayout *L, QString s, bool transform = false)
{
    QPixmap im(s);
    QLabel* lab = new QLabel();
    if (transform)
        lab->setScaledContents(true);
    lab->setPixmap(im);
    lab->setAlignment(Qt::AlignLeft);
    L->addWidget(lab,1);
}

QVBoxLayout *sRect ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    QHBoxLayout *Lay1 = new QHBoxLayout();
    addLabel(Lay, "<center><big><b>Маятник Галилея</b></big></center>");
    addLabel(Lay, "<big><b>Физическая и математическая составляющие проекта</b></big>");
    addLabel(Lay, "Маятник Галилея – математический маятник, у которого движение груза представимо в виде двух состояний – до и после прохождения «препятствия»."
                  "Препятствие представляет собой тонкий стержень, расположенный перпендикулярно движению нити.\n\n"
                  "До столкновения с препятствием система представляет собой обычный математический маятник, после – тот же маятник, но с измененными характеристиками, будем называть его «деформированный маятник».  "
                  "При этом максимальная высота поднятия груза до и после препятствия не отличается.\n\n"
                  "Математический маятник – это осциллятор, представляющий собой систему из груза массой m на конце нерастяжимой нити.\n\n"
                  "На рисунке представлены возможные траектории движения груза:\n\n");
    addImage(Lay, ":/Sup/Math/1.jpg");
    addLabel(Lay, "\n");
    addImage1(Lay1, ":/Sup/Math/2.1.jpg");
    addLabel1(Lay1, " - угол отклонения груза от положения равновесия\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/2.2.jpg");
    addLabel1(Lay1, " - длина нити\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/2.3.jpg");
    addLabel1(Lay1, " - максимальная высота поднятия груза \n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/2.4.jpg");
    addLabel1(Lay1, " - масса груза\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "Пусть h - высота препятствия, необходимо рассмотреть два случая:\n"
                  "1) |l - h| - очень маленькая величина, т.е. препятствие расположено близко"
                  " к креплению нити, тогда система будет из себя математический маятник, траектория движения груза:");
    addImage(Lay, ":/Sup/Math/3.jpg");
    addLabel(Lay, "2) Препятствие находится на высоте ");
    addImage(Lay, ":/Sup/Math/3.1.jpg");
    addLabel(Lay, "где:");
    addImage1(Lay1, ":/Sup/Math/2.3.jpg");
    addLabel1(Lay1, " - максимальная высота поднятия груза при движении без препятствия, траектория движения груза:");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage(Lay, ":/Sup/Math/4.jpg");
    addLabel(Lay, "Для вывода дифференциального уравнения колебания математического маятника"
                  " воспользуемся дифференциальным уравнением колебания физического маятника:");
    addImage(Lay,":/Sup/Math/5.jpg");
    addLabel(Lay, "где:");
    addImage1(Lay1, ":/Sup/Math/6.1.jpg");
    addLabel1(Lay1, " - ускорение свободного падения,\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/6.2.jpg");
    addLabel1(Lay1, " - длина нити,\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/6.3.jpg");
    addLabel1(Lay1, " - масса груза,\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/6.4.jpg");
    addLabel1(Lay1, " - момент инерции физического маятника\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "В этой формуле заменим момент инерции I на физического маятника на момент инерции материальной точки:\n");
    addImage(Lay, ":/Sup/Math/7.1.jpg");
    addImage1(Lay1, ":/Sup/Math/7.2.jpg");
    addLabel1(Lay1, "- расстояние от материальной точки до места крепления нити.\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "После подстановки получим дифференциальное уравнение колебания"
                  " математического маятника в виде (при малых отклонениях):");
    addImage(Lay,":/Sup/Math/8.jpg");
    addLabel(Lay, "Введем обозначение: ");
    addImage1(Lay1, ":/Sup/Math/9.jpg");
    addLabel1(Lay1, "-собственная частота колебаний математического маятника");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "Окончательный вид уравнения:");
    addImage(Lay,":/Sup/Math/10.jpg");
    addLabel(Lay, "Решение уравнения представимо в виде:");
    addImage(Lay,":/Sup/Math/11.jpg");
    addImage1(Lay1, ":/Sup/Math/12.1.jpg");
    addLabel1(Lay1, " - максимальное отклонение маятника от оложения равновесия, задается начальным условием");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/12.2.jpg");
    addLabel1(Lay1, " - начальная фаза колебаний");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "Циклическая частота математического маятника зависит только от длины его подвеса: ");
    addImage(Lay,":/Sup/Math/13.1.jpg");
    addImage1(Lay1, ":/Sup/Math/13.2.jpg");
    addLabel1(Lay1, " - гравитационная постоянная");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1, ":/Sup/Math/13.3.jpg");
    addLabel1(Lay1, " - длина нити;");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "Так как маятник Галилея представляет собой совокупность двух математических маятников"
                  " с разными характеристиками, то для вычисления собственной частоты до препятствия формула"
                  " останется без изменения, после препятствия длина нити меняется, соответственно формула примет вид:");
    addImage1(Lay1,":/Sup/Math/14.jpg");
    addImage1(Lay1,":/Sup/Math/14.3.jpg");
    addLabel1(Lay1,"- высота препятствия, или\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/14.1.jpg");
    addLabel1(Lay1,"где");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/14.2.jpg");
    addLabel1(Lay1,"- коэффициент сжатия.\n");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "Период колебаний для математического и деформированного маятников соответственно:");
    addImage(Lay,":/Sup/Math/15.jpg");
    addImage(Lay,":/Sup/Math/16.jpg");
    addLabel(Lay, "Полный период системы:");
    addImage(Lay,":/Sup/Math/17.jpg");
    addLabel(Lay, "Полный период системы:");
    addImage(Lay,":/Sup/Math/18.jpg");
    addLabel(Lay, "Для деформированного:");
    addImage(Lay,":/Sup/Math/19.jpg");
    addLabel(Lay, "Для деформированного:");
    addImage(Lay,":/Sup/Math/20.1.jpg");
    addImage1(Lay1,":/Sup/Math/20.2.jpg");
    addLabel1(Lay1,"- кинетическая энергия маятника");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/20.3.jpg");
    addLabel1(Lay1,"- потенциальная энергия маятника");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/20.4.jpg");
    addLabel1(Lay1," - скорость движения маятника");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/20.5.jpg");
    addLabel1(Lay1,"- линейное смещение груза маятника от положения равновесия по дуге окружности радиуса");
    addImage1(Lay1,":/Sup/Math/20.6.jpg");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/20.7.jpg");
    addLabel1(Lay1,"- масса груза");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addLabel(Lay, "Максимальное значение потенциальной энергии математического маятника равно:");
    addImage(Lay,":/Sup/Math/21.jpg");
    addLabel(Lay, "Максимальная величина кинетической энергии:");
    addImage(Lay,":/Sup/Math/22.jpg");
    addLabel(Lay, "где");
    addImage1(Lay1,":/Sup/Math/23.jpg");
    addLabel1(Lay1,"- максимальная высота поднятия груза, ");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/24.1.jpg");
    addLabel1(Lay1,"- максимальное отклонение маятника от положения равновесия, ");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    addImage1(Lay1,":/Sup/Math/24.2.jpg");
    addLabel1(Lay1,"- максимальная скорость.");
    Lay->addLayout(Lay1);
    Lay1 = new QHBoxLayout();
    return Lay;
}
