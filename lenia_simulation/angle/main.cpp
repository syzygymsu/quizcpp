#include <cmath>
#include <algorithm>
#include <iostream>

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
    if (critical < top * top) {
        return sqrt(critical) * (1. / acc + 1. / dec);
    }
    return angle / top + top * (1. / acc + 1. / dec) / 2.;
}

double Device::angle(double time) const {
    double critical = top * (1. / acc + 1. / dec);
    if (critical > time) {
        double res = acc * dec * time * time / (acc + dec) / 2.;
        return res;
    }
    double res =  top * (time - critical / 2.);
    return res;
}


using namespace std;

int TEST_NUM = 1;

void expect_eq(double ac, double ex) {
    const double abs = std::abs(ac - ex);
    const double sum = std::abs(ex + ac);
    const double rel = sum > 0 ? std::abs(ac - ex) / std::abs(ex + ac) : abs;
    std::cout << "TEST #" << TEST_NUM++ << "\t";
    if (rel < 1e-12) {
        std::cout << "PASSED";
    }
    else {
        std::cout << " | rel: " << rel << ", abs: " << abs << " " << ac << " " << ex << "\n";
        std::cout << "NOT PASSED";
    }
    std::cout << std::endl;
    

}

void test_case_invariant(const Device& d, double time, double angle) {
    expect_eq(d.time(d.angle(time)), time);
    expect_eq(d.angle(d.time(angle)), angle);
}

void test_case_sym() {
    Device d(10, 10, 10);
    expect_eq(d.angle(0.0), 0.0);
    expect_eq(d.angle(1.0), 2.5);
    expect_eq(d.angle(2.0), 10.0);
    expect_eq(d.angle(3.0), 20.0);
    expect_eq(d.angle(4.0), 30.0);
}

void test_case_asym() {
    Device d1(1, 2, 10);
    expect_eq(d1.angle(0.0), 0.0);
    expect_eq(d1.angle(3.0), 3.0);

    Device d2(1, 0.5, 10);
    expect_eq(d2.angle(3.0), 1.5);
}

void run_tests() {
    Device d(10, 10, 10);
    const int n = 20;
    const double angle_step = 180.0 / n;
    const double time_step = 3600.0 / n;
    test_case_invariant(d, time_step, angle_step);
    for (int i = 0; i < n; ++i) {
        test_case_invariant(d, i * time_step, i * angle_step);
    }
    test_case_sym();
    test_case_asym();
}

int main()
{
    Device d(5, 3, 20);
    cout << d.time(30) << std::endl;
    cout << d.angle(5) << std::endl;
    run_tests();
    return 0;
}

