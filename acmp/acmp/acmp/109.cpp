#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef map<int, int> mii;
typedef mii::iterator mii_iter;

#define all(c) c.begin(),c.end()

void output(int div, const vi & tail, int begPeriod) {
	cout << div << '.';
	for (int i = 0; i < (begPeriod == -1 ? tail.size() : begPeriod); ++i) {
		cout << tail[i];
	}
	if (begPeriod != -1) {
		cout << '(';
		for (int i = begPeriod; i < tail.size(); ++i) {
			cout << tail[i];
		}
		cout << ')';
	}
	cout << endl;
}

void solve(int a, int b) {
	if (a >= b && a % b == 0) {
		cout << a / b;
	}
	else {
		int div = a / b;
		int fract = a % b;
		vi tail;
		mii mem;
		int begPeriod = -1;
		while (fract) {
			fract = fract * 10;
			mii_iter iter = mem.find(fract);
			if (iter != mem.end()) {
				begPeriod = iter->second;
				break;
			}
			mem[fract] = tail.size();
			tail.push_back(fract / b);
			fract %= b;
		}
		output(div, tail, begPeriod);
	}
}
int main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);


	int a, b;
	while (scanf("%d/%d", &a, &b) != -1) {
		solve(a, b);
	}
	return 0;
}