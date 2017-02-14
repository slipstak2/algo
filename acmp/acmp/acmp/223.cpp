#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef long long ll;

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

struct BigInt: vi {
	
	const static int  DIGIT_WIDTH = 9; // 10-base digits count in BigInt digit (DIGIT_WIDTH must be in [1..9])
	const static int  BASE = Power<10, DIGIT_WIDTH>::value;

	template<class Predicate>
	static bool     cmp    (const BigInt & a, const BigInt & b, Predicate digitCmp);
	static BigInt & plus   (      BigInt & a, const BigInt & b);
	static BigInt   mul    (const BigInt & a, const BigInt & b);

	BigInt() {}
	BigInt(int num) {
		while (num) {
			push_back(num % BASE);
			num /= BASE;
		}
	}
	BigInt(const vi & v): vi(v) {}
	int operator [] (size_t i) const {
		return i < size() ? vi::operator[](i) : 0;
	}
	int & operator [] (size_t i) {
		return vi::operator[](i);
	}
	BigInt & norm() {
		while (size() > 1 && !back()) {
			pop_back();
		}
		return *this;
	}
	BigInt & fixCarry(int carry) {
		if (carry) {
			push_back(carry);
		}
		return *this;
	}
};

template<class Predicate>
bool BigInt::cmp(const BigInt & a, const BigInt & b, Predicate digitCmp) {
	if (a.size() != b.size()) {
		return digitCmp(a.size(), b.size());
	}
	for (int i = a.size() - 1; i >= 0; --i) {
		if (a[i] != b[i]) {
			return digitCmp(a[i], b[i]);
		}
	}
	return digitCmp(0, 0);
}

bool operator == (const BigInt & a, const BigInt & b) {
	return BigInt::cmp(a, b, equal_to<int>());
}

BigInt & BigInt::plus(BigInt & a, const BigInt & b) {
	BigInt & res = a;
	res.resize(max(a.size(), b.size()));
	int carry = 0;
	for (size_t i = 0; i < a.size(); ++i) {
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


BigInt   BigInt::mul(const BigInt & a, const BigInt & b) {
	BigInt c;
	BigInt & res = c;
	res.resize(a.size() + b.size());
	int carry = 0;
	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = 0; j < b.size() || carry; ++j) {
			ll tmp = res[i + j] + (ll)a[i] * b[j] + carry;
			carry = int(tmp / BigInt::BASE);
			res[i + j] = int(tmp - (ll)carry * BigInt::BASE);
		}
	}
	return c.norm();
}

template<class T>
BigInt operator * (const BigInt & a, T b) {
	BigInt res = a;
	return BigInt::mul(res, b);
}

ostream & operator << (ostream & out, const BigInt & bi) {
	out << (bi.empty() ? 0 : bi.back());
	for (int i = bi.size() - 2; i >= 0; --i) {
		out << setw(BigInt::DIGIT_WIDTH) << setfill('0') << bi[i];
	}
	return out;
}


typedef BigInt T;
typedef vector<T>   vT;
typedef vector<vT>  v2T;
typedef vector<v2T> v3T;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	string src, dst;
	cin >> src >> dst;

	int n = (int)src.size();
	v3T dp(1 + n, v2T(1 + n, vT(1 + n)));

	// [len][srcFirst][dstFirst]
	for (int srcFirst = 0; srcFirst <= n; ++srcFirst) {
		for (int dstFirst = 0; dstFirst <= n; ++dstFirst) {
			dp[1][srcFirst][dstFirst] = src[srcFirst] == dst[dstFirst] ? 1 : 0;
			dp[0][srcFirst][dstFirst] = 1;
		}
	}

	for (int len = 2; len <= n; ++len) {
		for (int srcFirst = 0; srcFirst + len <= n; ++srcFirst) {
			for (int dstFirst = 0; dstFirst + len <= n; ++dstFirst) {
				T & sum = dp[len][srcFirst][dstFirst];
				for (int add = 0; add < len; ++add) {
					if (src[srcFirst] == dst[dstFirst + add]) {
						sum += dp[add][srcFirst + 1][dstFirst] * dp[len - 1 - add][srcFirst + 1 + add][dstFirst + 1 + add];
					}
				}
			}
		}
	}

	cout << dp[n][0][0];
	return 0;
}