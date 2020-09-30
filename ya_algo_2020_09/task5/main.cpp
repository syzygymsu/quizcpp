// problems/E/

// #include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

struct Node {
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
	int maxDis = 0;
	int nodeIdx = u;
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
				maxDis = dis[t] + 1;
				dis[v] = maxDis;
				pred[v] = t;
				nodeIdx = v;
			}
		}
	}
	return std::make_pair(std::make_pair(nodeIdx, maxDis), pred);
}


std::pair<int, int> getCenter(const std::vector<Node>& graph, int u, int markedZero)
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
	return { t, res.second[t] };
}

void func(std::istream& f, std::ostream& out) {
	int n;
	f >> n;
	std::vector<Node> nodes;
	nodes.reserve(n);
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

	auto big = getCenter(nodes, 0, -1);
	auto left = getCenter(nodes, big.first, big.second);
	auto right = getCenter(nodes, big.second, big.first);
	out << left.second + 1 << " " << right.second + 1 << std::endl;
}

int main() {
	std::ifstream f("input.txt");
	std::ofstream out("output.txt");
	func(f, out);
	// func(std::cin, std::cout);
	return 0;
}
