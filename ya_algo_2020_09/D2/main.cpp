// https://contest.yandex.ru/contest/19811/problems/D/

#include <iostream>

long long combine(long long& n, long long d) {
    long long tmp = 1;
    do
    {
        tmp *= d;
        n = n / d;
    } while (n % d == 0);
    tmp /= d;
    return tmp * (d - 1);
}

long long primeFactors(long long n) {
    long long res = 1;
    if (n % 2 == 0) {
        res *= combine(n, 2);
    }
    for (long long i = 3; i * i <= n; i = i + 2) {
        if (n % i == 0) {
            res *= combine(n, i);
        }
    }
    if (n > 1) {
        return (n - 1) * res;
    }
    return res;
}

// n = p1^a1*p2^a2*...pk^ak;
// res = fast(p1)*p1^(a1-1)+... + fast(pk)*pk^(ak-1);
long long fast(long long n) {
    if (n == 1) {
        return 2;
    }
    return primeFactors(n);
}

int main() {
    long long n;
    std::cin >> n;
    std::cout << fast(n) << std::endl;
    return 0;
}
