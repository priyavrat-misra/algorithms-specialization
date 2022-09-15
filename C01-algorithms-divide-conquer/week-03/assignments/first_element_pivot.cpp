#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

int partition(int* a, int& n) {
	int i = 0, j = 1;
	// using 1st element as pivot
	while (j < n) {
		if (a[j] < a[0])
			swap(a[i+1], a[j]), ++i, ++j;
		else
			++j;
	}
	swap(a[i], a[0]);
	return i;
}

void qsort(int* a, int n, int& ans) {
	if (n > 1) {
		int pivot = partition(a, n);
		ans += n - 1;
		qsort(a, pivot, ans);
		qsort(a + pivot + 1, n - pivot - 1, ans);
	}
}

int main() {
	int n, ans = 0;
	cin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> a[i];

	qsort(a, n, ans);
	cout << ans << endl;
	delete[] a;
}
