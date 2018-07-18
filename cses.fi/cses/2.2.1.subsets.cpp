// Задача №80. Двоичные строки заданной длины
// https://informatics.mccme.ru/mod/statements/view3.php?id=211&chapterid=80


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

int n;
vi subset;
void search(int k) { 
	if (k == n) {
		REP(i, 0, n-1) cout << subset[i];
		cout << endl;
	} else {
		subset.push_back(0);
		search(k + 1);
		subset.pop_back();

		subset.push_back(1);
		search(k + 1);
		subset.pop_back();
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

	return 0;
}