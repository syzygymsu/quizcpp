#include "hirsh.h"

int hirsh_extra_space(const std::vector<int>& v) {
    std::vector<int> h(v.size() + 1);
    for (auto el : v) {
        if (el < h.size()) {
            ++h[el];
        }
        else {
            ++h.back();
        }
    }
    size_t summ = 0;
    for (size_t i = h.size(); i > 0; --i) {
        summ += h[i-1];
        if (summ >= i-1) {
            return static_cast<int>(i-1);
        }
    }
    return 0;
}
