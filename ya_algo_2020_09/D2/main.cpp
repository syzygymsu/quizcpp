// https://contest.yandex.ru/contest/19811/problems/D/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <numeric>
#include <array>


long long mult(long long a, long long b, long long mod) {
    return (__int128)a * b % mod;
}

/*
long long mult(long long a, long long b, long long mod) {
    long long result = 0;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}
*/
long long f(long long x, long long c, long long mod) {
    return (mult(x, x, mod) + c) % mod;
}

long long rho(long long n, long long x0 = 2, long long c = 1) {
    long long x = x0;
    long long y = x0;
    long long g = 1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = std::gcd(abs(x - y), n);
    }
    return g;
}

long long brent(long long n, long long x0 = 2, long long c = 1) {
    long long x = x0;
    long long g = 1;
    long long q = 1;
    long long xs, y;

    int m = 128;
    int l = 1;
    while (g == 1) {
        y = x;
        for (int i = 1; i < l; i++)
            x = f(x, c, n);
        int k = 0;
        while (k < l && g == 1) {
            xs = x;
            for (int i = 0; i < m && i < l - k; i++) {
                x = f(x, c, n);
                q = mult(q, abs(y - x), n);
            }
            g = std::gcd(q, n);
            k += m;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            xs = f(xs, c, n);
            g = std::gcd(std::abs(xs - y), n);
        } while (g == 1);
    }
    return g;
}

void print(const std::vector<long long>& arr) {
    for (auto el : arr) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

long long slow(long long n) {
    std::vector<long long> arr = { 1, 1 };
    for (int i = 1; i < n; ++i) {
        std::vector<long long> arrN(arr.size()*2 - 1);
        int k = 0;
        for (int j = 0; j < arr.size() - 1; ++j) {
            arrN[k++] = arr[j];
            arrN[k++] = arr[j] + arr[j+1];
        }
        arrN[k++] = arr.back();
        arr = arrN;
    }
    return std::count(arr.begin(), arr.end(), n);
}

long long slow2(long long n) {
    std::vector<long long> arr = { 1, 1 };
    for (int i = 1; i < n; ++i) {
        std::vector<long long> arrN;
        int k = 0;
        for (int j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] > n) {
                continue;
            }
            arrN.push_back(arr[j]);
            arrN.push_back(arr[j] + arr[j + 1]);
        }
        arrN.push_back(arr.back());
        arr = arrN;
    }
    return std::count(arr.begin(), arr.end(), n);
}

long long slow3(long long n) {
    if (n == 1) {
        return 2;
    }
    if (n == 2) {
        return 1;
    }
    std::vector<long long> arr = { 1, 2 };
    for (int i = 2; i < n; ++i) {
        std::vector<long long> arrN;
        int k = 0;
        for (int j = 0; j < arr.size() - 1; ++j) {
            if (arr[j] > n) {
                assert(false);
            }
            arrN.push_back(arr[j]);
            if (arr[j] + arr[j + 1] > n) {
                continue;
            }
            arrN.push_back(arr[j] + arr[j + 1]);
        }
        arrN.push_back(arr.back());
        arr = arrN;
        // print(arr);
    }
    
    return 2 * std::count(arr.begin(), arr.end(), n);
}

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


long long primeFactors(long long& n, long long limit)
{

    long long res = 1;
    if (n % 2 == 0) {
        res = combine(n, 2);
    }

    // n must be odd at this point. So we can skip 
    // one element (Note i = i +2) 
    for (int i = 3; i <= limit; i = i + 2) {
        // While i divides n, print i and divide n 
        if (n % i == 0)
        {
            res *= combine(n, i);
        }        
    }
    return res;
}

long long trial_division3(long long& n, long long limit) {
    long long res = 1;
    // Print the number of 2s that divide n 
    long long tmp = 1;

    for (int d : {2, 3, 5}) {
        if (n % d == 0) {
            res *= combine(n, d);
        }
    }
    static std::array<int, 8> increments = { 4, 2, 4, 2, 4, 6, 2, 6 };
    int i = 0;
    for (long long d = 7; d <= limit; d += increments[i++]) {
        if (n % d == 0) {
            res *= combine(n, d);
        }
        if (i == 8) {
            i = 0;
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
    if (n == 2) {
        return 1;
    }

    long long smallLimit = 10000;
    long long limit = smallLimit * smallLimit;
    long long res = primeFactors(n, smallLimit);
    while (n > limit) {
        long long d = brent(n);
        if (d == n) {
            return res * (n - 1);
        }
        res *= combine(n, d);
    }

    if (n < smallLimit) {
        return res;
    }
    if (n < limit) {
        return res * (n - 1);
    }
}



int main() {
    long long n;
    std::cin >> n;
    std::cout << fast(n) << std::endl;
    // std::cout << brent(137) << std::endl;
    // std::cout << fast(10'000'000'000'000ll) << std::endl;
    // std::cout << slow2(200) << std::endl;
    /*
    for (int i = 1; i <= 100; ++i) {
        // assert(slow2(i) == slow3(i));
        int sl = slow3(i);
        int ff = fast(i);
        assert(sl == ff);
        std::cout << i << " " << slow3(i) << std::endl;
    }
    */
    return 0;
}
