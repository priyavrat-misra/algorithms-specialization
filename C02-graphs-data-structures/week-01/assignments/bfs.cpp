#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
	bool is_visited = false;
	vector<int> neighbors;
};

class Graph {
private:
	vector<Node*> adj_list;
public:
	Graph(int num_nodes) {
		while (num_nodes--)
			adj_list.push_back(new Node);
	}

	void addEdge(int u, int v, bool undir = true) {
		adj_list[u] -> neighbors.push_back(v);
		if (undir)
			adj_list[v] -> neighbors.push_back(u);
	}

	void bfs(int source) {
		queue<int> q;
		q.push(source);
		adj_list[source] -> is_visited = true;
		
		while (!q.empty()) {
			int f = q.front();
			cout << " " << f;
			q.pop();
			for (int& neighbor : adj_list[f] -> neighbors)
				if (!adj_list[neighbor] -> is_visited) {
					q.push(neighbor);
					adj_list[neighbor] -> is_visited = true;
				}
		}
	}

	~Graph() {
		for (Node*& node : adj_list)
			delete node;
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
	g.bfs(1);
	cout << endl;
}
