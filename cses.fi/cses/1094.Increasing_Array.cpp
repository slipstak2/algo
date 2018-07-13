#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll>  vll;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(0);

	int n;
	cin >> n;
	vll a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	ll cnt = 0;
	for (int i = 1; i < n; ++i) {
		if (a[i - 1] > a[i]) {
			cnt += a[i - 1] - a[i];
			a[i] = a[i - 1];
		}
	}
	cout << cnt;

	return 0;
}