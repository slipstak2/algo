#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;

ll item(int row, int col) {
	ll n = max(row, col);
	ll corner = n * n - (n - 1);
	
	if (row == n) {
		int mul = (n & 1) ? -1 : 1;
		corner += (n - col) * mul;
	} else {
		int mul = (n & 1)? 1 : -1;
		corner += (n - row) * mul;
	}
	return corner;
}

void solve() {
	ll tests, row, col;
	cin >> tests;
	while (tests --> 0) {
		cin >> row >> col;
		cout << item(row, col) << endl;
	}
}
void test() {
	int n = 10;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout.width(4);
			cout << item(i , j);
		}
		cout << endl;
	}
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(0);

	
	//test();
	solve();
	return 0;
}