// #Bit Manipulation
#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int l, r;
	cin >> l >> r;
	int res = l ^ r;
	for (int i = l; i <= r; ++i) {
		for (int j = l; j <= r; ++j) {
			res = max(res, i ^ j);
		}
	}
	cout << res;
	return 0;
}