#include <iostream>
#include <vector>
#include <cstring>

void print(const std::vector<int>& row) {
    std::cout << "[";
    for (int v : row) {
        std::cout << v << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    int n = 10;
    std::vector<int> positions(n, 0);
    int from = 5;
    int filler = 1;
    memset(&positions[from], filler, sizeof(int) * (n-from));
    print(positions);
    return 0;
}
