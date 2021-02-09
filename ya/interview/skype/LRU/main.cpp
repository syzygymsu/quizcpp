#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

/*
Есть 2 взаимодействующие системы. Одна из них - БД хранящая информацию о
пользователях, вторая - использует эту информацию для принятия решения.
Пользователи обычно используют систему периодами (сессиями), и в рамках сессии
делают много запросов. Между сессиями достаточно большой временной интервал.
Хочется сэкономить ресурсы БД и повторяющиеся запросы по возможности не
выполнять заново, а выдавать уже запомненный где-то результат.
*/

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

LRU::LRU(int _capacity) : capacity(_capacity), head{ nullptr }, tail{ nullptr } {}

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
        // TODO
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
    LRU cache(4);
    cache.add(1, 1);
    cache.add(10, 15);
    cache.add(15, 10);
    cache.add(10, 16);
    cache.add(12, 15);
    cache.add(18, 10);
    cache.add(13, 16);

    assert(-1 == cache.get(1));
    assert(16 == cache.get(10));
    assert(-1 == cache.get(15));
    return 0;
}
