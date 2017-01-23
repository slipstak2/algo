#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

const string INF_STRING = string(200 + 5, 'z');
string opens = "([";
string closes = ")]";

bool isPair(char open, char close) {
	size_t pos = opens.find(open);
	return (pos != -1 && closes[pos] == close);
}
// corrrect bracket sequence
string cbs(char c) {
	size_t pos = opens.find(c) ^ closes.find(c) ^ -1;
	return STR(opens[pos]) + STR(closes[pos]);
}

bool cmp(const string & a, const string & b) {
	return a.size() < b.size();
}

string solve(const string & s) {
	if (s.empty()) {
		return s;
	}
	vvs dp(s.size(), vs(s.size(), INF_STRING));

	for (int len = 0; len < (int)s.size(); ++len) {
		for (int beg = 0; beg + len < (int)s.size(); ++beg) {
			int end = beg + len;
			if (len == 0) {
				dp[beg][end] = cbs(s[beg]);
			}
			else if (len == 1) {
				dp[beg][end] = isPair(s[beg], s[end]) ? STR(s[beg]) + STR(s[end]) : cbs(s[beg]) + cbs(s[end]);
			}
			else {
				string & res = dp[beg][end];
				if (isPair(s[beg], s[end])) {
					res = min(res, s[beg] + dp[beg + 1][end - 1] + s[end], cmp);
				}
				for (int mdl = beg; mdl + 1 <= end; ++mdl) {
					res = min(res, dp[beg][mdl] + dp[mdl + 1][end], cmp);
				}
			}
		}
	}
	return dp[0][s.size() - 1];
}
int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	std::ios::sync_with_stdio(false);

	string s;
	while (getline(cin, s)) {
		cout << solve(s) << endl;
	}
	return 0;
}