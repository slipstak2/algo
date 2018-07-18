#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)

void output_set(int b) {
	cout << '{';
	for (int k = 0; k < 32; ++k) {
		if (b & 1) {
			if (b & b - 1) {
				cout << k << ", ";
			} else {
				cout << k;
			}
		}
		b >>= 1;
	}
	cout << '}' << endl;
}
void emaxx(int x) {
	cout << "emaxx:" << endl;
	for (int s = x; s; s=(s-1)&x) {
		output_set(s);
	}
}

void laaksonen(int x) {
	cout << "laaksonen:" << endl;
	int b = 0;
	do {
		output_set(b);
	} while (b=(b-x)&x);
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	ios::sync_with_stdio(0);

	int x = 32 + 16 + 4;
	
	cout << "Init set:" << endl;
	output_set(x);
	cout << "----------------------" << endl;

	laaksonen(x);
	emaxx(x);

	return 0;
}