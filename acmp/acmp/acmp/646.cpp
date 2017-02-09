#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;
	vi a(n);
	{
		ll sum = 0;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
			sum += a[i];
		}
		if (sum < 2 * k) {
			cout << 0;
			return 0;
		}
	}

	vll dp(n * k);
	dp[0] = 1;

	for (int i = 0; i < n; ++i) {
		for (int cnt = k - 1; cnt - a[i] >= 0; --cnt) {
			dp[cnt] += dp[cnt - a[i]];
		}
	}

	ll sum = accumulate(dp.begin(), dp.end(), 0LL);
	cout << ((1LL << n) - 2 * sum);
	return 0;
}