#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <stack>
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
typedef vector<ll> vll;
typedef vector<vll> v2ll;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

typedef pair<int,int> matrix;
#define x first
#define y second

const int INF = (int)1e9;
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<matrix> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i].x >> a[i].y;
	}

	v2ll dp(n, vll(n, INF));

	for (int i = 0; i < n; ++i) {
		dp[i][i] = 0;
	}

	for (int len = 2; len <= n; ++len) {
		for (int beg = 0; beg + len - 1 < n; ++beg) {
			int end = beg + len - 1;
			ll & res = dp[beg][end];
			for (int mdl = beg; mdl < end; ++mdl) {
				// [beg, mdl] [mdl + 1, end]
				res = min(res, 
					a[beg].x * a[end].y + dp[beg][mdl] + dp[mdl + 1][end]);
			}
		}
	}
	cout << dp[0][n-1];
	return 0;
}