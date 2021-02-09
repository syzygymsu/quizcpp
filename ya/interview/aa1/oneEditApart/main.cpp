#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>

bool oneEditApart(const std::string& first, const std::string& second) {
    const std::string& small = first.size() <= second.size() ? first : second;
    const std::string& big = first.size() > second.size() ? first : second;
    int lenDiff = static_cast<int>(big.size() - small.size());
    if (lenDiff > 1) {
        return false;
    }
    int diffs = 0;
    for (size_t i = 0; i < small.size(); ++i) {
        if (small[i] != big[i + std::min(diffs, lenDiff)]) {
            ++diffs;
            if (diffs > 1) {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    assert(oneEditApart("cat", "can"));
    assert(oneEditApart("c", ""));
    assert(oneEditApart("", "a"));
    assert(oneEditApart("a", "ca"));
    assert(!oneEditApart("ab", "ca"));
    assert(!oneEditApart("cat", "dog"));
    assert(oneEditApart("cat", "cats"));
    assert(oneEditApart("cat", "cut"));
    assert(oneEditApart("cat", "cast"));
    assert(oneEditApart("cat", "at"));
    assert(!oneEditApart("cat", "acts"));
    return 0;
}
