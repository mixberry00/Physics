#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <QtCore>

class Gyroscope
{
public:
    Gyroscope();

    double GetArg() { return arg; }
    double GetValue1() { return value1; }
    double GetValue2() { return value2; }
    double GetValue3() { return value3; }

    void Update();

private:
    double arg;
    double value1;
    double value2;
    double value3;
};

#endif // GYROSCOPE_H
