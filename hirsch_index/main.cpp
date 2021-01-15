#include <vector>
#include <algorithm>

int hirsh(std::vector<int>& v) {
	auto begin = v.begin();
	auto end = v.end();
	auto mid = v.begin() + v.size() / 2;
	while (end - begin > 1) {
		std::nth_element(begin, mid, end);
		int mid_el = *mid;
		if ((v.end() - mid == mid_el) || (v.end() - mid - 1 == mid_el)) {
			return mid_el;
		}
		if (v.end() - mid < mid_el) {
			end = mid - 1;
		}
		else {
			begin = mid + 1;
		}
		mid = begin + (end - begin) / 2;
	}
	return v.end() - mid;
}

#include <iostream>
#include <cassert>

int main()
{
	std::vector<int> v{ 5, 6, 4, 3, 2, 6, 7, 9, 3, 0, 0, 1, 2, 2, 3 };
	assert(hirsh(v) == 5);
	std::vector<int> v1{ 100 };
	assert(hirsh(v1) == 1);
	std::vector<int> v2{ 2, 2, 2, 2, 2 };
	assert(hirsh(v2) == 2);
	std::vector<int> v3{ 0, 1, 2, 5, 4, 3 };
	assert(hirsh(v3) == 3);
	// std::cout << hirsh(v1) << std::endl;
}
