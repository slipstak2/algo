#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int INF = (int)1e9;

#define all(c) c.begin(),c.end()

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vi a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	vvi dp(n, vi(n, INF));

	for (int len = 0; len < 2; ++len) {
		for (int beg = 0; beg + len < n; ++beg) {
			dp[beg][beg + len] = 0;
		}
	}

	for (int len = 2; len < n; ++len) {
		for (int beg = 0; beg + len < n; ++beg){
			int end = beg + len;
			int &res = dp[beg][end];
			for (int mdl = beg + 1; mdl < end; ++mdl) {
				res = min(res, 
					dp[beg][mdl] + dp[mdl][end] + a[mdl] * (a[beg] + a[end]));
			}
		}
	}
	cout << dp[0][n - 1];
	return 0;
}