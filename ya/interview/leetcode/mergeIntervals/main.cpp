#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

/*
https://leetcode.com/problems/merge-intervals/submissions/
*/

using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& segments) {
    if (segments.empty()) {
        return segments;
    }
    std::vector<vector<int>> res;
    std::sort(segments.begin(), segments.end());
    int currLeft = segments[0][0];
    int currRight = segments[0][1];
    for(int i = 1; i < segments.size(); ++i) {
        const auto& seg = segments[i]; 
        if (currRight >= seg[0]) {
            currRight = std::max(currRight, seg[1]);
        } else {
            res.push_back({currLeft, currRight});
            currLeft = seg[0];
            currRight = seg[1];
        }
        
    }
    res.push_back({currLeft, currRight});
    return res;

    }
};

int main()
{
    assert(true);
    return 0;
}
