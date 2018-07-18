#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)

int moveX[4] = {1,  2,  2, 1};
int moveY[4] = {-2, -1, 1, 2};

inline bool correct(int row, int col, const ll &n) {
	if (row < 0 || col < 0) return false;
	if (row >= n || col >= n) return false;
	return true;
}

ll solve(ll n)  {
	int row = -1, col = -1;
	ll items = n * n - 1;
	ll cnt = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ll cur = items;
			for (int k = 0; k < 4; ++k) {
				row = i + moveX[k];
				col = j + moveY[k];
				if (correct(row, col, n)) {
					cur--;
				}
			}
			cnt += cur;
			items--;
		}
	}
	return cnt;
}

int main() {
//#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
//#endif
	ios::sync_with_stdio(0);

	ll n;
	cin >> n;
	cout << solve(10000) << '\n';
	return 0;
}