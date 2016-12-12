#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
const int NOT_FOUND = (int)-2e9 - 123;

int n;
vector<int> met;

int m;
int hMin, hMax;

struct segment {
	int beg;
	int lst;
	segment() : beg(0), lst(-1)
	{}
	segment(int beg, int lst) : beg(beg), lst(lst)
	{}
	int len() {
		return lst - beg;
	}
};
struct cmp {
	bool operator () (const segment & s, int pos) {
		return s.beg < pos;
	}
	bool operator () (int pos, const segment & s) {
		return pos < s.beg;
	}
};
bool operator < (const segment & s, int pos) {
	return s.beg < pos;
}


vector<segment> segs;

int getLast(int val) {
	vector<segment>::iterator it = upper_bound(segs.begin(), segs.end(), val, cmp());
	return (*(it - 1)).lst;
}

int nearLeftMet(int val) {
	vector<int>::iterator it = upper_bound(met.begin(), met.end(), val);
	return *(it - 1);
}

bool isCorrectSegment(int len) {
	return hMin <= len && len <= hMax;
}
bool checkBegin(int beg) {
	int curLst = getLast(beg);
	int targetLst = beg + m;
	if (targetLst <= curLst) {
		if (binary_search(met.begin(), met.end(), targetLst)) {
			return true;
		}
		else {
			int lastDelta = targetLst - nearLeftMet(targetLst);
			if (isCorrectSegment(lastDelta)) {
				return true;
			}
		}
	}
	return false;
}
int try_find_begin() {
	for (int i = 0; i < (int)met.size(); ++i) {
		if (checkBegin(met[i])) return met[i];
		if (1 <= i) {
			if (met[i - 1] <= met[i] - hMin && checkBegin(met[i] - hMin)) return met[i] - hMin;
			if (met[i - 1] <= met[i] - hMax && checkBegin(met[i] - hMax)) return met[i] - hMax;
		}
	}
	return NOT_FOUND;
}

int BEGIN() {
	segs.reserve(n);
	segs.push_back(segment(met[0], met[0]));

	for (int i = 1; i < (int)met.size(); ++i) {
		segment & lastSegment = segs.back();
		int len = met[i] - lastSegment.lst;
		if (isCorrectSegment(len)) {
			lastSegment.lst = met[i];
		}
		else {
			if (len > hMax) {
				lastSegment.lst += hMax;
			}
			segs.push_back(segment(met[i], met[i]));
		}
	}

	return try_find_begin();
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	cin >> n;

	met.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> met[i];
	}

	cin >> m >> hMin >> hMax;

	met.insert(met.begin(), met[0] - hMax);
	met.push_back(met.back() + hMax);
	n += 2;


	int beginResult = BEGIN();
	for (int i = 0; i < met.size(); ++i) {
		met[i] = -met[i];
	}
	sort(met.begin(), met.end());
	int endResult = BEGIN();

	if (beginResult != NOT_FOUND) {
		cout << beginResult;
	}
	else {
		cout << -endResult - m;
	}
	return 0;
}