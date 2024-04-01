// https://contest.yandex.ru/contest/19811/problems/D/

#include <iostream>
#include <cmath>

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

long long primeFactors(long long& n, long long limit) {
    long long res = 1;
    if (n % 2 == 0) {
        res *= combine(n, 2);
    }

    for (int i = 3; i <= limit; i = i + 2) {
        if (n % i == 0) {
            res *= combine(n, i);
        }
    }
    return res;
}

// n = p1^a1*p2^a2*...pk^ak;
// res = fast(p1)*p1^(a1-1)+... + fast(pk)*pk^(ak-1);
long long fast(long long n) {
    if (n == 1) {
        return 2;
    }
    long long limit = (long long)std::sqrt(n) + 1;
    long long res = primeFactors(n, limit);
    if (n < limit) {
        return res;
    }
    return res * (n - 1);
}

int main() {
    long long n;
    std::cin >> n;
    std::cout << fast(n) << std::endl;
    return 0;
}
