// problems/A/
// https://contest.yandex.ru/contest/19811/problems/O/

#include <iostream>
#include <bit>

typedef unsigned int ui;

void setBitToMask(int n, ui& mask) {
    mask |= 1 << n;
}

int readInt() {
    int x;
    std::cin >> x;
    return x;
}

void print(int count) {
    if (count >= 3) {
        std::cout << "Lucky" << std::endl;
    }
    else {
        std::cout << "Unlucky" << std::endl;
    }
}

int main() {
    ui mask = 0;
    for (int i = 0; i < 10; ++i) {
        setBitToMask(readInt() - 1, mask);
    }
    int n = readInt();
    for (int i = 0; i < n; ++i) {
        ui ticket = 0;
        for (int j = 0; j < 6; ++j) {
            setBitToMask(readInt() - 1, ticket);
        }
        print(std::popcount(mask & ticket));
    }
    return 0;
}
