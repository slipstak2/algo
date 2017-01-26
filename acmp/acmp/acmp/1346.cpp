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
typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

const string INF_STRING = string(200 + 5, 'z');

bool cmp(const string & a, const string & b) {
	return a.size() < b.size();
}

void tryCompress(const string & s, const vvs & dp, string & res, int beg, int end, int len) {
	for (int sublen = 1; sublen <= len / 2; ++sublen) {
		if (len % sublen == 0) {
			bool isOK = true;
			for (int pos = beg; pos < beg + sublen && isOK; ++pos) {
				for (int mul = 1; pos + sublen * mul <= end && isOK; ++mul) {
					if (s[pos] != s[pos + sublen * mul]) {
						isOK = false;
					}
				}
			}
			if (isOK) {
				stringstream ss;
				ss << len / sublen << '(' << dp[beg][beg+sublen-1] << ')';
				res = min(res, ss.str(), cmp);
			}
		}
	}
}

string solve(const string & s) {

	int n = s.size();
	vvs dp(n, vs(n));
	
	for (int len = 1; len <= n; ++len) {
		for (int beg = 0; beg + len - 1 < n; ++beg) {
			int end = beg + len - 1;
			dp[beg][end] = s.substr(beg, len);
			string & res = dp[beg][end];
			if (len == 1) {
				dp[beg][end] = STR(s[beg]);
			} else {
				tryCompress(s, dp, res, beg, end, len);
				for (int mid = beg; mid < end; ++mid) {
					res = min(res, dp[beg][mid] + dp[mid + 1][end], cmp);
				}
			}
		}
	}
	return dp[0][n-1];
}

int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::ios::sync_with_stdio(false);

	string s;
	while (cin >> s) {
		cout << solve(s) << endl;
	}
	return 0;
}