// Найдутся 100 подряд идущих натуральных чисел среди которых ровно 5 простых - https://youtu.be/rEHheWPSG-k?t=2826

/*
 * C++ Program to Implement Miller Rabin Primality Test
 */
#include <iostream>
#include <cstring>
#include <cstdlib>
#define ll long long
using namespace std;

/*
 * calculates (a * b) % c taking into account that a * b might overflow
 */
ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0, y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}
/*
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}

/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(ll p, int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2 == 0)
    {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

// works under 1373653 
// https://stackoverflow.com/questions/4424374/determining-if-a-number-is-prime
bool isPrime(int number)
{
    if (((!(number & 1)) && number != 2) || (number < 2) || (number % 3 == 0 && number != 3))
        return false;

    for (int k = 1; 36 * k * k - 12 * k < number; ++k)
        if ((number % (6 * k + 1) == 0) || (number % (6 * k - 1) == 0))
            return false;
    return true;
}

bool isPrimeSlow(int number) {

    if (number < 2) return false;
    if (number == 2) return true;
    if (number % 2 == 0) return false;
    for (int i = 3; (i * i) <= number; i += 2) {
        if (number % i == 0) return false;
    }
    return true;

}


bool test(int a) {
    int cnt = 0;
    for (int i = a; i < a + 100; ++i) {
        if (isPrimeSlow(i)) {
            // std::cout << i << std::endl;
            ++cnt;
        }
    }
    return cnt == 0;
}

int main()
{
    for (int i = 0; i < 1000000; ++i) {
        if (test(i)) {
            std::cout << i << std::endl;
        }
    }
	return 0;
}
