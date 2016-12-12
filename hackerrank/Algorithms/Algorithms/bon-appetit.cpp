#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	int cur, sum = 0;
	for (int i = 0; i < n; ++i) {
		cin >> cur;
		if (i != k) {
			sum += cur;
		}
	}

	int b;
	cin >> b;
	if (b > sum / 2) {
		cout << b - sum / 2;
	}
	else {
		cout << "Bon Appetit";
	}

	return 0;
}