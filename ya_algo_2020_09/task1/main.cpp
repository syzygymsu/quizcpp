// problems/A/

#include <iostream>
#include <cstdint>

void setBitTomask(int n, uint32_t& mask) {
	mask = (1 << n) | mask;
}

int numberOfSetBits(uint32_t i)
{
	// Java: use int, and use >>> instead of >>
	// C or C++: use uint32_t
	i = i - ((i >> 1) & 0x55555555);
	i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
	return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}

int main()
{
	uint32_t mask = 0;
	for (int i = 0; i < 10; ++i) {
		int x;
		std::cin >> x;
		setBitTomask(x - 1, mask);
	}
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		uint32_t ticket = 0;
		for (int j = 0; j < 6; ++j) {
			int x;
			std::cin >> x;
			setBitTomask(x - 1, ticket);
		}
		uint32_t res = mask & ticket;
		int count = numberOfSetBits(res);
		if (count >= 3) {
			std::cout << "Lucky" << std::endl;
		}
		else {
			std::cout << "Unlucky" << std::endl;
		}

	}
	return 0;
}
