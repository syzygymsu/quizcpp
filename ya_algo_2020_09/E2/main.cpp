// https://contest.yandex.ru/contest/19811/problems/E/

#include <iostream>
#include <queue>
#include <deque>
#include <vector>
#include <cassert>

struct Node {
    Node() : parent(0), k(0), visited(0), level(-1) {};
    int parent;
    int k;
    int visited;
    int level;
    std::vector<int> child;
};

std::priority_queue<std::pair<int, int>> setLevels(std::vector<Node>& parents) {
    std::queue<int> q;
    std::priority_queue<std::pair<int, int>> res;
    res.push({ 0, parents.size()  - 1});
    q.push(parents.size() - 1);
    for (; !q.empty(); q.pop()) {
        int ind = q.front();
        Node& v = parents[ind];
        for (int chind : v.child) {
            Node& ch = parents[chind];
            if (ch.level >= 0) {
                continue;
            }
            ch.level = v.level + 1;
            res.push({ ch.level, chind });
            q.push(chind);
        }
    }
    return res;
}

void debug_print(const std::deque<int>& t) {
    std::cout << "debug_print ";
    for (int el : t) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
}

int solve(std::vector<Node> parents) {
    std::priority_queue<std::pair<int, int>> q = setLevels(parents);
    int res = 0;
    for (; !q.empty(); q.pop()) {
        auto [level, ind1] = q.top();
        std::deque<int> temp;
        temp.push_back(ind1);
        while (!temp.empty()) {            
            const int ind = temp.front();
            temp.pop_front();
            if (ind == parents.size() - 1) {
                return res;
            }
            Node& v = parents[ind];
            if (v.visited) {
                continue;
            }
            v.visited = 1;
            ++res;
            for (int chInd : v.child) {
                Node& ch = parents[chInd];
                if (!ch.visited) {
                    temp.push_back(chInd);
                }
            }
            const int nextInd = v.parent;
            assert(v.k >= 0);
            assert(nextInd >= 0);
            Node& next = parents[nextInd];
            if (next.visited) {
                continue;
            }
            --next.k;
            if (next.k <= 0) {
                temp.push_front(nextInd);
            }            
        }
    }
    assert(false);
    return res;
}


int readInt() {
    int x;
    std::cin >> x;
    return x;
}

int solveTest() {
    int n = readInt();
    int k = readInt() - 1;
    std::vector<Node> parents(n);
    for (int i = 0; i < n - 1; ++i) {
        int p = readInt() - 1;
        parents[i].parent = p;
        parents[i].k = k;
        parents[p].child.push_back(i);
    }
    parents.back().parent = -1;
    parents.back().k = k;
    parents.back().level = 0;
    return solve(std::move(parents));
}

int main() {
    int t = readInt();
    for (int i = 0; i < t; ++i) {
        std::cout << solveTest() << std::endl;
    }
    return 0;
}
