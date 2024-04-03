#include <vector>
#include <numeric>

// https://leetcode.com/problems/domino-and-tromino-tiling/description/
class Solution {
    static const int modulo = 1e9 + 7;

public:
    int numTilings(int n) {
        std::vector<int> ans(n + 1, -1);
        ans[0] = 1;
        return helper(n, ans);
    }

    static int add(int k, long long diff) {
        return (diff + k) % modulo;
    }

    int helper(int n, std::vector<int> &ans) {
        if (n < 0) {
            return 0;
        }
        if (ans[n] > 0) {
            return ans[n];
        }
        int first = helper(n - 1, ans);
        int second = helper(n - 2, ans);
        int third = 0;
        for (int i = 0; 3 + i * 2 <= n; ++i) {
            third = add(third, 2ll * helper(n - 3 - 2 * i, ans));
        }

        int forth = 0;
        for (int i = 0; 4 + i * 2 <= n; ++i) {
            forth = add(forth, 2ll * helper(n - 4 - 2 * i, ans));
        }

        // int res = add(add(add(third, first), second), forth);
        int v[] = {first, second, third, forth};
        int res = std::reduce(std::begin(v), std::end(v), 0, add);
        ans[n] = res;
        return res;
    }
};
