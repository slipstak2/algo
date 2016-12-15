#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

ll n;

vector<map<int, ll> > dp;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	cin >> n;
	

	ll modulo = 1e9 + 7;
	ll fact = 1;
	for (ll i = 3; i <= n; ++i) {
		fact = (fact * i) % modulo;
	}

	cout << (fact * n) % modulo;
	return 0;


	dp.resize(max(4LL, n + 1));

	dp[1][1] = 1LL;
	dp[2][1] = 1LL;
	dp[3][1] = 1LL;
	dp[3][2] = 1LL;
	for (int V = 3; V < n; ++V) {
		for (map<int, ll>::iterator it = dp[V].begin(); it != dp[V].end(); ++it) {
			int L = it->first;
			dp[V + 1][L] += it->second * L;
			if (V - L >= 1) {
				dp[V + 1][L + 1] += it->second * (V - L);
			}
		}
	}

	ll CNT = 0;
	for (map<int, ll>::iterator it = dp[n].begin(); it != dp[n].end(); ++it) {
		CNT += it->second;
	}

	double E = 0;
	for (map<int, ll>::iterator it = dp[n].begin(); it != dp[n].end(); ++it) {
		E += (double)it->first * (double)(it->second) / CNT;
	}


	// f(V, L) = f(V - 1, L) * L + f(V - 1, L -1) * (V - L - 2)


	cout << E << endl << (ll)(E * fact + 1e-6) << endl;
	cout << fact / 2 * n << endl;
	return 0;
}