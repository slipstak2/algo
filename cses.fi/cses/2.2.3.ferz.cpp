// https://www.e-olymp.com/ru/problems/2712
// https://www.e-olymp.com/ru/problems/4445

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

const int MAXN = 15;
int n;
bool usedCol[MAXN], usedD1[2 * MAXN], usedD2[2 * MAXN];

bool field[MAXN][MAXN];

int cnt = 0;
void search(int row) {
	if (row == n) {
		cnt++;
		return;
	} else {
		for (int col = 0; col < n; ++col) {
			int d1 = row + col;
			int d2 = col - row + n;
			if (!usedCol[col] && !usedD1[d1] && !usedD2[d2]) {
				usedCol[col] = usedD1[d1] = usedD2[d2] = true;
				field[row][col] = true;
				search(row + 1);
				field[row][col] = false;
				usedCol[col] = usedD1[d1] = usedD2[d2] = false;
			}
		}
	}
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(0);

	cin >> n;

	search(0);
	cout << cnt << endl;

	return 0;
}