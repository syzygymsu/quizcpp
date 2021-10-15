#include <iostream>
#include <vector>
#include <cassert>

int main()
{
	std::vector<int> a;
	int size = a.size() - 1;
	assert(size == -1);
	return 0;
}
