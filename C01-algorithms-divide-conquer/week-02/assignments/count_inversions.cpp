// count inversions in an array
#include <iostream>
using namespace std;

int* slice(int* a, int start, int end) {
	int* s = new int[end-start];
	for (int i = start; i < end; ++i)
		s[i-start] = a[i];

	return s;
}

unsigned mergeNcount(int* a, int* left, int* right, int ls, int rs) {
	int i = 0, j = 0;
	unsigned c = 0;
	while (i < ls && j < rs) {
		if (left[i] > right[j])
			a[i+j] = right[j], ++j, c += (ls - i);
		else
			a[i+j] = left[i], ++i;
	}

	while (i < ls)
		a[i+j] = left[i], ++i;
	
	while (j < rs)
		a[i+j] = right[j], ++j;

	delete[] left;
	delete[] right;
	
	return c;
}

unsigned divideNsort(int* a, int n) {
	if (n == 1)
		return 0;

	unsigned c = 0;
	int mid = n / 2;
	int* left = slice(a, 0, mid);
	int* right = slice(a, mid, n);
	
	c += divideNsort(left, mid);
	c += divideNsort(right, n - mid);
	c += mergeNcount(a, left, right, mid, n - mid);
	return c;
}

int main() {
	int n;
	cout << "Enter size of the array: ";
	if (cin >> n && n > 0) {
		int* a = new int[n];
		cout << "Enter the elements: ";
		for (int i = 0; i < n; ++i)
			cin >> a[i];

		cout << "Number of inversions: " << divideNsort(a, n) << endl;
		delete[] a;
	} else {
		cerr << "Size must be positive." << std::endl;
	}
}
