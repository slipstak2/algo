#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

inline bool correct(int x, int y, int n) {
	if (x < 0 || x >= n) return false;
	if (y < 0 || y >= n) return false;
	return true;
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int moveX[] = { -1, 0, 1, 0 };
	int moveY[] = { 0, -1, 0, 1 };
	const char BORDER = '1';

	int n, k;
	cin >> n >> k;
	vs field(n);
	for (int i = 0; i < n; ++i) {
		cin >> field[i];
	}

	vvvi dp(n, vvi(n, vi(k+1)));

	dp[0][0][0] = 1;
	for (int steps = 1; steps <= k; ++steps) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				for (int p = 0; p < 4; ++p) {
					int ii = i + moveX[p];
					int jj = j + moveY[p];
					if (correct(ii, jj, n) && field[ii][jj] != BORDER) {
						dp[i][j][steps] += dp[ii][jj][steps - 1];
					}
				}				
			}
		}
	}
	cout << dp[n - 1][n - 1][k];

	return 0;
}