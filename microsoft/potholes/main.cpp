// https://habr.com/ru/post/648917/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

int max_fix(const std::string& road, int budget) {
	if (budget <= 1) {
		return 0;
	}
	int hole_len = 0;
	std::vector<int> lens;
	for (char c : road) {
		if (c == 'x') {
			++hole_len;
		}
		else {
			if (hole_len > 0) {
				if (hole_len >= budget - 1) {
					return budget - 1;
				}
				lens.push_back(hole_len);
				hole_len = 0;
			}
		}
	}
	if (hole_len > 0) {
		if (hole_len >= budget - 1) {
			return budget - 1;
		}
		lens.push_back(hole_len);
	}
	std::sort(lens.begin(), lens.end());
	int answer = 0;
	for (auto it = lens.rbegin(); it != lens.rend(); ++it) {
		if (*it < budget - 1) {
			answer += *it;
			budget -= (*it + 1);
		}
		else {
			answer += (budget - 1);
			break;
		}
	}
	return answer;
}

int main()
{
	assert(max_fix("...xxx..x....xxx.", 7) == 5);
	assert(max_fix("..xxxxx", 4) == 3);
	return 0;
}
