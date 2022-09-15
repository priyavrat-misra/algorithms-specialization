#include <iostream>
using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

int medianOfThree(int*& a, int& n) {
	int mid = n % 2 ? n / 2 : n / 2 - 1;
	if ((a[0] > a[mid]) ^ (a[0] > a[n-1]))
		return 0;
	else if ((a[mid] < a[0]) ^ (a[mid] < a[n-1]))
		return mid;
	else
		return n - 1;
}

int partition(int* a, int& n) {
	int i = 0, j = 1;
	// use median(first, mid, last) as pivot
	swap(a[medianOfThree(a, n)], a[0]);
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
