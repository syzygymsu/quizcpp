#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

/*
Написать метод, который заменит все пробелы в строке на "%20" inplace.
На вход подается строка с зарезервированными под расширение символами
(гарантируется, что resize до разумных размеров не будет аллоцировать память).

void urlify(std::string& s);

std::string s0 = "my url";
s0.reserve(20);
urlify(s0);
assert(s0 == "my%20url");
*/


using namespace std;

void urlify(std::string& s) {
    size_t spaceCount = 0;
    for (char c : s) {
        if (c == ' ') {
            ++spaceCount;
        }
    }
    size_t oldSize = s.size();
    size_t currIndex = s.size() + spaceCount * 2;
    s.resize(currIndex);
    for (int i = static_cast<int>(oldSize) - 1; i >= 0; --i) {
        char c = s[i];
        if (c != ' ') {
            s[--currIndex] = c;
        }
        else {
            s[--currIndex] = '0';
            s[--currIndex] = '2';
            s[--currIndex] = '%';
        }
    }
}


int main()
{
    std::string s0 = "my url";
    s0.reserve(20);
    urlify(s0);
    assert(s0 == "my%20url");
    return 0;
}
