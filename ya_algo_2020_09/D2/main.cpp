// https://contest.yandex.ru/contest/19811/problems/D/

#include <iostream>

long long combine(long long& n, long long d) {
    long long tmp = d - 1;
    while(true) {
        n /= d;
        if (n % d != 0) {
            return tmp;
        }
        tmp *= d;
    }
}

long long primeFactors(long long n) {
    long long res = 1;
    if (n % 2 == 0) {
        res *= combine(n, 2);
    }
    for (long long i = 3; i * i <= n; i += 2) {
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
// res = (p1-1)*p1^(a1-1)*...*(pk-1)*pk^(ak-1);
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
