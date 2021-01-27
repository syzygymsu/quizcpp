#include "hirsh.h"
#include <algorithm>
#include <vector>

int hirsh(std::vector<int>& v) {
	auto begin = v.begin();
	auto end = v.end();
	while (true) {
		auto mid = begin + (end - begin) / 2;
		if (end - begin <= 0) {
			return v.end() - mid;
		}
		std::nth_element(begin, mid, end);
		int mid_el = *mid;
		if ((v.end() - mid == mid_el)) { // || (v.end() - mid - 1 == mid_el)) {
			return mid_el;
		}
		if (v.end() - mid < mid_el) {
			end = mid;
		}
		else {
			begin = mid + 1;
		}
	}
}
