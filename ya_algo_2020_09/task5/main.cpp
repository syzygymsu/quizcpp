// problems/E/

#include <iostream>
// #include <fstream>
#include <string>
#include <vector>
#include <queue>

struct Node {
	Node() {}
	Node(int i) : index{ i } {}
	int index;
	std::vector<Node> nodes;
};

std::pair<std::pair<int, int>, std::vector<int>> bfs(const std::vector<Node>& graph, int u, int markedZero)
{
	int V = graph.size();

	std::vector<int> pred(V);
	std::queue<int> q;
	q.push(u);
	std::vector<int> dis(V, -1);
	if (markedZero >= 0) {
		dis[markedZero] = 0;
	}
	dis[u] = 0;      
	pred[u] = u; 

	while (!q.empty())
	{
		int t = q.front();
		q.pop();
		for (Node node : graph[t].nodes)
		{
			int v = node.index;
			if (dis[v] == -1)
			{
				q.push(v);
				dis[v] = dis[t] + 1;
				pred[v] = t;
			}
		}
	}
	int maxDis = -1;
	int nodeIdx;
	//  get farthest node distance and its index 
	for (int i = 0; i < V; i++)
	{
		if (dis[i] > maxDis)
		{
			maxDis = dis[i];
			nodeIdx = i;
		}
	}
	return std::make_pair(std::make_pair(nodeIdx, maxDis), pred);
}

struct LeftCenterRight {
	int l, cl, r, cr;
	LeftCenterRight(int _l, int  _cl, int _r, int _cr) : l{ _l }, cl{ _cl }, r{ _r }, cr{ _cr } {}
};

LeftCenterRight longestPathLength(const std::vector<Node>& graph, int u, int markedZero)
{
	std::pair<int, int> t1, t2;
	int V = graph.size();	
	t1 = bfs(graph, u, markedZero).first;

	auto res = bfs(graph, t1.first, markedZero);
	t2 = res.first;

	int t = t2.first;
	for (int i = 0; i < (t2.second-1)/2; ++i) {
		t = res.second[t];
	}
	int l = t;
	t = res.second[t];
	if (t2.second % 2 == 1) {
		return LeftCenterRight(l, l, t, t);
	}
	int cl = t;
	t = res.second[t];
	int r = t;
	return LeftCenterRight(l, cl, r, cl);
}

int func(std::istream& f) {
	int n;
	f >> n;
	std::vector<Node> nodes(n);

	for (int i = 0; i < n; ++i) {
		nodes.push_back(Node(i));
	}

	for (int i = 0; i < n - 1; ++i) {
		int first, second;
		f >> first;
		f >> second;
		nodes[first - 1].nodes.push_back(second - 1);
		nodes[second - 1].nodes.push_back(first - 1);
	}
	if (n <= 3) {
		std::cout << "1 2" << std::endl;
		return 0;
	}

	LeftCenterRight big = longestPathLength(nodes, 0, -1);
	LeftCenterRight left = longestPathLength(nodes, big.cl, big.r);
	LeftCenterRight right = longestPathLength(nodes, big.cr, big.l);
	if (left.cl != right.cr) {
		std::cout << left.cl + 1 << " " << right.cr + 1 << std::endl;
	}
	else if (left.cl != right.r) {
		std::cout << left.cl + 1 << " " << right.l + 1 << std::endl;
	}
	else {
		std::cout << left.cl + 1 << " " << right.r + 1 << std::endl;
	}
	return 0;
}


int main() {
	// std::fstream f("input.txt");
	func(std::cin);
	return 0;
}
