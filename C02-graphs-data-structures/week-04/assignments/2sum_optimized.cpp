#include <iostream>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	long long e;
	set<long long> s;
	while (n--)
		cin >> e, s.insert(e);

	bitset<20001> range;
	for (auto& x : s) {
		set<long long>::iterator l = s.lower_bound(-10000 - x);
		set<long long>::iterator r = s.upper_bound(10000 - x);
		while (l != r) {
			if (*l == x) {
				++l;
				continue;
			}
			long long sum = *l + x;
			assert(sum >= -10000 && sum <= 10000);
			range.set(sum + 10000);
			++l;
		}
	}
	cout << range.count() << endl;
}
