// problems/E/

#include <iostream>
#include <string>
#include <vector>

struct Node {
	Node() {}
	Node(int i) : index{ i } {}
	int index;
	std::vector<Node> nodes;
};


int main()
{
	int n;
	std::cin >> n;
	std::vector<Node> nodes(n);
	for (int i = 0; i < n; ++i) {
		nodes.push_back(Node(i));
	}
	for (int i = 0; i < n-1; ++i) {
		int first, second;
		std::cin >> first;
		std::cin >> second;
		nodes[first - 1].nodes.push_back(second - 1);
		nodes[second - 1].nodes.push_back(first - 1);
	}
	if (n <= 3) {
		std::cout << "1 2" << std::endl;
		return 0;
	}

	return 0;
}
