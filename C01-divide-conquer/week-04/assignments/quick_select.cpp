#include <iostream>
#include <cstdlib>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

int partition(int* a, int& n) {
	int i = 0, j = 1;
	swap(a[rand() % n], a[0]);
	while (j < n) {
		if (a[j] < a[0])
			swap(a[i+1], a[j]), ++i, ++j;
		else
			++j;
	}
	swap(a[i], a[0]);
	return i;
}

int qselect(int* a, int n, int k) {
	if (n == 1)
		return a[0];
	
	int pivot = partition(a, n);
	if (pivot > k)
		return qselect(a, pivot, k);
	else if (pivot < k)
		return qselect(a + pivot + 1, n - pivot - 1, k - pivot - 1);
	else
		return a[pivot];
}

int main() {
	int n;
	cout << "Enter the size of the array: ";
	if (cin >> n && n > 0) {
		int* a = new int[n];
		cout << "Enter the elements: ";
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		
		int k;
		while (true) {
			cout << "Enter the required smallest element: ";
			if (cin >> k && k > 0 && k <= n)
				break;
			else
				cerr << "Out of range. Try Again." << endl;
		}
		srand(clock());
		cout << k << "th smallest element is: " << qselect(a, n, k - 1) << endl;
		delete[] a;
	} else {
		cerr << "Invalid array size." << endl;
	}
}
