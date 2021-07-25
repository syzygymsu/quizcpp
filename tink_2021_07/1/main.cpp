#include <iostream>
#include <algorithm>

int main()
{
	int T;
	std::cin >> T;
	for (int i = 0; i < T; ++i) {
		int arr[3];
		for (int j = 0; j < 3; ++j) {
			int temp;
			std::cin >> temp;
			arr[j] = temp;
		}
		std::sort(arr, arr + 3);
		if (arr[1] - arr[0] == arr[2] - arr[1]) {
			std::cout << "Yes\n";
		}
		else {
			std::cout << "No\n";
		}
	}
	return 0;
}
