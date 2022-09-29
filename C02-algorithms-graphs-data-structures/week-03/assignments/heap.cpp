#include <iostream>
#include <vector>
using namespace std;

class Heap {
private:
	int size;
	vector<int> btree;

	void swap(int& a, int& b) {
		int t = a;
		a = b;
		b = t;
	}

	void heapify(int& parent) {
		int lchild = 2 * parent;
		int rchild = 2 * parent + 1;
		int smallest = parent;

		if (lchild <= size && btree[lchild] < btree[parent])
			smallest = lchild;
		if (rchild <= size && btree[rchild] < btree[smallest])
			smallest = rchild;
		if (smallest != parent)
			swap(btree[smallest], btree[parent]),
			heapify(smallest);
	}

	void buildHeap() {
		int i = size / 2;
		while (i > 0)
			heapify(i),
			--i;
	}
public:
	Heap() : btree(1), size(0) {}

	Heap(vector<int> arr) : btree(1) {
		this -> size = arr.size();
		btree.insert(btree.end(), arr.begin(), arr.end());
		buildHeap();
	}

	void push(int x) {
		btree.push_back(x);
		++size;
		int parent = size / 2;
		int child = size;
		while (parent && btree[parent] > btree[child])
			swap(btree[parent], btree[child]),
			child = parent, parent /= 2;
	}

	void pop() {
		swap(btree[1], btree[size]);
		--size;
		btree.pop_back();
		int parent = 1;
		int lchild = 2;
		int rchild = 3;
		while (lchild <= size) {
			if (lchild == size) {
				if (btree[parent] > btree[lchild])
					swap(btree[parent], btree[lchild]);
				break;
			} else {
				if (btree[parent] < btree[lchild] && btree[parent] < btree[rchild])
					break;
			}

			int smallest = btree[lchild] < btree[rchild] ? lchild : rchild;
			swap(btree[parent], btree[smallest]);
			parent = smallest;
			lchild = 2 * parent;
			rchild = 2 * parent + 1;
		}
	}

	int top() {
		if (!empty())
			return btree[1];

		return -1;
	}

	bool empty() {
		return size == 0;
	}
};

int main() {
	Heap h1({11, 7, 4, 9, 12, 8, 13, 4, 4, 10, 9, 5});

	while (!h1.empty()) {
		cout << " " << h1.top();
		h1.pop();
	}
	cout << endl;

	Heap h2;
	h2.push(11);
	h2.push(7);
	h2.push(4);
	h2.push(9);
	h2.push(12);
	h2.push(8);
	h2.push(13);
	h2.push(4);
	h2.push(4);
	h2.push(10);
	h2.push(9);
	h2.push(5);

	while (!h2.empty()) {
		cout << " " << h2.top();
		h2.pop();
	}
	cout << endl;
}
