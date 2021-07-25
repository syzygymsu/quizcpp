#include <iostream>
#include <algorithm>

struct Point {
	int x, y;
};

int distance(const Point& a, const Point& b) {
	return std::max(std::abs(a.x - b.x), std::abs(a.y - b.y));
}

int main()
{
	int N;
	std::cin >> N;
	Point arr[3];
	for (int i = 0; i < 2; ++i) {
		Point p;
		std::cin >> p.x;
		std::cin >> p.y;
		arr[i] = p;
	}
	int max_dist = distance(arr[0], arr[1]);
	int prev_max = 0;
	for (int i = 2; i < N; ++i) {
		Point p;
		std::cin >> p.x;
		std::cin >> p.y;
		int dist1 = distance(p, arr[0]);
		int dist2 = distance(p, arr[1]);
		if (dist1 > max_dist) {
			if (dist2 > dist1) {
				prev_max = dist1;
				arr[0] = p;
			}
			else {
				prev_max = std::max(max_dist, dist2);
				arr[1] = p;
			}
		}
		else if (dist2 > max_dist) {
			arr[0] = p;
			prev_max = max_dist;
		}
		else {
			prev_max = std::max(prev_max, dist1);
			prev_max = std::max(prev_max, dist2);
		}
	}
	std::cout << prev_max << std::endl;
	return 0;
}
