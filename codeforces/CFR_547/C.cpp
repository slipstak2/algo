#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int n;
vector<int> q;

enum RESULT {
	LESS = 1,
	GREATE = 2,
	EQUAL = 3,
	ERROR = 4
};

RESULT f(int first, bool output) {
	set<int> uniq;
	vector<int> result(n);
	result[0] = first;
	uniq.insert(first);
	for (int i = 0; i < q.size(); ++i) {
		result[i + 1] = result[i] + q[i];
		uniq.insert(result[i + 1]);
		if (result[i + 1] < 1) return RESULT::LESS;
		if (result[i + 1] > n) return RESULT::GREATE;
	}
	
	if (output) {
		for (int i = 0; i < result.size(); ++i) {
			cout << result[i] << ' ';
		}
	}
	return uniq.size() == result.size() ? RESULT::EQUAL : RESULT::ERROR;
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	iostream::sync_with_stdio(false);

	cin >> n;
	q.resize(n - 1);
	for (int i = 0; i < q.size(); ++i) {
		cin >> q[i];
	}

	int l = 1, r = n;
	while (l <= r) {
		int m = (l + r) / 2;
		RESULT result = f(m, false);
		if (result == RESULT::LESS) {
			l = m + 1;
		}
		else if (result == RESULT::GREATE) {
			r = m - 1;
		}
		else if (result == RESULT::EQUAL){
			f(m, true);
			return 0;
		}
		else {
			cout << -1;
			return 0;
		}
	}
	cout << -1;
	return 0;
}