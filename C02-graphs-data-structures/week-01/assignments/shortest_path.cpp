#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Node {
public:
	int parent = -1, distance = -1;
	vector<int> neighbors;
};

class Graph {
private:
	vector<Node*> adj_list;

	void printPath(int& source, int& destination) {
		if (source == destination) {
			cout << "Path: " << source;
			return;
		}
		printPath(source, adj_list[destination] -> parent);
		cout << " " << destination;
	}

	void bfs(int& source) {
		queue<int> q;
		q.push(source);
		adj_list[source] -> distance = 0;
		adj_list[source] -> parent = source;
		while (!q.empty()) {
			int f = q.front();
			q.pop();
			for (int& neighbor : adj_list[f] -> neighbors)
				if (adj_list[neighbor] -> parent == -1) {
					q.push(neighbor);
					adj_list[neighbor] -> distance = 1 + adj_list[f] -> distance;
					adj_list[neighbor] -> parent = f;
				}
		}
	}
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

	void shortestPath(int source, int destination) {
		bfs(source);
		printPath(source, destination);
		cout << endl << "Distance: " << adj_list[destination] -> distance << endl;
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

	g.shortestPath(1, 6);
	//g.shortestPath(6, 1);
	//g.shortestPath(1, 1);
}
