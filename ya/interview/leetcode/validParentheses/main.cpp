#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>
#include <algorithm>
#include <unordered_map>

/*
https://leetcode.com/problems/valid-parentheses/submissions/
*/

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if (s.empty()) {
            return true;
        }
        vector<char> stack;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            int closedIndex = index(closed, c);
            if (closedIndex >= 0) {
                if (stack.empty()) {
                    return false;
                }
                char o = stack.back();
                int openIndex = index(open, o);
                if (closedIndex != openIndex) {
                    return false;
                }
                stack.pop_back();
            } else {
                stack.push_back(c);
            }
        }
        return stack.empty();
    }
    
private:
    static constexpr char closed[] = {')', '}', ']'};
    static constexpr char open[] = {'(', '{', '['};

    static int index(const char* arr, char c) {
        for (int i = 0; i < 3; ++i) {
            if (c == arr[i]) {
                return i;
            }            
        }
        return -1;
    } 
};

int main()
{
    assert(true);
    return 0;
}
