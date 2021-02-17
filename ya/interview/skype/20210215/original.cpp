#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

// Given an array where elements are sorted in ascending order,
// convert it to a height balanced BST.

struct Node {
  Node(int _val, Node* _left, Node* _right) : val{_val}, left{_left}, right{_right} {}
  int val;
  Node* left;
  Node* right;  
};


Node* toTreeRec(size_t begin, size_t end, const std::vector<int>& arr) {
    if (begin >= end) {
        return nullptr;
    }
    size_t half = (end+begin)/2;
    Node* left = toTreeRec(0, half, arr);
    Node* right = toTreeRec(half+1, end, arr);

    Node* root = new Node(arr[half], left, right);
    return root;        
}

Node* toTree(const std::vector<int>& arr) {
    if (arr.empty()) {
        return nullptr;
    }
    return toTreeRec(0, arr.size(), arr);
}


{}
{1, 2}
{1, 2, 6}
{1, 2, 3, 4, 5, 6}


// Дано натуральное число.
// Вернуть список целых чисел, сумма квадратов которых даст исходное число.
// Список должен быть минимальной длины.
// S = a1^2 + a2^2 + ... + aN^2
// S = a1^2 + S', S' < S, S' = S - a1^2

struct Helper {
    Helper (int _val, int _count, int _prev) : val(_val), count(_count), prev(_prev) {}
  int val;
  int count;
  int prev;  
};

std::vector<int> toList(int n) {
    assert(n >= 1);
    std::vector<Helper> dp;
    dp.push_back(Helper(0, 0, -1));
    dp.push_back(Helper(1, 1, -1));
    for (int i = 2; i <= n; ++i) {
        int sqrt = sqrt(n);
        if (sqrt*sqrt == n) {
            dp.push_back(Helper(i, 1, -1));
        } else {
            int min = i;
            Helper h(i, min, -1);
            for (int j = 1; j <= sqrt; ++j) {
                int sPrev = i - j*j;
                if (min > dp[sPrev].count) {
                    min = dp[sPrev].count;
                    h.prev = sPrev;
                    h.count = min + 1;
                    h.val = j;
                }
            }
            dp.push_back(h);
        }
        
    }
    vector<int> res;
    int currIndex = n;
    while (currIndex > 0) {
        Helper h = dp[currIndex];
        res.push_back(h.val);
        currIndex = h.prev;
    }
    return res;
}
