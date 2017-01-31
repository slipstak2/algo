#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
typedef vector<long long> vll;
typedef vector<vll>       v2ll;
typedef vector<v2ll>      v3ll;
typedef vector<v3ll>      v4ll;
typedef vector<v4ll>      v5ll;

const int A = 0;
const int B = 1;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int n, k;
	string loco, car;
	cin >> n >> k;
	cin >> loco;
	int locoBeg = loco[0] == 'A' ? A : B;
	int locoEnd = loco[1] == 'A' ? A : B;

	int AA = 0, AB = 0, BA = 0, BB = 0;
	for (int i = 0; i < n; ++i) {
		cin >> car;
		if (car == "AA") AA++;
		if (car == "AB") AB++;
		if (car == "BA") BA++;
		if (car == "BB") BB++;
	}
	v5ll dp(2, v4ll(AA + 1, v3ll(AB + 1, v2ll(BA + 1, vll(BB + 1)))));
                             // A/B   AA   AB   BA   BB 
    if (locoEnd == A && AA)  dp[ A ][ 1 ][ 0 ][ 0 ][ 0 ] = 1;
    if (locoEnd == A && AB)  dp[ B ][ 0 ][ 1 ][ 0 ][ 0 ] = 1;
    if (locoEnd == B && BA)  dp[ A ][ 0 ][ 0 ][ 1 ][ 0 ] = 1;
    if (locoEnd == B && BB)  dp[ B ][ 0 ][ 0 ][ 0 ][ 1 ] = 1;

	for (int aa = 0; aa <= AA; ++aa) {
		for (int ab = 0; ab <= AB; ++ab) {
			for (int ba = 0; ba <= BA; ++ba) {
				for (int bb = 0; bb <= BB; ++bb) {
					if (aa < AA) dp[A][aa + 1][ab][ba][bb] += dp[A][aa][ab][ba][bb];
					if (ab < AB) dp[B][aa][ab + 1][ba][bb] += dp[A][aa][ab][ba][bb];
					if (ba < BA) dp[A][aa][ab][ba + 1][bb] += dp[B][aa][ab][ba][bb];
					if (bb < BB) dp[B][aa][ab][ba][bb + 1] += dp[B][aa][ab][ba][bb];
				}
			}
		}
	}

	ll res = 0;
	for (int aa = 0; aa <= AA; ++aa) {
		for (int ab = 0; ab <= AB; ++ab) {
			for (int ba = 0; ba <= BA; ++ba) {
				for (int bb = 0; bb <= BB; ++bb) {
					if (aa + ab + ba + bb == k) {
						res += dp[locoBeg][aa][ab][ba][bb];
					}
				}
			}
		}
	}
	if (res) {
		cout << "YES" << endl << res;
	}
	else {
		cout << "NO";
	}

	return 0;
}