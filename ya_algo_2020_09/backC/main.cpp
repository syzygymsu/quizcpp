// problems/B/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <limits>

int64_t count(const std::unordered_map<int, int>& map, long T, int X) {
    int64_t c = 0;
    for (const auto& ti : map) {
        c += std::max((T - (long)ti.second + X) / X, 0L);
    }
    return c;
}

void func(std::istream& f, std::ostream& out) {
    int n, x, k;
    f >> n;
    f >> x;
    f >> k;
    std::vector<int> t_list(n);

    for (int i = 0; i < n; ++i) {
        f >> t_list[i];
    }

    std::unordered_map<int, int> m_unique;
    for (int t : t_list) {
        int key = t % x;
        auto it = m_unique.find(key);
        if (it != m_unique.end()) {
            it->second = std::min(it->second, t);
        }
        else {
            m_unique[key] = t;
        }
    }

    int64_t left = 0;
    int64_t right = std::numeric_limits<int64_t>::max();
    while (right > left) {
        int64_t mid = left + (right - left) / 2;
        int64_t c = count(m_unique, mid, x);
        if (c < k) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    out << left << std::endl;
}

int main() {
    func(std::cin, std::cout);
    return 0;
}
