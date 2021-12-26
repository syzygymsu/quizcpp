#include <iostream>
#include <string>

int digits(const std::string& s) {
    int count = 0;
    for (int i = 0; i < s.size();) {
        if (s[i] == 'o') {
            i += 3;
        }
        else {
            i += 4;
        }
        ++count;
    }
    return count;
}

int main() {
    std::string first;
    std::string second;
    std::getline(std::cin, first);
    std::getline(std::cin, second);
    int size1 = digits(first);
    int size2 = digits(second);
    if (size1 < size2) {
        std::cout << "<" << std::flush;
        return 0;
    }
    if (size1 > size2) {
        std::cout << ">" << std::flush;
        return 0;
    }
    int i1 = 0;
    int i2 = 0;
    while (true) {
        if (i1 >= first.size()) {
            break;
        }
        if (i2 >= second.size()) {
            break;
        }
        if (first[i1] == 'o') {
            if (second[i2] == 'o') {
                i1 += 3;
                i2 += 3;
            }
            else {
                std::cout << ">" << std::flush;
                return 0;
            }
        }
        else {
            if (second[i2] == 'z') {
                i1 += 4;
                i2 += 4;
            }
            else {
                std::cout << "<" << std::flush;
                return 0;
            }
        }
    }

    std::cout << "=" << std::flush;
    return 0;
}
