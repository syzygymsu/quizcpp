#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

void urlify(std::string& s) {
    int spaceCount = 0;
    for (char c : s) {
        if (c == ' ') {
            ++spaceCount;
        }
    }
    int oldSize = s.size();
    int currIndex = s.size() + spaceCount * 2;
    s.resize(currIndex);
    for (int i = oldSize - 1; i >= 0; --i) {
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
