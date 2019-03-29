#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef map<char, vector<int>> DATA;
typedef vector<pair<int,int>> RESULT;


void calc(const string& s, DATA &data) {
	for (int i = 0; i < s.size(); ++i) {
		data[s[i]].push_back(i + 1);
	}
}


void getCommon(DATA &a, DATA &b, RESULT &result) {
	for (char c = 'a'; c <= 'z'; ++c) {
		vector<int> &va = a[c];
		vector<int> &vb = b[c];
		int cnt = min(va.size(), vb.size());
		for (int i = 0; i < cnt; ++i) {
			int valA = va.back(); va.pop_back();
			int valB = vb.back(); vb.pop_back();
			result.push_back(make_pair(valA, valB));
		}
	}
}

void getSimbols(DATA &a, DATA &b, RESULT &result, bool isRev = false) {
	vector<int> &va = a['?'];
	for (char c = 'a'; c <= 'z'; ++c) {
		vector<int> &vb = b[c];
		for (int i = 0; i < vb.size(); ++i) {
			if (va.size()) {
				int valA = va.back(); va.pop_back();
				if (!isRev) {
					result.push_back(make_pair(valA, vb[i]));
				}
				else {
					result.push_back(make_pair(vb[i], valA));
				}
				
			}
		}
	}
}
void getQuest(vector<int> &va, vector<int> &vb, RESULT &result) {
	int len = min(va.size(), vb.size());
	for (int i = 0; i < len; ++i) {
		result.push_back(make_pair(va[i], vb[i]));
	}
}
void output(const RESULT &result) {
	cout << result.size() << endl;
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i].first << ' ' << result[i].second << '\n';
	}
}
int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	iostream::sync_with_stdio(false);

	int n;
	string a, b;
	DATA dataA, dataB;
	RESULT result;

	cin >> n;
	cin >> a;
    calc(a, dataA);
	cin >> b;
	calc(b, dataB);

	getCommon(dataA, dataB, result);
	getSimbols(dataA, dataB, result);
	getSimbols(dataB, dataA, result, true);
	getQuest(dataA['?'], dataB['?'], result);

	output(result);

	return 0;
}