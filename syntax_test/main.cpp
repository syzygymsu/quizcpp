#include <iostream>

int main()
{
    int n = 5;
	for (int i = 0; i < n; ++i) {
        std::cout << i << " b"[i == n-1];
    }
	return 0;
}
