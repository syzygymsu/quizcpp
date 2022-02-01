// https://habr.com/ru/post/648917/

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

size_t helper(const std::string& str, const std::string& sample) {
    static const constexpr int alphabet_size = 26;
    std::vector<size_t> mask(alphabet_size, 0);
    for (char c: sample) {
        int ind = c - 'A';
        ++mask[ind];
    }
    
    std::vector<size_t> all(alphabet_size, 0);
    for (char c: str) {
        int ind = c - 'A';
        ++all[ind];
    }
    
    size_t result = str.size();
    for (int i = 0; i < alphabet_size; ++i) {
         size_t mask_mark = mask[i];
         if (mask_mark > 0) {
            result = std::min(result, all[i] / mask_mark); 
         }
    }
    return result;
}

size_t solution2(const std::string& str) {
    return helper(str, "BALLOON");
}

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
    assert(solution2("BAONXXOLL") == 1);
    assert(solution2("BAOOLLNNOLOLGBAX") == 2);
    assert(solution2("QAWABAWONL") == 0);
    return 0;
}
