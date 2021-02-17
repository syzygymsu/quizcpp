#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <queue>
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
    Node* left = toTreeRec(begin, half, arr);
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

void printNode(Node* n) {
    if (n != nullptr) {
        printNode(n->left);
        std::cout << n->val << " ";
        // std::cout << std::endl;
        printNode(n->right);
    }
    // std::cout << std::endl;
}


void cleanup(Node* n) {
    if (n != nullptr) {
        cleanup(n->left);
        cleanup(n->right);
        delete n;
    }
}

/*
{}
{1, 2}
{1, 2, 6}
{1, 2, 3, 4, 5, 6}
*/

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
        int sqrt = (int)std::sqrt(i);
        if (sqrt*sqrt == i) {
            dp.push_back(Helper(sqrt, 1, -1));
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
    std::vector<int> res;
    int currIndex = n;
    while (currIndex > 0) {
        Helper h = dp[currIndex];
        res.push_back(h.val);
        currIndex = h.prev;
    }
    return res;
}

void test2() {
    auto res = toList(2);
    for (int a : res) {
        std::cout << a << " ";
    }
    std::cout << std::endl;
    assert(res[0] == 1);
}

void test1(const std::vector<int>& arr) {
    Node* r = toTree(arr);
    printNode(r);
    cleanup(r);
}
 
int main()
{
    assert(true);

    test1({});
    std::cout << std::endl;
    test1({1});
    std::cout << std::endl;
    test1({1, 2});
    std::cout << std::endl;
    test1({ 1, 2 , 3});
    std::cout << std::endl;

    return 0;
}
