#include <iostream>
#include <utility>
#include <set>

int main()
{
	int n;
	std::cin >> n;
	std::set<std::pair<int, int>> map;
	for (int i = 0; i < n; ++i) {
		int size;
		std::cin >> size;
		map.insert(std::make_pair(size, i + 1));
	}
	int k;
	std::cin >> k;
	for (int i = 0; i < k; ++i) {
		int new_count;
		std::cin >> new_count;
		if (map.empty()) {
			std::cout << "0" << std::endl;
			continue;
		}
		std::set<std::pair<int, int>>::iterator it;
		if (new_count >= 0) {
			it = map.begin();
		}
		else {
			it = map.end();
			--it;
		}
		auto updated = std::make_pair(it->first + new_count, it->second);
		map.erase(it);
		map.insert(updated);
		std::cout << updated.second << std::endl;
	}

    return 0;
}
