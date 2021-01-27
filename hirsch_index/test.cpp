#include "test.h"
#include <functional>
#include <iostream>
#include <vector>

bool test(std::function<int(std::vector<int>&)> to_test)
{
	std::vector<std::pair<std::vector<int>, int>> tests = {
		{{}, 0 },
		{{ 0 }, 0 },
		{{ 0, 0}, 0 },
		{{ 0, 0, 0}, 0 },
		{{ 0, 1}, 1 },
		{{ 1, 2}, 1 },
		{{ 0, 1, 0}, 1 },
		{{ 2, 1}, 1 },
		{{ 1, 2}, 1 },
		{{ 0, 100}, 1 },
		{{ 1, 100}, 1 },
		{{ 100, 1}, 1 },
		{{ 100, 3}, 2 },
		{{ 5, 6, 4, 3, 2, 6, 7, 9, 3, 0, 0, 1, 2, 2, 3 }, 5},
		{{ 2, 2, 2, 2, 2 }, 2 },
		{{ 0, 1, 2, 5, 4, 3 }, 3 },
		{{ 0, 0, 0, 0, 0, 0 }, 0 },
		{{ 1, 2, 3 }, 2 },
		{{ 1, 1, 3 }, 1 },
		{{ 1, 3}, 1 },
		{{ 2, 1}, 1 },
		{{ 2, 2}, 2 },
		{{ 5, 3}, 2 },
	};

	return test(to_test, tests);
}

bool test(std::function<int(std::vector<int>&)> to_test, const std::vector<std::pair<std::vector<int>, int>>& tests) {
	bool has_error = false;
	for (int i = 0; i < tests.size(); ++i) {
		int expected = tests[i].second;
		auto data = tests[i].first;
		int result = to_test(data);
		if (result != expected) {
			const auto& initial_data = tests[i].first;
			std::cerr << "Error in test " << i << " expected " << expected << " but result " << result << " on (";
			for (auto s : initial_data) std::cerr << s << " ";
			std::cerr << "\b)" << std::endl;
			has_error = true;
		}
	}
	return !has_error;
}
