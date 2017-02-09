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
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

const string A = "aAbB";
const string B = "AaBb";

char Pair(char a) {
	return B[A.find(a)];
}
bool isPair(char a, char b) {
	return Pair(a) == b;
}
string rev(const string & s, bool reverseResult = false) {
	string res;
	for(char c : s) {
		res += Pair(c);
	}
	if (reverseResult) {
		reverse(res.begin(), res.end());
	}
	return res;
}
string canonical(const string & str) {
	stack<char> s;
	for (char c : str) {
		if (!s.empty() && isPair(s.top(), c)) {
			s.pop();
		} else {
			s.push(c);
		}
	}
	string res;
	while (!s.empty()) {
		res += s.top();
		s.pop();
	}
	reverse(res.begin(), res.end());
	return res;
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);
	
	string x, y;
	cin >> x >> y;

	string xc = canonical(x);
	string yc = canonical(y);

	vvi dp(xc.size(), vi(yc.size()));

	int lcLen = 0;
	int xcBeg = 0;
	int ycBeg = 0;

	for (int i = 0; i < xc.size(); ++i) {
		for (int j = 0; j < yc.size(); ++j) {
			int & res = dp[i][j];
			if (xc[i] == yc[j]) {
				res = ((i - 1 >= 0 && j - 1 >= 0) ? dp[i - 1][j - 1] : 0) + 1;
			} else {
				res = 0;
			}
			if (res > lcLen) {
				lcLen = res;
				xcBeg = i - lcLen + 1;
				ycBeg = j - lcLen + 1;
			}
		}
	}

	string res;
	res += xc.substr(0, xcBeg);
	res += rev(yc.substr(0, ycBeg), true);
	res += y;
	res += rev(yc.substr(ycBeg + lcLen, -1), true);
	res += xc.substr(xcBeg + lcLen, -1);

	cout << res;


	return 0;
}