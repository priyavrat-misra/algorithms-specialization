#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <string>
#include <sstream>
using namespace std;
typedef pair<int, int> pii;

class Node {
public:
	int parent = -1;
	int dist = numeric_limits<int>::max();
	vector<pii> neighbors;
};

class Graph {
private:
	vector<Node*> adj_list;
public:
	Graph(int n) {
		while (n--)
			adj_list.push_back(new Node);
	}

	void addEdge(int& u, int& v, int& wgt) {
		adj_list[u] -> neighbors.push_back(make_pair(v, wgt));
	}

	void printPath(int& destination) {
		if (destination == -1)
			return;

		printPath(adj_list[destination] -> parent);
		cout << " -> " << destination + 1;
	}

	void getShortestPath(int destination) {
		cout << "Shortest Path:";
		printPath(destination);
		cout << endl << "Distance: " << adj_list[destination] -> dist << endl;
	}

	void dijkstra(int source) {
		adj_list[source] -> dist = 0;
		priority_queue<pii, vector<pii>, greater<pii>> pq;
		pq.push(make_pair(0, source));
		while (!pq.empty()) {
			int dist = pq.top().first;
			int prev = pq.top().second;
			pq.pop();
			for (pii& node : adj_list[prev] -> neighbors) {
				int& next = node.first;
				int& dist_next = node.second;
				if (dist + dist_next < adj_list[next] -> dist) {
					adj_list[next] -> dist = dist + dist_next;
					adj_list[next] -> parent = prev;
					pq.push(make_pair(dist + dist_next, next));
				}
			}
		}
	}

	~Graph() {
		for (Node*& node : adj_list)
			delete node;
	}
};

int main() {
	string line;
	getline(cin, line);
	Graph g(stoi(line));

	while (getline(cin, line)) {
		istringstream ss(line);
		string node;
		getline(ss, node, ' ');
		int u = stoi(node) - 1;
		while (getline(ss, node, ' ')) {
			int v = stoi(node) - 1;
			int comma = node.find(',');
			int wgt = stoi(node.substr(comma + 1, node.size() - comma));
			g.addEdge(u, v, wgt);
		}
	}

	g.dijkstra(0);
	int nodes[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
	for (int& node : nodes)
		g.getShortestPath(node - 1);
}
