// problems/A/
// https://contest.yandex.ru/contest/19811/problems/O/

#include <iostream>
#include <bitset>

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
    std::bitset<32> mask;
    for (int i = 0; i < 10; ++i) {
        mask.set(readInt() - 1);
    }
    int n = readInt();
    for (int i = 0; i < n; ++i) {
        std::bitset<32> ticket;
        for (int j = 0; j < 6; ++j) {
            ticket.set(readInt() - 1);
        }
        print((mask & ticket).count());
    }
    return 0;
}
