#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int s, t;
int a, b;
int m, n;

int check(int x) {
	return (s <= x && x <= t) ? 1 : 0;
}

int calc(int beg, int n) {
	int cnt = 0;
	for (int i = 0, x; i < n; ++i) {
		cin >> x;
		cnt += check(beg + x);
	}
	return cnt;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);


	cin >> s >> t;
	cin >> a >> b;
	cin >> m >> n;

	int apples = calc(a, m);
	int oragnes = calc(b, n);
	cout << apples << endl << oragnes;

	return 0;
}