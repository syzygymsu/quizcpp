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

int main()
{
	std::vector<std::pair<std::vector<int>, int>> tests = {
		{{ 5, 6, 4, 3, 2, 6, 7, 9, 3, 0, 0, 1, 2, 2, 3 }, 5},
		{{ 100 }, 1},
		{{ 2, 2, 2, 2, 2 }, 2 },
		{{ 0, 1, 2, 5, 4, 3 }, 3 },
		{{ 0, 0, 0, 0, 0, 0 }, 0 },
		{{ 1, 2, 3 }, 2 },
		{{ 1, 1, 3 }, 1 },
	};
	for (int i = 0; i < tests.size(); ++i) {
		int expected = tests[i].second;
		auto data = tests[i].first;
		int result = hirsh(data);
		bool has_error = false;
		if (result != expected) {
			const auto& initial_data = tests[i].first;
			std::cerr << "Error in test " << i << " expected " << expected << " but result " << result << " on (";
			for (auto s : initial_data) std::cerr << s << " ";
			std::cerr << "\b)" << std::endl;
			has_error = true;
		}
		if (has_error) {
			return 1;
		}
	}
	return 0;
}
