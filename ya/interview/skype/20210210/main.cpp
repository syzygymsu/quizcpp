#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <queue>

struct Node {
    int val;
    Node* next;
};

Node* reverseList(Node* node) {
    Node* prev = nullptr;
    while (node != nullptr) {
        Node* next = node->next;
        node->next = prev;
        prev = node;
        node = next;
    }
    return prev;
}
int listLen(Node* node) {
    int len = 0;
    while (node != nullptr) {
        node = node->next;
        ++len;
    }
    return len;
}

bool isPalindrome(Node* node) {
    Node* begin = node;
    int n = listLen(node);
    if (n == 0 || n == 1) {
        return true;
    }
    int half = (n % 2 == 0) ? n / 2 : (n + 1) / 2;
    Node* curr = node;
    for (int i = 0; i < half; ++i) {
        curr = node->next;
    }
    Node* reversed = reverseList(curr);
    curr = begin;
    while (reversed != nullptr) {
        if (reversed->val != curr->val) {
            return false;
        }
        reversed = reversed->next;
        curr = curr->next;
    }
    return true;
}


class Rejector {
public:
    Rejector(int _time_limit, int _rps) : time_limit(_time_limit), rps(_rps) {}
    bool canRequest(time_t now) {
        removeOld(now);
        if (q.size() >= rps) {
            return false;
        }
        q.push(now);
        return true;
    }
private:
    std::queue<time_t> q;
    int time_limit;
    int rps;


    void removeOld(time_t now) {
        while (!q.empty()) {
            time_t first = q.front();
            if (first + time_limit < now) {
                q.pop(); // 
            }
            else {
                return;
            }
        }
    }
};


int main()
{
    Rejector r(1000, 3);
    assert(r.canRequest(0));
    assert(r.canRequest(1));
    assert(r.canRequest(2));
    assert(!r.canRequest(3));
    assert(!r.canRequest(4));
    assert(r.canRequest(10005));
    return 0;
}
