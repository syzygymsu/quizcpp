/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
ListNode* mergeKLists(vector<ListNode*>& v) {
    if (v.empty()) {
        return nullptr;
    }
    ListNode* result = nullptr;    
    std::make_heap(v.begin(), v.end(), compareNodes);
    while (true) {
        std::pop_heap(v.begin(), v.end(), compareNodes);
        auto top = v.back();
        if (top == nullptr) {
            return reverseList(result);
        }
        v.back() = top->next;
        top->next = result;
        result = top;
        std::push_heap(v.begin(), v.end(), compareNodes);
    }


    }
private:
    bool compareNodes(ListNode* left, ListNode* right) {
        if (right == nullptr) {
            return false;
        }    

        if (left == nullptr) {
            return true;
        }
        return left->val > right->val;
    }
    
    ListNode* reverseList(ListNode* node) {
        ListNode* prev = nullptr;
        while (node != nullptr) {
            ListNode* next = node->next;
            node->next = prev;
            prev = node;
            node = next;
        }
        return prev;
    }
};
