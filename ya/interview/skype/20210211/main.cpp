#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <queue>

/*
Вход: [1, 5] [4, 8] [0, 2] [10, 15]
Выход: [0, 8] [10, 15]

Вход: [1, 3] [100, 200] [2, 4]
Выход: [1, 4] [100, 200]
*/

/*

*/
std::vector<std::pair<int, int>> merge_segment(const std::vector<std::pair<int, int>>& _segments) {
    if (_segments.empty()) {
        return _segments;
    }
    std::vector<std::pair<int, int>> res;
    std::vector<std::pair<int, int>> segments = _segments;
    std::sort(segments.begin(), segments.end());
    int currLeft = segments[0].first;
    int currRight = segments[0].second;
    for(int i = 1; i < segments.size(); ++i) {
        const auto& seg = segments[i]; 
        if (currRight > seg.first) {
            currRight = std::max(currRight, seg.second);
        } else {
            res.push_back(std::make_pair(currLeft, currRight));
            currLeft = seg.first;
            currRight = seg.second;
        }
        
    }
    res.push_back(std::make_pair(currLeft, currRight));
    return res;
}


struct Node {
    int _value ;
    Node* next;
};

/*
assert(mergeLists({}) == nullptr);

assert(mergeLists({}) == nullptr);
*/
Node* mergeLists(std::vector<Node*> lists) {
    Node * good = nullptr;
    Node * tail = nullptr;
    while (true) {
        Node* min = nullptr;
        for (int i = 0; i < (int)lists.size(); ++i) {
            Node* curr = lists[i];
            if (curr != nullptr) {
                if (min == nullptr) {
                    min = curr;
                } else {
                    if (min->_value > curr->_value) {
                        min = curr;
                    }
                }
                lists[i] = curr->next;
            }
            
        }
        if (min == nullptr) {
            return good;
        }
        min->next = nullptr;
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


int read4(char *buf);

int read(char* buf, int n) {
    if (n == 0) {
        return 0;
    }
    int summ = 0;
    char temp[4];
    int curr = read4(temp);
    while (n > 0 && curr == 4) {
        for (int i = 0; i < 4; ++i) {
            buf[summ] = temp[i];
        }
        summ+=4;
        --n;
        curr = read4(temp);
    }
    for (int i = 0; i < std::min(n, curr); ++i) {
        buf[summ] = temp[i];
        ++summ;
    }
    return summ;
}


int main()
{
    assert(true);
    return 0;
}
