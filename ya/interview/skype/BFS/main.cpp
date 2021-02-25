#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

std::vector<int> bfs(int s, int toV, int n, const std::vector<std::vector<int> >& g) {
    std::queue<int> q;
    q.push(s);
    std::vector<bool> used(n);
    std::vector<int> d(n), p(n);
    used[s] = true;
    p[s] = -1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (!used[to]) {
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }
    if (!used[toV]) {
        cout << "No path!";
        return {};
    }
    else {
        vector<int> path;
        for (int v = toV; v != -1; v = p[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        std::cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] + 1 << " ";
        }
        return path;
    }
}


int main()
{
    vector < vector<int> > g; // граф
    int n = 5; // число вершин
    int s = 0; // стартовая вершина (вершины везде нумеруются с нуля)
    bfs(s, n, n, g);

    return 0;
}
