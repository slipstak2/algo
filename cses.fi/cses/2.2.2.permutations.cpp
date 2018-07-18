// Задача №85. Все перестановки заданной длины
// https://informatics.mccme.ru/mod/statements/view3.php?id=211&chapterid=85#1
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

const int MAXN = 10;
int n;
vi permutation;
bool used[MAXN + 1];

void search() {
	if (permutation.size() == n) {
		REP(i, 0, n - 1) cout << permutation[i];
		cout << endl;
	} else {
		for (int i = 1; i <= n; ++i) {
			if (!used[i]) {
				used[i] = true;
				permutation.push_back(i);
				search();
				permutation.pop_back();
				used[i] = false;
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
	search();

	return 0;
}