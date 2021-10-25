#include <algorithm>
#include <iostream>
#include <vector>

unsigned int a, b;

unsigned int cur = 0; 
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

unsigned int nextRand32() {
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b;
}

void print(const std::vector<unsigned int>& v) {
	for (auto a : v) {
		std::cout << a << ' ';
	}
	std::cout << std::endl;
}

int main2()
{
	int n;
	std::cin >> n;
	std::vector<int> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i) {
		int x;
		std::cin >> x;
		v.push_back(x);
	}
	auto m = v.begin() + v.size() / 2;
	std::nth_element(v.begin(), m, v.end());
	int med = v[v.size() / 2];
	size_t sum = 0;
	for (size_t i = 0; i < v.size() / 2; ++i) {
		sum += med - v[i];
	}
	for (size_t i = v.size() / 2; i < v.size(); ++i) {
		sum += v[i] - med;
	}
	std::cout << sum << std::endl;
	return 0;
}

int main()
{
	int n;
	std::cin >> n;
	std::cin >> a;
	std::cin >> b;
	std::vector<unsigned int> v;
	v.reserve(n);
	for (int i = 0; i < n; ++i) {
		v.push_back(nextRand32());
	}
	auto m = v.begin() + v.size() / 2;
	std::nth_element(v.begin(), m, v.end());
	auto med = v[v.size() / 2];
	size_t sum = 0;
	for (size_t i = 0; i < v.size() / 2; ++i) {
		sum += med - v[i];
	}
	for (size_t i = v.size() / 2; i < v.size(); ++i) {
		sum += v[i] - med;
	}
	std::cout << sum << std::endl;
	return 0;
}
