#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

/*
https://leetcode.com/problems/add-two-numbers/submissions/
*/



struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int vUme = 0;
        ListNode* l2First = l2;
        ListNode* l1First = l1;
        while(true) {
            int sum = vUme + l1->val;
            if (l2 != nullptr) {
                sum += l2->val;
            }
            if (sum >= 10) {
                vUme = sum/10;
                sum = sum%10;
            } else {
                vUme = 0;
            }
            l1->val = sum;
            if (l1->next != nullptr) {
                l1 = l1->next;  
                if (l2 != nullptr) {
                    l2 = l2->next;
                } else {
                    if (vUme == 0) {
                        return l1First;
                    }
                }
            } else {
                if (l2 == nullptr || l2->next == nullptr) {
                    if (vUme != 0) {
                        l1->next = l2First;
                        l2First->next = nullptr;
                        l2First->val = vUme;
                    }
                    return l1First;
                }
                l1->next = l2->next;
                l1 = l2->next;
                l2 = nullptr;
            }
        }
    }
};


int main()
{
    assert(true);
    return 0;
}
