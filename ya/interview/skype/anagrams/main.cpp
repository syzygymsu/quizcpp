#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <unordered_map>

// ["eat", "tea", "tan", "ate", "nat", "bat"]
/* [
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
] */

struct VectorHasher {
    int operator()(const std::vector<int>& V) const {
        int hash = V.size();
        for (auto& i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

std::vector<int> getTrace(const std::string& s) {
    std::vector<int> res(26);
    for (char c : s) {
        ++res[c - 'a'];
    }
    return res;
}

std::vector<std::vector<std::string>> anagrams(const std::vector<std::string> &input)
{
    std::unordered_map<std::vector<int>, std::vector<std::string>, VectorHasher> map;
    for (auto s : input) {
        std::vector<int> trace  = getTrace(s);
        auto it = map.find(trace);
        if (it == map.end()) {
            std::vector<std::string> emptyVec;
            emptyVec.push_back(s);
            map[trace] = emptyVec;
        }
        else {
            it->second.push_back(s);
        }
    }
    std::vector<std::vector<std::string>> result;
    for (auto entry : map) {
        result.push_back(entry.second);
    }
    return result;
}

int main()
{
    assert(true);
    auto res = anagrams({ "eat", "tea", "tan", "ate", "nat", "bat" });
    for (auto item : res) {
        for (auto s : item) {
            std::cout << s << '\t';
        }
        std::cout << std::endl;
    }
    return 0;
}
