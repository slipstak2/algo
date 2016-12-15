#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	const int LETTERS_CNT = 26;
	vi h(LETTERS_CNT);
	for (int i = 0; i < LETTERS_CNT; ++i){
		cin >> h[i];
	}

	string word;
	cin >> word;

	int maxH = h[word[0] - 'a'];
	for (char c : word) {
		maxH = max(maxH, h[c - 'a']);
	}

	cout << word.size() * maxH;
	
	return 0;
}