#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int sum(int n) {
	int res = 0;
	while (n) {
		res += n % 10;
		n /= 10;
	}
	return res;
}

bool cmp(int a, int b) {
	int sumA = sum(a);
	int sumB = sum(b);
	if (sumA != sumB) {
		return sumA < sumB;
	}
	return a > b;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int n;
	cin >> n;

	vector<int> divs;
	int len = sqrt(n + 0.0);
	for (int i = 1; i <= len; ++i) {
		if (n % i == 0) {
			divs.push_back(i);
			divs.push_back(n / i);
		}
	}

	cout << *max_element(divs.begin(), divs.end(), cmp);

	return 0;
}