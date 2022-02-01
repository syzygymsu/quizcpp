// https://habr.com/ru/post/648917/

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

size_t solution(const std::string& str) {
    static const std::string unique = "BANLO";
    std::vector<size_t> count(5, 0);
    for (char c : str) {
        size_t ind = unique.find(c);
        if (ind != std::string::npos) {
            ++count[ind];
        }
    }
    return std::min({ count[0], count[1], count[2], count[3] / 2, count[4] / 2 });
}

int main()
{
    assert(solution("BAONXXOLL") == 1);
    assert(solution("BAOOLLNNOLOLGBAX") == 2);
    assert(solution("QAWABAWONL") == 0);
    return 0;
}
