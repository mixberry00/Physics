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

QVBoxLayout *sRect ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    addLabel(Lay, "<center><big><b>Главная справка</b></big></center>");
    addImage(Lay, ":/Res/1.jpg");
    return Lay;
}

QVBoxLayout *sRect1 ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    addLabel(Lay, "<center><big><b>Торсионный маятник</b></big></center>");
    addLabel(Lay, "<big><b>Физическая и математическая составляющие проекта</b></big>");
    addLabel(Lay, "«Торсионный маятник» - это механическая система, представляющая собой стержень на каждом конце которого закреплены грузики. "
                  "Стержень по центру закреплён на штифте. Стержень обладает лишь одной степенью свободы: "
                  "вращением вокруг оси при выведении из состояния равновесия за счёт возникновения возвращающего крутящего момента. ");
    addImage(Lay, ":/Sup/Math1/2.jpg");
    addLabel(Lay, "Движение маятника описывается основным уравнением динамики вращательного движения.");
    addImage(Lay, ":/Sup/Math3/2.png");
    addLabel(Lay, "Уравнение движения для угла отклонения φ свободно колеблющегося крутильного маятника, записывается следующим образом:");
    addImage(Lay, ":/Sup/Math1/1.jpg", true);
    return Lay;
}

QVBoxLayout *sRect3 ()
{
    QVBoxLayout *Lay = new QVBoxLayout();
    addLabel(Lay, "<center><big><b>Колебания жесткого математического маятника с большими амплитудами</b></big></center>");
    addLabel(Lay, "<big><b>Физическая и математическая составляющие проекта</b></big>");
    addLabel(Lay, "Математический маятник — модель осциллятора, представляющая собой механическую систему, состоящую из материальной "
                  "точки на конце невесомого стержня и "
                  "находящуюся в однородном поле сил тяготения. \n\n В данном проекте реализуется модель математического маятника без учета силы трения в точке подвеса. "
                  "Данная модель позволяет моделировать колебания при любых (в том числе достаточно больших) углах отклонения от положения равновесия. ");
    addImage(Lay, ":/Sup/Math3/1.png");
    addLabel(Lay, "Движение маятника описывается основным уравнением динамики вращательного движения.");
    addImage(Lay, ":/Sup/Math3/2.png");
    addLabel(Lay, "На маятник действует момент силы:");
    addImage(Lay, ":/Sup/Math3/3.png");
    addLabel(Lay, "В проекции на Ох:");
    addImage(Lay, ":/Sup/Math3/4.png");
    addLabel(Lay, "(Момент силы М равен произведению составляющей силы тяжести F<sub>2</sub> на плечо ℓ)");
    addImage(Lay, ":/Sup/Math3/5.png");
    addLabel(Lay, "После подстановки значений формула имеет вид:");
    addImage(Lay, ":/Sup/Math3/6.png");
    addLabel(Lay, "Дифференциальное уравнение колебаний математического маятника без трения:");
    addImage(Lay, ":/Sup/Math3/7.png");
    addLabel(Lay, "Чтобы сделать модель маятника более точной и приближенной к реальным условиям, было учтено сопротивление среды. "
                  "В этом случае так же принимается во внимание размеры шарика, ранее рассматриваемого только в качестве материальной точки.");
    addImage(Lay, ":/Sup/Math3/8.png", true);
    addLabel(Lay, "Вектор силы сопротивления коллинеарен тангенциальной составляющей вектора скорости и ускорения движения маятника, при этом противоположен вектору скорости.");
    addLabel(Lay, "Величина силы сопротивления пропорциональна характерной площади S (для шара – площади поперечного сечения), плотности среды ρ и квадрату скорости V:");
    addImage(Lay, ":/Sup/Math3/9.png");
    addLabel(Lay, "C<sub>x</sub>— безразмерный аэродинамический коэффициент сопротивления, приблизительно равный 0.3 для шара");
    addLabel(Lay, "(https://ru.wikipedia.org/wiki/Лобовое_сопротивление)");
    addImage(Lay, ":/Sup/Math3/10.png");
    addLabel(Lay, "Тогда дифференциальное уравнение имеет вид:");
    addImage(Lay, ":/Sup/Math3/11.png");
    return Lay;
}
