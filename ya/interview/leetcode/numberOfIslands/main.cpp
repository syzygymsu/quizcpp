#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

/*
https://leetcode.com/problems/number-of-islands/submissions/
*/

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if (isLand(i, j, grid)) {
                    ++count;
                }
            }
        }
        return count;
    }
private:
    static bool isLand(int x, int y, vector<vector<char>>& grid) {
        if (x < 0 || x >= grid.size()) {
            return false;
        }
        if (y < 0 || y >= grid[x].size()) {
            return false;
        }
        if (grid[x][y] == '0') {
            return false;
        }
        grid[x][y] = '0';
        for (int i = 0; i < 4; ++i) {
            isLand(x + dx[i], y + dy[i], grid);
        }
        return true;
    }
    static constexpr int dx[] = {-1, 0, 1, 0};    
    static constexpr int dy[] = {0, 1, 0, -1};
};

int main()
{
    assert(true);
    return 0;
}
