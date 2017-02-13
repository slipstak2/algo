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

typedef long double ld;
typedef vector<ld> vd;
typedef vector<vd> vvd;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int n, sum;
	cin >> n >> sum;
	int size = max(sum, 6);
	vd prv(size + 1), cur(size + 1);
	for (int s = 1; s <= 6; ++s) {
		prv[s] = (double)1/6;
	}


	for (int cnt = 2; cnt <= n; ++cnt) {
		for (int s = 1; s <= sum; ++s) {
			ld & res = cur[s];
			for (int val = 1; val <= 6; ++val) {
				if (s - val >= 1) {
					res += prv[s - val] / 6;
				}
			}
		}
		prv.swap(cur);
		cur.assign(size + 1, 0);
	}
	cout << prv[sum];
	return 0;
}