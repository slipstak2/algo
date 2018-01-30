#pragma comment (linker, "/STACK:64000000")

#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

#define For(i, st, en) for(int i=(st); i<=(int)(en); i++)
#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define fori(it, x) for (auto it = (x).begin(); it != (x).end(); it++)

const int INF = (int)1e9 - 1;
const int N = 1005;
int a[N][N];
int dp[N][N][2];
bool up[N][N][2];

void printZero(int row, int n) {
	For(i, 2, row)     cout << 'D';
	For(i, 2, n)       cout << 'R';
	For(i, row + 1, n) cout << 'D';
}

void print(int i, int j, int k) {
	string s;
	while (i != 1 || j != 1){
		if (up[i][j][k]) {
			s += 'D';
			i--;
		} else {
			s += 'R';
			j--;
		}
	}
	reverse(s.begin(), s.end());
	cout << s;
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	iostream::sync_with_stdio(false);

	int n, x;
	cin >> n;
	For(i, 2, n) {
		dp[i][0][0] = dp[0][i][0] = INF;
		dp[i][0][1] = dp[0][i][1] = INF;
	}
	int zeroRow = -1;
	For(i, 1, n) {
		For(j, 1, n) {
			cin >> x;
			if (x == 0) {
				zeroRow = i;
			} else {
				for (; !(x % 2); x /= 2) ++dp[i][j][0];
				for (; !(x % 5); x /= 5) ++dp[i][j][1];
			}

			for (int k = 0; k < 2; ++k) {
				bool isUp = dp[i - 1][j][k] < dp[i][j - 1][k];
				up[i][j][k] = isUp;
				if (isUp) {
					dp[i][j][k] += dp[i - 1][j][k];
				} else {
					dp[i][j][k] += dp[i][j - 1][k];
				}
			}
		}
	}
	int k = dp[n][n][0] < dp[n][n][1] ? 0 : 1;
	if (dp[n][n][k] != 0 && zeroRow != -1) {
		cout << 1 << endl;
		printZero(zeroRow, n);
	} else {
		cout << dp[n][n][k] << endl;
		print(n, n, k);
	}
	
	return 0;
}