// problems/C/

#include <iostream>

struct Point {
	Point() {};
	Point(int _x, int _y) : x{ _x }, y{ _y } {}
	int x;
	int y;
};

Point readCircle() {
	int r;
	int x;
	int y;
	std::cin >> r;
	std::cin >> x;
	std::cin >> y;
	Point p(x*2, y*2);
	return p;
}

Point readRectangle() {
	int x[4];
	int y[4];
	for (int i = 0; i < 4; ++i) {
		std::cin >> x[i];
		std::cin >> y[i];
	}
	Point p(x[0] + x[2], y[0] + y[2]);
	return p;
}

inline bool same(const Point& p1, const Point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

class Collinear {
private:
	Point p1;
	Point p2;
	int size = 0;
	bool isCollinear(const Point& p3) {
		return (p3.y - p2.y) * (p2.x - p1.x) == (p2.y - p1.y) * (p3.x - p2.x);
	}
public:
	bool check(Point p) {
		if (size == 0) {
			p1 = p;
			size = 1;
			return true;
		}
		if (size == 1) {
			if (!same(p1, p)) {
				p2 = p;
				size = 2;
			}
			return true;
		}

		if (size == 2) {
			return isCollinear(p);
		}
		return false;
	}

};

int main()
{
	int n;
	std::cin >> n;
	Collinear c;
	for (int i = 0; i < n; ++i) {
		int t;
		std::cin >> t;
		bool res = false;
		if (t == 0) {
			res = c.check(readCircle());
		}
		else if (t == 1) {
			res = c.check(readRectangle());
		}
		if (!res) {
			std::cout << "No" << std::endl;
			return 0;
		}
	}
	std::cout << "Yes" << std::endl;
	return 0;
}
