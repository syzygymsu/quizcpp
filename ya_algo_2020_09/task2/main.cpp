// problems/B/

#include <iostream>
#include <string>


int main()
{
	int minSize = 4;
	std::string line;
	std::getline(std::cin, line);
	if (line.size() < 2) {
		std::cout << "-1" << std::endl;
	}
	char minFirst = 'z';
	char minSecond = 'z';
	int size = (int)line.size();
	for (int i = 1; i < size; ++i) {
		char prev = line[i - 1];
		char curr = line[i];
		if (curr == prev) {
			if (minSize > 2 || minFirst > prev) {
				minFirst = prev;
			}
			minSize = 2;
			++i;
			continue;
		}
		if (i + 1 < size && minSize > 2) {
			char next = line[i + 1];
			if (next == prev) {
				minSize = 3;
				if (minFirst > prev) {
					minFirst = prev;
					minSecond = curr;
				}
				else if (minFirst == prev && minSecond > curr) {
					minSecond = curr;
				}
			}
		}
	}
	if (minSize > 3) {
		std::cout << "-1" << std::endl;
	}
	else if (minSize == 3) {
		std::cout << minFirst << minSecond << minFirst  << std::endl;
	}
	else if (minSize == 2) {
		std::cout << minFirst << minFirst << std::endl;
	}
	return 0;
}
