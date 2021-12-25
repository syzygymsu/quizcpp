#include <iostream>
#include <limits>
#include <vector>
#include <cassert>

int main()
{
	std::vector<int> a;
	int size = a.size() - 1;
	assert(size == -1);
	std::cout << std::numeric_limits<int>::max() << std::endl;
	std::cout << std::numeric_limits<size_t>::max() << std::endl;
	size_t big = 2147483648;
	int test_int = big;
	assert(test_int < 0);
	std::cout << test_int << std::endl;
	return 0;
}
