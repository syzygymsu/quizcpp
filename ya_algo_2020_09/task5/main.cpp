// problems/E/

#include <iostream>
// #include <fstream>
#include <string>
#include <vector>
#include <queue>

using namespace std;
struct Node {
	Node() {}
	Node(int i) : index{ i } {}
	int index;
	std::vector<Node> nodes;
};


pair<pair<int, int>, vector<int>> bfs(const std::vector<Node>& graph, int u, int markedZero)
{
	int V = graph.size();

	vector<int> pred(V);
	queue<int> q;
	q.push(u);
	std::vector<int> dis(V, -1);
	if (markedZero >= 0) {
		dis[markedZero] = 0;
	}
	dis[u] = 0;       //  distance of u from u will be 0 
	pred[u] = { u };  // I added this line

	while (!q.empty())
	{
		int t = q.front();
		q.pop();
		//  loop for all adjacent nodes of node-t 
		for (Node node : graph[t].nodes)
		{
			int v = node.index;
			// cout << "adjacent node:" << v << endl;
			// push node into queue only if it is not visited already 
			if (dis[v] == -1)
			{
				q.push(v);
				// make distance of v, one more than distance of t 
				dis[v] = dis[t] + 1;
				// cout << "parent of adjacent node:" << t << endl;
				pred[v] = t; // store the predecessor of v
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
	return make_pair(make_pair(nodeIdx, maxDis), pred);
}

struct LeftCenterRight {
	int l, cl, r, cr;
	LeftCenterRight(int _l, int  _cl, int _r, int _cr) : l{ _l }, cl{ _cl }, r{ _r }, cr{ _cr } {}
};

LeftCenterRight longestPathLength(const std::vector<Node>& graph, int u, int markedZero)
{
	pair<int, int> t1, t2;
	int V = graph.size();
	
	// first bfs to find one end point of longest path
	t1 = bfs(graph, u, markedZero).first;

	//  second bfs to find actual longest path
	auto res = bfs(graph, t1.first, markedZero); // or  pair<pair<int, int>, vector<int>> res
	t2 = res.first;

	int t = t2.first;
	for (int i = 0; i < (t2.second-1)/2; ++i) {
		// cout << t + 1 << " ";
		t = res.second[t];
	}
	// cout << t + 1 << " r " << t2.second << " " << u + 1<< endl;
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
	// fstream f("input.txt");
	func(std::cin);
	return 0;
}

pair<pair<int, int>, vector<int>> longest_branch(const std::vector<Node>& graph, int start, std::vector<bool>& visited) {
	int V = graph.size();
	vector<int> dis(V, -1);

	vector<int> pred(V);

	queue<int> q;
	while (!q.empty())
	{
		int t = q.front();       q.pop();

		//  loop for all adjacent nodes of node-t
		for (Node node : graph[t].nodes)
		{
			int v = node.index;
			// push node into queue only if
			// it is not visited already
			if (dis[v] == -1)
			{
				q.push(v);

				// make distance of v, one more
				// than distance of t
				dis[v] = dis[t] + 1;
				pred[v] = t;
			}
		}
	}
	int maxDis = 0;
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
	return make_pair(make_pair(nodeIdx, maxDis), pred);
}



int main2()
{
	int n;
	std::cin >> n;
	std::vector<Node> nodes(n);
	std::vector<bool> visited(n, false);
	std::vector<bool> visited2(n, false);
	std::vector<bool> visited3(n, false);
	std::vector<bool> visited4(n, false);
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
	auto longest_path = longest_branch(nodes, 0, visited);
	auto longest_path2 = longest_branch(nodes, longest_path.first.first, visited2);
	int nn = longest_path2.second.size() - 1;
	int split = nn / 2;

	visited3[longest_path2.second[n - split + 1]] = true;
	auto lp = longest_branch(nodes, longest_path2.second[0], visited3);
	int split_left = lp.second[(lp.second.size() - 1) / 2];
		//# права€ часть и центр
	visited4[longest_path2.second[split - 1]] = true;
	auto lp2 = longest_branch(nodes, longest_path2.second[longest_path2.second.size() - 1], visited4);
	int split_right = lp2.second[(lp2.second.size() - 1) / 2];
	if (split_left == split_right) {
		// # в случае симмитричного графа у нас может выбратьс€ центральный узел дважды
		split_right = lp2.second[(lp2.second.size() - 1) / 2 + 1];
	}
	std::cout << split_left + 1 << " " << split_right + 1 << std::endl;

	return 0;
}
