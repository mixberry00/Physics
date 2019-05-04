#include "gyroscope.h"

Gyroscope::Gyroscope()
{
    arg = 0;
    value1 = 0;
    value2 = 1;
    value3 = -2;
}

void Gyroscope::Update()
{
    arg += 0.05;
    value1 = 4 * sin(arg);
    value2 = 4 * exp(-arg * 0.01) * cos(arg + 5);
    value3 = 4 * sin(arg) * sin(arg);
}
