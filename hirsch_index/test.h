#pragma once
#include <functional>
#include <vector>
bool test(std::function<int(std::vector<int>&)> to_test);
bool test(std::function<int(std::vector<int>&)> to_test, const std::vector<std::pair<std::vector<int>, int>>& tests);
