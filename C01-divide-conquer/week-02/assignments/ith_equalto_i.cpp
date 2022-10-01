// given a sorted array a, find if there exists some element
// whose value is same as it's index (a[i] == i)
#include <iostream>
using namespace std;

int find_i(int*& a, int lo, int hi) {
	if (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		if (mid == a[mid])
			return mid;
		else if (mid > a[mid])
			return find_i(a, mid + 1, hi);
		else
			return find_i(a, lo, mid - 1);
	}
	return -1;
}

int main() {
	int n;
	cout << "Enter size of the array: ";
	if (cin >> n && n > 0) {
		int* a = new int[n];
		cout << "Enter the elements in increasing order: ";
		for (int i = 0; i < n; ++i)
			cin >> a[i];

		int i = find_i(a, 0, n - 1);
		if (i > -1)
			cout << "Element found at index " << i << "." << endl;
		else
			cout << "No such element found." << endl;

		delete[] a;
	} else {
		cerr << "Size must be positive." << endl;
	}
}
