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
		vector<vector<int>> adj_matrix;
	public:
		Graph(int n) : num_nodes(n), adj_matrix(n, vector<int>(n, 0)) {}

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
				int u, v;
				do {
					u = rand() % num_nodes;
					v = rand() % num_nodes;
				} while (!adj_matrix[u][v]);
				mergeNodes(u, v);
				removeSelfLoops();
			}
			for (int i = 0; i < num_nodes - 1; ++i)
				for (int j = i + 1; j < num_nodes; ++j)
					if (adj_matrix[i][j])
						return adj_matrix[i][j];

			return 0;
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
		int min_cut = INT_MAX;
		for (int i = 0; i < runs; ++i) {
			srand(clock());
			//if (!(i % 1000))
			//	cout << i << " / " << runs << ": " << min_cut << endl; 
			Graph tgraph = graph;
			min_cut = min(min_cut, tgraph.kargersAlgo());
		}
		cout << min_cut << endl;
	} else {
		cerr << "Invalid number of vertices." << endl;
	}
}
