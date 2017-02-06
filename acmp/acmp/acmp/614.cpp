#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

template<int p, int q>
class Power {
public:
	static const int value = p * Power<p, q - 1>::value;
};

template<int p>
class Power<p, 0> {
public:
	static const int value = 1;
};

struct BigInt {
	
	const static int  DIGIT_WIDTH = 9; // 10-base digits count in BigInt digit (DIGIT_WIDTH must be in [1..9])
	const static int  BASE = Power<10, DIGIT_WIDTH>::value;

	static BigInt & plus   (      BigInt & a, const BigInt & b);

	vi digits;
	BigInt() {}
	BigInt(int num) {
		while (num) {
			digits.push_back(num % BASE);
			num /= BASE;
		}
	}
	BigInt(const vi & v) {
		digits = v;
	}
	void setEmpty() {
		digits.push_back(-1);
	}
	bool isEmpty() const {
		return size() == 1 && digits[0] == -1;
	}
	int operator [] (int i) const {
		return i < size() ? digits[i] : 0;
	}
	int size() const {
		return digits.size();
	}


	BigInt & norm() {
		while (size() > 1 && !digits.back()) {
			digits.pop_back();
		}
		return *this;
	}
	BigInt & fixCarry(int carry) {
		if (carry) {
			digits.push_back(carry);
		}
		return *this;
	}
};

BigInt & BigInt::plus(BigInt & a, const BigInt & b) {
	vi & res = a.digits;
	res.resize(max(a.size(), b.size()));
	int carry = 0;
	for (int i = 0; i < a.size(); ++i) {
		res[i] = a[i] + b[i] + carry;
		carry = res[i] / BigInt::BASE;
		res[i] -= carry * BigInt::BASE;
	}
	return a.fixCarry(carry);
}

template<class T>
BigInt operator + (const BigInt & a, T b) {
	BigInt res = a;
	return BigInt::plus(res, b);	
}

template<class T>
BigInt & operator += (BigInt & a, T b) {
	return BigInt::plus(a, b);
}

ostream & operator << (ostream & out, const BigInt & bi) {
	out << (bi.digits.empty() ? 0 : bi.digits.back());
	for (int i = bi.size() - 2; i >= 0; --i) {
		out << setw(BigInt::DIGIT_WIDTH) << setfill('0') << bi.digits[i];
	}
	return out;
}
string s;
typedef vector<BigInt> vbi;
typedef vector<vbi> vvbi;

vvbi dp;


BigInt EMPTY;
BigInt go(int len, int opensCount) {
	BigInt & res = dp[len][opensCount];
	if (!res.isEmpty()) {
		return res;
	}

	res = 0;
	if (opensCount == 0)	res = 1;
	else						res = 0;

	size_t nextOpen = len + 1;
	for (; nextOpen < s.size() && s[nextOpen] != '('; ++nextOpen);
	if (nextOpen < s.size()) {
		res += go(nextOpen, opensCount + 1);
	}

	if (opensCount > 0) {
		size_t nextClose = len + 1;
		for (; nextClose < s.size() && s[nextClose] != ')'; ++nextClose);
		if (nextClose < s.size()) {
			res += go(nextClose, opensCount - 1);
		}
	}
	return res;
}


int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);


	cin >> s;
	s = '#' + s;
	BigInt EMPTY;
	EMPTY.setEmpty();
	dp.resize(s.size(), vbi(s.size(), EMPTY));
	cout << go(0, 0);
	return 0;
}