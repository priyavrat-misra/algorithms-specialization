#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

void heapify(int* btree, int& parent, int& n) {
	int lchild = 2 * parent;
	int rchild = 2 * parent + 1;
	int largest = parent;
	if (lchild <= n && btree[lchild] > btree[parent])
		largest = lchild;
	if (rchild <= n && btree[rchild] > btree[largest])
		largest = rchild;
	if (largest != parent)
		swap(btree[parent], btree[largest]),
		heapify(btree, largest, n);
}

void buildHeap(int* btree, int& n) {
	int i = n / 2; // first non-leaf node
	while (i > 0)
		heapify(btree, i, n),
		--i;
}

int main() {
	int n;
	cin >> n;
	int* btree = new int[n + 1];
	for (int i = 1; i <= n; ++i)
		cin >> btree[i];

	buildHeap(btree, n);

	cout << "Max-Heapified tree:";
	for (int i = 1; i <= n; ++i)
		cout << " " << btree[i];
	
	cout << endl;
	delete[] btree;
}
