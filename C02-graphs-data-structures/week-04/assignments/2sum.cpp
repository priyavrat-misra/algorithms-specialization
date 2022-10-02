#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
	int n;
	cin >> n;

	long long e;
	unordered_set<long long> s;
	while (n--)
		cin >> e, s.insert(e);

	int ans = 0;
	for (int target = -10000; target <= 10000; ++target) {
		for (auto& x : s) {
			long long y = target - x;
			if (s.count(y) && y != x) {
				++ans;
				break;
			}
		}
	}
	cout << ans << endl;
}
