#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	iostream::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> a(2 * n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int i = 0; i < n; ++i) {
		a[n + i] = a[i];
	}

	vector<int> dp(2 * n);
	for (int i = 0; i < 2 * n; ++i) {
		if (a[i] == 1) {
			if (i - 1 >= 0) {
				dp[i] = dp[i - 1] + 1;
			}
			else {
				dp[i] = 1;
			}
		}
	}

	cout << *max_element(dp.begin(), dp.end());
	return 0;
}