// given co-ordinates in a 2D plane,
// find the distance between the closest pair
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

void delete2d(int** a, int n) {
	// deletes a 2d array
	for (int i = 0; i < n; ++i)
		delete[] a[i];
	delete[] a;
}

void swap(int* a, int* b) {
	// swaps two arrays
	int t[] = {a[0], a[1]};
	a[0] = b[0];
	a[1] = b[1];
	b[0] = t[0];
	b[1] = t[1];
}

void qsort(int** points, int n, bool sort_y) {
	if (n > 1) {
		// randomly chooses a pivot element
		swap(points[rand() % n], points[0]);
		int i = 0, j = 1;
		while (j < n) {
			if (points[0][sort_y] < points[j][sort_y]) {
				++j;
			} else {
				swap(points[i+1], points[j]);
				++i;
				++j;
			}
		}
		swap(points[i], points[0]);

		qsort(points, i, sort_y);
		qsort(points + i + 1, n - i - 1, sort_y);
	}
}

inline double distance(int* p, int* q) {
	return sqrt((q[0] - p[0]) * (q[0] - p[0]) + (q[1] - p[1]) * (q[1] - p[1]));
}

double closest_pair(int** points, int n) {
	if (n == 2) { // base case
		return distance(points[0], points[1]);
	} else if (n == 3) { // base case
		double a = distance(points[0], points[1]);
		double b = distance(points[1], points[2]);
		double c = distance(points[2], points[0]);
		return min(a, min(b, c));
	} else {
		// divide
		int mid = n / 2;
		double dl = closest_pair(points, mid);
		double dr = closest_pair(points + mid, n - mid);
		double d = min(dl, dr);
		
		/* create an array of elements whose x co-ordinates
		 * are in range (mid point - d, mid point + d) */
		int** strip = new int*[n];
		int k = 0, s = 0;
		dl = points[mid][0] - d;
		dr = points[mid][0] + d;
		while (k < n) {
			if (points[k][0] > dl && points[k][0] < dr) {
				strip[s] = new int[2];
				strip[s][0] = points[k][0];
				strip[s][1] = points[k][1];
				++s;
			}
			++k;
		}

		qsort(strip, s, true); // sort strip wrt y co-ordinates
		
		// combine
		/* for every element in the strip check distance between
		 * the next 7 elements, if smaller, update min distance d */
		for (int i = 0; i < s - 1; ++i) {
			for (int j = i + 1; j < s && j < i + 8; ++j) {
				double t = distance(strip[i], strip[j]);
				if (t < d)
					d = t;
			}
		}

		delete2d(strip, s);

		return d;
	}
}

int main() {
	int n;
	cout << "Enter number of points: ";
	if (cin >> n && n > 1) {
		int** points = new int*[n];
		
		// get and store the inputs in a 2d array
		cout << "Enter the co-ordinates:" << endl;
		for (int i = 0; i < n; ++i) {
			points[i] = new int[2];
			cout << "x y: ";
			cin >> points[i][0] >> points[i][1];
		}

		srand(clock()); // sets seed for random no generation
		// sort the points wrt x co-ordinates inplace
		qsort(points, n, false);

		cout << "The distance between the closest pair is: "
			<< closest_pair(points, n) << endl;

		// deallocate array from heap
		delete2d(points, n);
	} else {
		cerr << "There must be at least 2 points." << endl;
	}
}
