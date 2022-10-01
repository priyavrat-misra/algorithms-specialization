#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
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
	unordered_map<int, Node*> adj_list;
public:
	Graph(int n) {
		for (int i = 1; i <= n; ++i)
			adj_list[i] = new Node;
	}

	void addEdge(int& u, int& v, int& wgt) {
		adj_list[u] -> neighbors.push_back(make_pair(v, wgt));
	}

	void printPath(int& destination) {
		if (destination == -1)
			return;

		printPath(adj_list[destination] -> parent);
		cout << " -> " << destination;
	}

	void getShortestPath(int& destination) {
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
		for (pair<const int, Node*>& row : adj_list)
			delete row.second;
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
		int u = stoi(node);
		while (getline(ss, node, ' ')) {
			int v = stoi(node);
			int comma = node.find(',');
			int wgt = stoi(node.substr(comma + 1, node.size() - comma));
			g.addEdge(u, v, wgt);
		}
	}

	g.dijkstra(1);
	int nodes[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
	for (int& node : nodes)
		g.getShortestPath(node);
}
