// problems/D/

#include <iostream>

int main()
{
	int n, m;
	std::cin >> n;
	std::cin >> m;
	int bsumm = 0;
	int asumm = 0;
	int aMax = -1;
	int aMaxIndFirst = -1;
	int aMaxIndLast = -1;
	int bMax = -1;
	int aFirst = -1;
	int aLast = -1;
	int bFirst = -1;
	int bLast = -1;
	for (int i = 0; i < n; ++i) {
		int c;
		std::cin >> c;
		asumm += c;
		if (c > aMax) {
			aMax = c;
			aMaxIndFirst = i;
			aMaxIndLast = i;
		}
		else if (c == aMax) {
			aMaxIndLast = i;
		}
		if (i == 0) {
			aFirst = c;
		} 
		if (i == n - 1) {
			aLast = c;
		}
	}
	for (int i = 0; i < m; ++i) {
		int c;
		std::cin >> c;
		bsumm += c;
		if (i == 0) {
			bFirst = c;
		}
		if (i == m - 1) {
			bLast = c;
		}
		if (c > bMax) {
			bMax = c;
		}
	}
	int small = bMax * (aMaxIndLast - aMaxIndFirst) + bsumm + bLast * (n - 1 - aMaxIndLast) + bFirst * aMaxIndFirst;
	int big = aMax * (m - 1) + asumm;
	long long res = big * (long long)1e9 + small;
	std::cout << res << std::endl;
	return 0;
}
