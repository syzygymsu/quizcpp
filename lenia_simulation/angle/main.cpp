#include <cmath>
#include <algorithm>
class Device {
public:
    Device(double acc, double dec, double top)
        : acc(acc), dec(dec), top(top)
    {}

    // Возвращает время (с), за которое осуществляется 
    // перенацеливание на заданный угол (°)
    double time(double angle) const;

    // Возвращает угол (°), на которой осуществляется 
    // перенацеливание за заданное время (с)
    double angle(double time) const;

private:
    double acc; // Ускорение, °/с²
    double dec; // Торможение, °/с²
    double top; // Максимальная скорость, °/с
};

double Device::time(double angle) const {
    double critical = 2 * angle * acc * dec / (acc + dec);
    if (critical <= top * top) {
        return sqrt(critical) * (1. / acc + 1. / dec);
    }
    return angle / top + top / 2 * (1. / acc + 1. / dec);
}

double Device::angle(double time) const {
    double critical = top * (1. / acc + 1. / dec);
    if (critical <= time) {
        return std::min(acc * dec * time * time / (acc + dec), 180.);
    }
    return std::min(top * (time + critical / 2.), 180.);
}


#include <iostream>
using namespace std;

int main()
{
    Device d(5, 3, 20);
    cout << d.time(30) << std::endl;
    cout << d.angle(1) << std::endl;
    return 0;
}

