#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int n, val;
	cin >> n;
	const int CNT = 100 + 1;
	vi a(CNT);
	for (int i = 0; i < n; ++i) {
		cin >> val;
		a[val]++;
	}

	int res = 0;
	for (int i = 1; i < CNT; ++i) {
		int cur = a[i] + a[i - 1];
		res = max(res, cur);
	}
	cout << res;
	return 0;
}