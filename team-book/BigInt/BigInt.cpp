#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <vector>
#include <string>
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

struct BigInt {
	
	const static int  DIGIT_WIDTH = 9; // 10-base digits count in BigInt digit (DIGIT_WIDTH must be in [1..9])
	const static int  BASE = Power<10, DIGIT_WIDTH>::value;

	template<class Predicate>
	static bool     cmp    (const BigInt & a, const BigInt & b, Predicate digitCmp);
	static BigInt & plus   (      BigInt & a,       int      b);
	static BigInt & plus   (      BigInt & a, const BigInt & b);
	static BigInt & minus  (      BigInt & a,       int      b);
	static BigInt & minus  (      BigInt & a, const BigInt & b);
	static BigInt & mul    (      BigInt & a,       int      b);
	static BigInt   mul    (const BigInt & a, const BigInt & b);
	static BigInt & divmod (      BigInt & a,       int      b, int    & mod);
	static BigInt   divmod (const BigInt & a, const BigInt & b, BigInt & mod);
	static BigInt & div    (      BigInt & a,       int      b);
	static BigInt   div    (const BigInt & a, const BigInt & b);
	static int      mod    (      BigInt & a,       int      b);
	static BigInt   mod    (const BigInt & a, const BigInt & b);

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
	BigInt(const string & buf) {
		init(buf);
	}
	int size() const {
		return digits.size();
	}
	int operator [] (int i) const {
		return i < size() ? digits[i] : 0;
	}
	/*int & operator [] (int i) {
		return digits[i];
	}*/
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
private:
	void init(const string & buf) {
		digits.resize((buf.size() - 1) / DIGIT_WIDTH + 1);
		for (int i = buf.size() - 1, pos = 0; i >= 0; i -= DIGIT_WIDTH, ++pos) {
			int start = max(0, i - DIGIT_WIDTH + 1);
			digits[pos] = atoi(buf.substr(start, i - start + 1).c_str());
		}

	}
	friend istream & operator >> (istream & in, BigInt & bi);
};

istream & operator >> (istream & in, BigInt & bi)
{
	string buf;
	in >> buf;
	bi.init(buf);
	return in;
}
ostream & operator << (ostream & out, const BigInt & bi) {
	out << (bi.digits.empty() ? 0 : bi.digits.back());
	for (int i = bi.size() - 2; i >= 0; --i) {
		out << setw(BigInt::DIGIT_WIDTH) << setfill('0') << bi.digits[i];
	}
	return out;
}

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

bool operator <  (const BigInt & a, const BigInt & b) {
	return BigInt::cmp(a, b, less<int>());
}
bool operator == (const BigInt & a, const BigInt & b) {
	return BigInt::cmp(a, b, equal_to<int>());
}
bool operator >  (const BigInt & a, const BigInt & b) {
	return b < a;
}
bool operator >= (const BigInt & a, const BigInt & b) {
	return !(a < b);
}
bool operator <= (const BigInt & a, const BigInt & b) {
	return !(b < a);
}
bool operator != (const BigInt & a, const BigInt & b) {
	return !(a == b);
}

BigInt & BigInt::plus(BigInt & a, int b) {
	vi & res = a.digits;
	int carry = b;
	for (int pos = 0; pos < a.size() && carry; ++pos) {
		res[pos] += carry;
		if (res[pos] >= BigInt::BASE) {
			res[pos] -= BigInt::BASE;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}
	return a.fixCarry(carry);
}
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


BigInt & BigInt::minus(BigInt & a, int b) {
	vi & res = a.digits;
	int carry = b;
	for (int pos = 0; pos < a.size() && carry; ++pos) {
		res[pos] -= carry;
		if (res[pos] < 0) {
			res[pos] += BigInt::BASE;
			carry = 1;
		}
		else {
			carry = 0;
		}
	}
	return a.norm();
}
BigInt & BigInt::minus(BigInt & a, const BigInt & b) {
	vi & res = a.digits;
	for (int i = 0; i < a.size(); ++i) {
		res[i] -= b[i];
		if (res[i] < 0) {
			res[i] += BigInt::BASE;
			res[i + 1]--;
		}
	}
	return a.norm();
}

template<class T>
BigInt operator - (const BigInt & a, T b) {
	BigInt res = a;
	return BigInt::minus(res, b);
}

template<class T>
BigInt & operator -= (BigInt & a, T b) {
	return BigInt::minus(a, b);
}

BigInt & BigInt::mul(BigInt & a, int b) {
	vi & res = a.digits;
	int carry = 0;
	for (int i = 0; i < a.size(); ++i) {
		ll tmp = (ll)res[i] * b + carry;
		carry = (int)(tmp / BigInt::BASE);
		res[i] = (int)(tmp - carry * BigInt::BASE);
	}
	return a.fixCarry(carry).norm();
}

BigInt BigInt::mul(const BigInt & a, const BigInt & b) {
	BigInt c;
	vi & res = c.digits;
	res.resize(a.size() + b.size());
	int carry = 0;
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b.size() || carry; ++j) {
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

template<class T>
BigInt operator *= (BigInt & a, T b) {
	return BigInt::mul(a, b);
}

BigInt & BigInt::divmod(BigInt & a, int b, int & mod) {
	vi & res = a.digits;
	mod = 0;
	for (int i = a.size() - 1; i >= 0; --i) {
		ll tmp = (ll)mod * BigInt::BASE + res[i];
		res[i] = int(tmp / b);
		mod  = int(tmp - res[i] * b);
	}
	return a.norm();
}

void operator <<= (BigInt & a, const int k) {
	for (int i = 0; i < k; ++i) {
		a.digits.insert(a.digits.begin(), 0);
	}
	a.norm(); // 0 << 1 = 0;
}

BigInt BigInt::divmod(const BigInt & a, const BigInt & b, BigInt & mod) {
	BigInt res;
	vi & div = res.digits;
	div.resize(a.size());

	assert(mod == 0);
	for (int i = a.size() - 1; i >= 0; --i) {
		mod <<= 1;
		mod.digits[0] = a[i];

		BigInt Num;
		int l = 0, r = BigInt::BASE - 1, Dig;
		while (l <= r) {
			int dig = (l + r) / 2;
			BigInt num = b * dig;
			if (num <= mod) {
				Num = num;
				Dig = dig;
				l = dig + 1;
			} else {
				r = dig - 1;
			}
		}
		mod = mod - Num;
		div[i] = Dig;
	}
	return res.norm();
}

BigInt & BigInt::div(BigInt & a, int b) {
	int mod;
	return divmod(a, b, mod);
}

BigInt BigInt::div(const BigInt & a, const BigInt & b) {
	BigInt mod;
	return divmod(a, b, mod);
}

int BigInt::mod(BigInt & a, int b) {
	int res;
	divmod(a, b, res);
	return res;
}

BigInt BigInt::mod(const BigInt & a, const BigInt & b) {
	BigInt res;
	divmod(a, b, res);
	return res;
}

template<class T>
BigInt operator / (const BigInt & a, T b) {
	BigInt res = a;
	return BigInt::div(res, b);
}

template<class T>
BigInt operator /= (BigInt & a, T b) {
	return BigInt::div(a, b);
}

// BigInt можно передавать по значению - и тогда можно обойтись без временной переменной
template<class T>
T operator % (const BigInt & a, T b) {
	BigInt res = a;
	return BigInt::mod(res, b);
}

template<class T>
int operator %= (BigInt & a, T b) {
	return BigInt::mod(a, b);
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);

	BigInt a, b;
	cin >> a >> b;
	cout << a % b;
	return 0;

}