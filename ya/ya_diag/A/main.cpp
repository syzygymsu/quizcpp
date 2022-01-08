#include <iostream>
#include <string>

int main() {
    std::string j, s;
    std::cin >> j >> s;

    int map[26] = { 0 };
    for (char c : j) {
        map[c - 'a'] = 1;
    }

    int result = 0;
    for (char c : s) {
        result += map[c - 'a'];
    }

    std::cout << result << std::endl;
    return 0;
}
