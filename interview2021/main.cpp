#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

// using namespace std;


struct Node {
    int key;
    int value;
    Node* left;
    Node* right;
};

class LRU {
public:
    LRU(int capacity);
    void add(int key, int value);
    int get(int key);
private:
    std::unordered_map<int, Node*> map;
    int capacity;
    Node* head;
    Node* tail;
};

LRU::LRU(int _capacity) : capacity{ _capacity }, head{ nullptr }, tail{ nullptr } {}

int LRU::get(int key) {
    auto it = map.find(key);
    if (it == map.end()) {
        return -1;
    }
    else {
        Node* node = it->second;
        if (node->right != nullptr) {
            node->right->left = node->left;
        }
        if (node->left != nullptr) {
            node->left->right = node->right;
        }
        
        node->left = node->right = nullptr;
        if (tail != nullptr) {
            tail->right = node;
            node->left = tail;
        }
        tail = node;
        if (head == nullptr) {
            head = tail;
        }
        return node->value;
    }
}

void LRU::add(int key, int value) {
    int res = get(key);

    if (res == -1) {
        Node* node = new Node();
        node->left = node->right = nullptr;
        node->key = key;
        node->value = value;
        if (map.size() < capacity) {
            if (tail != nullptr) {
                tail->right = node;
                node->left = tail;
            }
            tail = node;
            if (head == nullptr) {
                head = tail;
            }
            map[key] = node;
        }
        else {
            if (head != nullptr) {
                Node* headRight = head->right;
                if (headRight != nullptr) {
                    headRight->left = nullptr;
                }
                map.erase(head->key);
                delete head;
                head = headRight;

            }
            if (tail == nullptr) {
                tail = head;
            }

            if (tail != nullptr) {
                tail->right = node;
                node->left = tail;
            }
            tail = node;
            if (head == nullptr) {
                head = tail;
            }
            map[key] = node;


        }
    }
    else {
        auto it = map.find(key);
        it->second->value = value;
    }
}



int main()
{
    assert(true);
    return 0;
}
