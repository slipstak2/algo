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

const int MAX_NUM = 1e5 + 10;

vi primes;
void findPrimes() {
	vector<bool> isPrime(MAX_NUM, true);
	for (int i = 2; i < MAX_NUM; ++i) {
		for (int mul = 2; mul * i < MAX_NUM; ++mul) {
			isPrime[i*mul] = false;
		}
	}
	primes.reserve(MAX_NUM);

	for (int i = 2; i < MAX_NUM; ++i) {
		if (isPrime[i]) {
			primes.push_back(i);
		}
	}
}

string solve(int n) {
	int cnt = 0;
	for (int i = 0; i < primes.size(); ++i) {
		if (primes[i] > n) {
			break;
		}
		else {
			++cnt;
		}
	}
	if (cnt & 1) {
		return "Alice";
	}
	else {
		return "Bob";
	}

}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	findPrimes();

	int games, n;
	cin >> games;
	while (games--) {
		cin >> n;
		cout << solve(n) << "\n";
	}
	return 0;
}