// Kosaraju's Strongly Connected Components Algorithm
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

class Node {
public:
	bool is_visited = false;
	vector<int> children;
	vector<int> parents;
};

class Graph {
private:
	int num_nodes, curr_rank;
	vector<int> topo_order;
	priority_queue<int, vector<int>, greater<int>> top5_scc;
	unordered_map<int, Node*> adj_list;

	void dfs(int& source) {
		adj_list[source] -> is_visited = true;
		for (int& node : adj_list[source] -> parents)
			if (!adj_list[node] -> is_visited)
				dfs(node);

		topo_order[--curr_rank] = source;
	}

	void topoSort() {
		for (int node = 1; node <= num_nodes; ++node)
			if (!adj_list[node] -> is_visited)
				dfs(node);

	}

	void dfsSCC(int& source, int& n) {
		++n;
		adj_list[source] -> is_visited = false;
		for (int& node : adj_list[source] -> children)
			if (adj_list[node] -> is_visited)
				dfsSCC(node, n);
	}
public:
	Graph(int n) : num_nodes(n), curr_rank(n), topo_order(n) {
		for (int node = 1; node <= num_nodes; ++node)
			adj_list[node] = new Node;
	}

	void addEdge(int u, int v) {
		adj_list[u] -> children.push_back(v);
		adj_list[v] -> parents.push_back(u);
	}

	void kosarajuAlgo() {
		topoSort();
		for (int& node : topo_order)
			if (adj_list[node] -> is_visited) {
				int n = 0;
				dfsSCC(node, n);
				top5_scc.push(n);
				if (top5_scc.size() > 5)
					top5_scc.pop();
			}

		while (!top5_scc.empty())
			cout << top5_scc.top() << endl, top5_scc.pop();
	}

	~Graph() {
		for (pair<const int, Node*>& row : adj_list)
			delete row.second;
	}
};

int main() {
	int v, e;
	cin >> v >> e;
	Graph g(v);
	while (e--) {
		int u, v;
		cin >> u >> v;
		g.addEdge(u, v);
	}

	g.kosarajuAlgo();
}
