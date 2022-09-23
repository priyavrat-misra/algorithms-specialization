#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Node {
public:
	bool is_visited = false;
	vector<int> neighbors;
};

class Graph {
private:
	unordered_map<int, Node*> adj_list;
public:
	Graph(int num_nodes) {
		for (int node_no = 0; node_no < num_nodes; ++node_no)
			adj_list[node_no] = new Node;
	}

	void addEdge(int u, int v, bool undir = true) {
		adj_list[u] -> neighbors.push_back(v);
		if (undir)
			adj_list[v] -> neighbors.push_back(u);
	}

	void dfs(int source) {
		cout << " " << source;
		adj_list[source] -> is_visited = true;
		for (int& neighbor : adj_list[source] -> neighbors)
			if (!adj_list[neighbor] -> is_visited)
				dfs(neighbor);
	}

	~Graph() {
		for (pair<const int, Node*>& row : adj_list)
			delete row.second;
	}
};

int main() {
	Graph g(7);
	g.addEdge(0, 1);
	g.addEdge(1, 2);
	g.addEdge(3, 5);
	g.addEdge(5, 6);
	g.addEdge(4, 5);
	g.addEdge(0, 4);
	g.addEdge(3, 4);
	g.addEdge(2, 3);
	g.dfs(1);
	cout << endl;
};
