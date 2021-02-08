#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <vector>

void addToString(std::string& s, int begin, int end) {
    if (!s.empty()) {
        s.push_back(',');
    }
    if (begin == end) {
        s.append(std::to_string(begin));
    }
    else {
        s.append(std::to_string(begin));
        s.push_back('-');
        s.append(std::to_string(end));
    }
}

std::string compress(std::vector<int> vec) {
    if (vec.empty()) {
        return "";
    }
    std::sort(vec.begin(), vec.end());
    int begin = vec[0];
    int end = begin;
    std::string result = "";
    for (int i = 1; i < vec.size(); ++i) {
        int curr = vec[i];
        if (curr == end + 1) {
            ++end;
        }
        else {
            addToString(result, begin, end);
            begin = curr;
            end = curr;
        }

    }
    addToString(result, begin, end);
    return result;
}

int main()
{
    std::cout << compress({ 1, 0, 3, 5, 12, 8 });
    assert(compress({ 1, 0, 3, 5, 12, 8 }) == "0-1,3,5,8,12");
    assert(compress({ 1, 4, 5, 2, 3, 9, 8, 11, 0 }) == "0-5,8-9,11");
    return 0;
}
