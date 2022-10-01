#include <cstdlib>
#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

int partition(int* a, int& n) {
	// randomly chooses a pivot element
	swap(a[rand() % n], a[0]);
	int i = 0, j = 1;
	while (j < n) {
		if (a[0] > a[j])
			swap(a[i+1], a[j]), ++i, ++j;
		else
			++j;
	}

	swap(a[i], a[0]);
	return i;
}

void qsort(int* a, int n) {
	if (n > 1) {
		int pivot = partition(a, n);
		qsort(a, pivot);
		qsort(a + pivot + 1, n - pivot - 1);
	}
}

int main() {
	int n;
	cout << "Enter size of the array: ";
	if (cin >> n && n > 0) {
		int *a = new int[n];
		cout << "Enter the elements: ";
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		
		srand(clock()); // sets seed for random no generation
		qsort(a, n);
		cout << "The elements in sorted order:";
		for (int i = 0; i < n; ++i)
			cout << " " << a[i];
		
		cout << endl;
		delete[] a;
	} else {
		cerr << "Invalid array size." << endl;
	}
}
