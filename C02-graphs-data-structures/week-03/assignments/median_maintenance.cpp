#include <iostream>
#include <queue>
using namespace std;

int main() {
	priority_queue<int> hlow;
	priority_queue<int, vector<int>, greater<int>> hhigh;
	int n, hls = 0, hhs = 0, x, ans;
	cin >> n >> x;
	hlow.push(x);
	++hls;
	ans = x % 10000;

	while (--n) {
		cin >> x;
		if (x > hlow.top())
			hhigh.push(x), ++hhs;
		else
			hlow.push(x), ++hls;

		if (hls > hhs) {
			hhigh.push(hlow.top());
			hlow.pop();
			++hhs, --hls;
		}

		if (hls < hhs) {
			hlow.push(hhigh.top());
			hhigh.pop();
			--hhs, ++hls;
		}

		ans += hlow.top();
		ans %= 10000;
	}

	cout << ans << endl;
}
