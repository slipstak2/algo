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

	vector<ll> mas(5);
	ll sum = 0;
	for (int i = 0; i < 5; ++i) {
		cin >> mas[i];
		sum += mas[i];
	}

	cout << 
		sum - *max_element(mas.begin(), mas.end()) << ' ' <<
		sum - *min_element(mas.begin(), mas.end());

	return 0;
}