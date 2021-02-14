#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <algorithm>

struct Node {
    Node(int _val, Node* _next) : value{ _val }, next{ _next } {}
    Node() {}
    int value ;
    Node* next;
};

void print(const std::string& label, Node* node) {
    std::cout << label;
    while (node != nullptr) {
        Node* temp = node->next;
        std::cout << node->value << ' ';
        node = temp;
    }
    std::cout << std::endl;
}


Node* mergeLists(std::vector<Node*> lists) {
    Node * good = nullptr;
    Node * tail = nullptr;
    while (true) {
        Node* min = nullptr;
        int minIndex = -1;
        for (int i = 0; i < (int)lists.size(); ++i) {
            Node* curr = lists[i];
            if (curr != nullptr) {
                // std::cout << "loop1 " << curr->value << std::endl;
                if (min == nullptr) {
                    min = curr;
                    minIndex = i;
                } else {
                    if (min->value > curr->value) {
                        min = curr;
                        minIndex = i;
                    }
                }                
            }
            
        }

        if (min == nullptr) {
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            return good;
        }
        lists[minIndex] = min->next;
        // std::cout << "loop " << min->value << std::endl;
        if (good == nullptr) {
            good = min;
            tail = min;
        } else {
            tail->next = min;
            tail = min;
        }
        
    }
    // never;
}

void printHeap(const std::string& label, const std::vector<Node*>& v) {
    std::cout << label;
    for (auto i : v) {
        if (i == nullptr) {
            std::cout << " null ";
        }
        else {
            std::cout << i->value << ' ';
        }
    }
    std::cout << '\n';
}

bool compareNodes(Node* left, Node* right) {
    if (right == nullptr) {
        return false;
    }
    if (left == nullptr) {
        return true;
    }
    return left->value > right->value;
}

Node* mergeLists2(std::vector<Node*> v) {
    if (v.empty()) {
        return nullptr;
    }
    Node* good = nullptr;
    Node* tail = nullptr;
    std::make_heap(v.begin(), v.end(), compareNodes);
    while (true) {
        std::pop_heap(v.begin(), v.end(), compareNodes);
        auto top = v.back();
        if (top == nullptr) {
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            return good;
        }
        if (good == nullptr) {
            good = top;
            tail = top;
        }
        else {
            tail->next = top;
            tail = top;
        }
        v.back() = top->next;
        std::push_heap(v.begin(), v.end(), compareNodes);
    }

}

void checkList(Node* node, int len) {
    if (node == nullptr) {
        assert(len == 0);
        return;
    }
    int l = 0;
    int prev = node->value;
    while (node != nullptr) {
        assert(node->value >= prev);
        prev = node->value;
        node = node->next;
        ++l;
    }
    assert(len == l);
}

void cleanup(Node* node) {
    while (node != nullptr) {
        Node* temp = node->next;
        delete node;
        node = temp;
    }
}


void test1() {
    Node* first = new Node(1, new Node(3, nullptr));
    Node* second = new Node(2, nullptr);
    Node* res = mergeLists({ first, second });
    checkList(res, 3);
    cleanup(res);
}

void test2() {
    Node* first = new Node(1, new Node(3, nullptr));
    Node* second = new Node(2, nullptr);
    Node* res = mergeLists2({ first, second });
    checkList(res, 3);
    cleanup(res);
}


int main()
{
    test1();
    test2();
    return 0;
}
