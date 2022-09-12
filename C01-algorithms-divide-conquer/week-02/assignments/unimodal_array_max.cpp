// max element in an unimodal array with logarithmic running time
#include <iostream>
using namespace std;

int umax(const int* a, const int& n) {
	if (n > 1) {
		int m = n / 2;
		return a[m-1] < a[m] ? umax(a + m, n - m) : umax(a, m);
	} else {
		return *a;
	}
}

int main() {
	int n;
	cout << "Enter size of the array: ";
	if (cin >> n && n > 0) {
		int* a = new int[n];
		cout << "Enter the elements: ";
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		cout << "Max element: " << umax(a, n) << endl;
		delete[] a;
	} else {
		cerr << "Size must be positive." << endl;
	}
}
