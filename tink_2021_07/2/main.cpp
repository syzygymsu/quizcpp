#include <iostream>
#include <string>
#include <algorithm>

int main()
{
	std::string S, T;
	std::getline(std::cin, S);
	std::getline(std::cin, T);
	int min_diff = T.size() + 1;
	for (int i = 0; i <= S.size() - T.size(); ++i) {
		int diff = 0;
		for (int j = 0; j < T.size(); ++j) {
			if (T[j] != S[j + i]) ++diff;
		}
		if (diff < min_diff) {
			min_diff = diff;
			if (min_diff == 0) break;
		}
	}
	std::cout << min_diff;
	return 0;
}
