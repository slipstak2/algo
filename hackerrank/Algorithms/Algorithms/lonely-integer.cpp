// #Bit Manipulation
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

	int n;
	cin >> n;
	int res = 0, cur;
	while (n-- > 0) {
		cin >> cur;
		res ^= cur;
	}
	cout << res;
	return 0;
}