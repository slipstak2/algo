#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll>  vll;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(0);

	int n;
	cin >> n;
	vi a(n);
	if (n == 2 || n == 3) {
		cout << "NO SOLUTION";
		return 0;
	} else if (n == 4) {
		for (int i = 0; i < n; ++i) a[i] = i + 1;
		do {
			bool isOK = true;
			for (int i = 1; i < n; ++i) {
				isOK &= abs(a[i] - a[i - 1]) != 1; 
			}
			if (isOK) break;
		} while(next_permutation(a.begin(), a.end()));
	} else {
	
		int cur = 0;
		for (int i = 0; i < n; i += 2) a[i] = ++cur;
		for (int i = 1; i < n; i += 2) a[i] = ++cur;
	}
	for (int i = 0; i < n; ++i) {
		cout << a[i] << ' ';
	}


	return 0;
}