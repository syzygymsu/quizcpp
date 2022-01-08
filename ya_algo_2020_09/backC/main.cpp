// problems/B/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdint>

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
    std::unordered_map<int, int> m_unique;

    for (int i = 0; i < n; ++i) {
        int t;
        f >> t;
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
    int64_t right = 1e19;
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
