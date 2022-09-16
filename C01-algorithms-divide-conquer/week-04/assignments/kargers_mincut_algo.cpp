#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <climits>
#include <cstdlib>
using namespace std;

class Graph {
	private:
		int num_nodes;
		vector<int> nodes;
		vector<vector<int>> adj_matrix;
	public:
		Graph(int n) : num_nodes(n), adj_matrix(n, vector<int>(n, 0)), nodes(n) {
			for (int i = 0; i < num_nodes; ++i)
				nodes[i] = i;
		}

		void setNeighbors(int& node, string& neighbors) {
			istringstream ss(neighbors);
			string neighbor;
			while (getline(ss, neighbor, ' '))
				adj_matrix[node][stoi(neighbor)-1] += 1;
		}

		void removeSelfLoops() {
			for (int i = 0; i < num_nodes; ++i)
				adj_matrix[i][i] = 0;
		}

		void mergeNodes(int& u, int& v) {
			for (int i = 0; i < num_nodes; ++i) {
				adj_matrix[i][v] += adj_matrix[i][u];
				adj_matrix[v][i] = adj_matrix[i][v];
				adj_matrix[i][u] = adj_matrix[u][i] = 0;
			}
		}

		int kargersAlgo() {
			removeSelfLoops();
			for (int i = num_nodes; i > 2; --i) {
				int n = nodes.size();
				int u, v;
				do {
					u = nodes[rand() % n];
					v = nodes[rand() % n];
				} while (u == -1 || v == -1 || !adj_matrix[u][v]);
				mergeNodes(u, v);
				nodes[u] = -1;
				removeSelfLoops();
			}

			int i = 0;
			while (i < num_nodes && nodes[i] == -1)
				++i;
			int u = nodes[i];

			++i;
			while (i < num_nodes && nodes[i] == -1)
				++i;
			int v = nodes[i];

			return adj_matrix[u][v];
		}
};

int main() {
	int n;
	cout << "Enter the number of vertices: ";
	if (cin >> n && n > 0) {
		Graph graph(n);
		cout << "Enter 'Adjacent List' with the following format." << endl
			<< "(1st node's neighbors in 1st line, 2nd's in 2nd line, ...)" << endl
			<< "Note: Each node's neighbors should be space-separated." << endl;

		cin.get();
		for (int i = 0; i < n; ++i) {
			string s;
			getline(cin, s);
			graph.setNeighbors(i, s);
		}

		int runs = n * n * log2(n);
		int min_cuts = INT_MAX;
		for (int i = 0; i < runs; ++i) {
			srand(clock());
			//if (!(i % 1000))
			//	cout << i << " / " << runs << ": " << min_cuts << endl; 
			Graph tgraph = graph;
			min_cuts = min(min_cuts, tgraph.kargersAlgo());
		}
		cout << min_cuts << endl;
	} else {
		cerr << "Invalid number of vertices." << endl;
	}
}
