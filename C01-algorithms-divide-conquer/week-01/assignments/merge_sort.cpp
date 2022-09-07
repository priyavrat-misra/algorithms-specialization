#include <iostream>
using namespace std;

int* slice(int* a, int start, int end) {
	int* sl = new int[end - start];
	for (int i = start; i < end; ++i)
		sl[i - start] = a[i];
	
	return sl;
}

void merge(int* a, int* left, int* right, int ls, int rs) {
	int i = 0, j = 0;
	while (i < ls && j < rs) {
		if (left[i] < right[j])
			a[i+j] = left[i], ++i;
		else
			a[i+j] = right[j], ++j;
	}
	while (i < ls)
		a[i+j] = left[i], ++i;

	while (j < rs)
		a[i+j] = right[j], ++j;

	delete[] left;
	delete[] right;
}

void msort(int* a, int n) {
	if (n > 1) {
		int mid = n / 2;
		int* left = slice(a, 0, mid);
		int* right = slice(a, mid, n);

		msort(left, mid);
		msort(right, n - mid);
		merge(a, left, right, mid, n - mid);
	}
}

int main() {
	int n;
	if (cin >> n && n > 0) {
		int *a = new int[n];
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		
		msort(a, n);
		for (int i = 0; i < n; ++i)
			cout << " " << a[i];
		
		cout << endl;
		delete[] a;
	} else {
		cerr << "Invalid array size." << endl;
	}
}
