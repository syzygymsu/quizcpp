#include <iostream>
#include <string>
#include <string_view>
#include <cassert>
#include <vector>

std::string normalize(std::string_view s) {
    if (s.empty()) {
        return "";
    }
    constexpr char DELIM = '/';
    constexpr std::string_view SAME = ".";
    constexpr std::string_view UP = "..";
    const bool hasRoot = s[0] == DELIM;

    std::vector<std::string_view> stack;
    int begin = 0;
    for (int i = 0; i <= s.size(); ++i) {
        if (i == s.size() || s[i] == DELIM) {
            if (begin < i) {
                std::string_view last = s.substr(begin, i - begin);
                if (last == UP) {
                    if (!stack.empty()) {
                        stack.pop_back();
                    }
                    else {
                        stack.push_back(last);
                    }
                }
                else if (last != SAME) {
                    stack.push_back(last);
                }
            }
            begin = i + 1;
        }
    }

    std::string res;
    for (auto part : stack) {
        if (!res.empty() || hasRoot) {
            res += DELIM;
        }
        res += part;
    }
    return res;
}

int main()
{
    assert(normalize("/a//b/") == "/a/b");
    assert("/foo/bar/baz/asdf" == normalize("/foo/bar//baz/asdf/quux/.."));
    assert("../b" == normalize("a/../../b"));
    assert("/documents/root" == normalize("/////documents/root/"));
    assert("/etc" == normalize("/////documents/root/.././../etc"));
    assert("etc" == normalize("./config/../etc"));
    assert("/etc" == normalize("/etc/"));

    return 0;
}
