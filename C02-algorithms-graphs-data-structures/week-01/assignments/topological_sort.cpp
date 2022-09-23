#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Node {
public:
	int label;
	bool is_visited = false;
	vector<int> neighbors;
};

class Graph {
private:
	int curr_label, num_nodes;
	vector<int> labels;
	unordered_map<int, Node*> adj_list;
public:
	Graph(int n) : curr_label(n), num_nodes(n), labels(n) {
		for (int node_no = 0; node_no < num_nodes; ++node_no)
			adj_list[node_no] = new Node;
	}

	void addEdge(int u, int v) {
		adj_list[u] -> neighbors.push_back(v);
	}

	void dfs(int& source) {
		adj_list[source] -> is_visited = true;
		for (int& neighbor : adj_list[source] -> neighbors)
			if (!adj_list[neighbor] -> is_visited)
				dfs(neighbor);
		
		labels[--curr_label] = source;
	}

	void dfsLoop() {
		for (int node_no = 0; node_no < num_nodes; ++node_no)
			if (!adj_list[node_no] -> is_visited)
				dfs(node_no);

		cout << "Topological Order:";
		for (int& label : labels)
			cout << " " << label;

		cout << endl;
	}

	~Graph() {
		for (pair<const int, Node*> row : adj_list)
			delete row.second;
	}
};

int main() {
	Graph g1(4);
	g1.addEdge(0, 1);
	g1.addEdge(0, 2);
	g1.addEdge(1, 3);
	g1.addEdge(2, 3);
	g1.dfsLoop();

	Graph g2(8);
	g2.addEdge(0, 3);
	g2.addEdge(1, 3);
	g2.addEdge(1, 4);
	g2.addEdge(2, 4);
	g2.addEdge(2, 7);
	g2.addEdge(3, 5);
	g2.addEdge(3, 6);
	g2.addEdge(3, 7);
	g2.addEdge(4, 6);
	g2.dfsLoop();
}
