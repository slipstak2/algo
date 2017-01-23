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

#define all(c) c.begin(),c.end()

const int INF = (int)1e9;
string opens =  "([{";
string closes = ")]}";

bool isPair(char open, char close) {
	int pos = opens.find(open);
	return (pos != -1 && closes[pos] == close);
}
int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::ios::sync_with_stdio(false);

	string s;
	cin >> s;
	vvi dp(s.size(), vi(s.size(), INF));

	for (int len = 0; len < (int)s.size(); ++len) {
		for (int beg = 0; beg + len < (int)s.size(); ++beg) {
			int end = beg + len;
			if (len == 0) {
				dp[beg][end] = 1;
			} else if (len == 1) {
				dp[beg][end] = isPair(s[beg], s[end]) ? 0 : 2;
			} else {
				int & res = dp[beg][end];
				if (isPair(s[beg], s[end])) {
					res = min(res, dp[beg + 1][end - 1]);
				}
				for (int mdl = beg; mdl + 1 <= end; ++mdl) {
					res = min(res, dp[beg][mdl] + dp[mdl + 1][end]);
				}
			}
		}
	}
	cout << dp[0][s.size()-1];

	return 0;
}