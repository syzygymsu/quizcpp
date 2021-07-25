#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    std::string s = "";
    std::cin >> s;
    int n = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        n += s[i] - '0';
    }
    //    std::cout << n << std::endl;

    if (n % 2 == 0) {
        std::cout << 2 << std::endl;
        return 0;
    }

    if (s.size() % 3 == 0) {
        std::cout << 3 << std::endl;
        return 0;
    }

    int d = 982451653; // 

    unsigned long long int ones = 1;
    for (int i = 1; i < s.size(); ++i) {
        ones = (ones * 10) % d;
        ones += 1;
    }

    for (int i = 3; i <= n; i += 2)
    {
        if (n % i == 0 || ones % i == 0) {
            d = i;
            break;
        }
    }


    std::cout << d << std::endl;
    return 0;
}
