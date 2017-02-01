#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> v2i;
typedef vector<v2i> v3i;
typedef vector<v3i> v4i;

typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

const int MOD = (int)1e9 + 7;

inline void SUM_MOD(int & a, int b) {
	a = (a + b) % MOD;
}

int solve_fast(const vi & number) {
	v4i dp(2, v3i(number.size(), v2i(10, vi(10)))); // dp[0/1][len][A][B]
	
	int last = number.size() - 1;
	int c = number[last];
	for (int a = 0;  a <= 9; ++a) {
		for (int b = 0; b <= 9; ++b) {
			int sum   = (a + b) % 10;
			int carry = (a + b) / 10;
			if (sum == c) {
				dp[carry][last][a][b] = 1;
			}
		}
	}

	for (int len = last - 1; len >= 0; --len) {
		int c = number[len];
		for (int a = 0; a <= 9; ++a) {
			for (int b = 0; b <= 9; ++b) {
				if ((a + b) % 10 == c) {
					for (int aa = 0; aa <= 9; ++aa) {
						for (int bb = 0; bb <= 9; ++bb) {
							if (aa != a && b != bb) {
								SUM_MOD(dp[(a + b) / 10][len][a][b], dp[0][len + 1][aa][bb]);
							}
						}
					}
				} else if ((a + b + 1) % 10 == c) {
					for (int aa = 0; aa <= 9; ++aa) {
						for (int bb = 0; bb <= 9; ++bb) {
							if (aa != a && b != bb) {
								SUM_MOD(dp[(a + b + 1) / 10][len][a][b], dp[1][len + 1][aa][bb]);
							}
						}
					}
				}
			}
		}
	}

	ll res = 0;
	for (int a = 1; a <= 9; ++a) {
		for (int b = 1; b <= 9; ++b) {
			res += dp[0][0][a][b];
		}
	}
	return res % MOD;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	string s;
	while (cin >> s) {
		vi number(s.size());
		for (int i = 0; i < (int)s.size(); ++i) {
			number[i] = s[i] - '0';
		}
		cout << solve_fast(number) << endl;
	}

	return 0;
}