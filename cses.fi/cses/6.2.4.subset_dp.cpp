#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int>     vi;
typedef vector<vi>     vvi;
typedef vector<ll>     vll;
typedef set<int>        si;
typedef multiset<int>  msi;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)

int solve(const vi& weigth, int X) {
	int n = weigth.size();
	vector<pair<int, int>> best(1 << n);
	best[0] = { 0, 0 };
	for (int mask = 1; mask < (1 << n); ++mask) {
		best[mask] = { n + 1, 0 };
		for (int bit = 0; bit < n; ++bit) {
			if (mask & (1 << bit)) {
				auto option = best[mask ^ (1 << bit)];
				if (option.second + weigth[bit] <= X) {
					option.second += weigth[bit];
				} else {
					option.first++;
					option.second = weigth[bit];
				}
				best[mask] = min(best[mask], option);
			}
		}
	}
	return best[(1 << n) - 1].first + 1;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(0);

	vi weight = { 6, 3, 6, 3, 5, 3, 1 };

	cout << solve(weight, 9);

	return 0;
}