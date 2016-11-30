#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>

using namespace std;

typedef long long ll;

const int MAX_NUM = (int)1e9 + 50;

int fast(int n, int m) {
	vector<bool> resIsPrimes(m - n + 1, true);
	if (n == 1) {
		resIsPrimes[0] = false;
	}

	int maxPrimeDiv = sqrt(MAX_NUM + 0.0);
	vector<bool> isPrimes(maxPrimeDiv + 1, true);
	for (int num = 2; num <= maxPrimeDiv; ++num) {
		if (isPrimes[num]) {
			for (int mul = 2; num * mul <= maxPrimeDiv; ++mul) {
				isPrimes[num * mul] = false;
			}
		}
	}

	for (int num = 2; num <= maxPrimeDiv; ++num) {
		if (isPrimes[num]) {
			for (int mul = max(2, n / num); num * mul <= m; ++mul) {
				if (num * mul >= n) {
					resIsPrimes[num * mul - n] = false;
				}
			}
		}
	}

	int cnt = 0;
	for (int i = 2; i < resIsPrimes.size(); ++i) {
		if (resIsPrimes[i] && resIsPrimes[i - 2]) {
			cnt++;
		}
	}
	return cnt;
}

bool isPrime(int n) {
	if (n < 2) return false;
	for (int i = 2; i * i <= n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

int slow(int n, int m) {
	int cnt = 0;
	for (int i = n+2; i <= m; ++i) {
		if (isPrime(i) && isPrime(i - 2)) {
			cnt++;
		}
	}
	return cnt;
}

void check() {
	int N = 9000, M = 9050;
	for (int i = N; i <= M; ++i) {
		for (int j = i; j <= M; ++j) {
			if (slow(i, j) != fast(i, j)) {
				cout << "FAIL: " << i << ' ' << j << endl;
				cout << "slow = " << slow(i, j) << endl;
				cout << "fast = " << fast(i, j) << endl;
			}
		}
	}
	cout << "OK" << endl;
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);
	
	int n, m;
	cin >> n >> m;

	cout << fast(n, m);

	return 0;
}