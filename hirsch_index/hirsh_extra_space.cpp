#include "hirsh.h"
#include <vector>

int hirsh_extra_space(const std::vector<int>& v) {
    std::vector<int> h(v.size() + 1);
    for (auto el : v) {
        if (el < h.size()) {
            ++h[el];
        }
        else {
            ++h[h.size() - 1];
        }
    }
    int summ = 0;
    for (int i = static_cast<int>(h.size()) - 1; i >= 0; --i) {
        summ += h[i];
        if (summ >= i) {
            return i;
        }
    }
    return 0;
}
