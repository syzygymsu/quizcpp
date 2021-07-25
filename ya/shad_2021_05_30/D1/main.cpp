#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>

using namespace std;

int main()
{
    using pr = pair<int, int>;
    auto rev = [](pr e) {return pr{ e.second, e.first }; };



    int n = 5;
    cin >> n;
    vector<pr> edges;
    for (int i = 0; i < n-1; ++i) {
        int j, k;
        cin >> j;
        cin >> k;
        edges.push_back(make_pair(j, k));
    }

    unordered_map<int, vector<pr>> in;
    unordered_map<int, vector<pr>> out;
    for (pr edge : edges) {
        in[edge.second].push_back(edge);
        in[edge.first].push_back(rev(edge));
        out[edge.first].push_back(edge);
        out[edge.second].push_back(rev(edge));
    }

    queue<pr> q;
    for (pr edge : edges) {
        q.push(edge);
        q.push(rev(edge));
    }

    map<pr, int> depths;
    while (!q.empty()) {
        pr dir = q.front();
        q.pop();

        if (depths.count(dir)) {
            continue;
        }

        int depth = 0;
        bool incomplete = false;
        for (pr e : out.at(dir.second)) {
            if (e == rev(dir)) {
                continue;
            }
            auto it = depths.find(e);
            if (it == depths.end()) {
                incomplete = true;
                break;
            }
            depth = max(depth, it->second);
        }
        if (!incomplete) {
            depths[dir] = 1 + depth;
            for (pr e : in.at(dir.first)) {
                if (e == dir) {
                    continue;
                }
                q.push(e);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        int depth = 0;
        for (pr e : out.at(i)) {
            depth = max(depth, depths.at(e));
        }
        cout << depth << " ";
    }
    cout << endl;

    return 0;
}
