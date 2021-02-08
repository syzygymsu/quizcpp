#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

void merge(std::map<int, int>& map, int key, int value) {
    auto entry = map.find(key);
    if (entry != map.end()) {
        entry->second += value;
    }
    else {
        map[key] = value;
    }
}


size_t maxGuests(const std::vector<std::pair<int, int>>& segments) {
    std::map<int, int> map;
    for (const auto& segment : segments) {
        merge(map, segment.first, 1);
        merge(map, segment.second, -1);
    }
    int max = 0;
    int summ = 0;
    for (const auto& entry : map) {
        summ += entry.second;
        max = std::max(summ, max);
    }
    return max;
}

int main()
{
    assert(maxGuests({}) == 0);
    assert(maxGuests({ {1, 2} }) == 1);
    assert(maxGuests({ {1, 2}, {2, 3} }) == 1);
    assert(maxGuests({ {1, 5}, {0, 1}, {4, 5} }) == 2);
    return 0;
}
