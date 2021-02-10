#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

vector<int> bfs(int s, int to, int n, const vector < vector<int> >& g) {
    queue<int> q;
    q.push(s);
    vector<bool> used(n);
    vector<int> d(n), p(n);
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
    if (!used[to]) {
        cout << "No path!";
        return {};
    }
    else {
        vector<int> path;
        for (int v = to; v != -1; v = p[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
        cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i)
            cout << path[i] + 1 << " ";
        return path;
    }
}


int main()
{
    vector < vector<int> > g; // граф
    int n; // число вершин
    int s; // стартовая вершина (вершины везде нумеруются с нуля)

    return 0;
}
