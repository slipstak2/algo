#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

int n, m;

const int LEFT  = 1;
const int RIGHT = 2;
const int UP    = 4;
const int DOWN  = 8;

vector<int> neibStates[2][2];

set<vi> used;


vi states;
vi colors;

bool metColors[11];

inline int is(int mask, int move) {
	return (mask & move) == move;
}


void updateColor(vi & colors, int oldColor, int newColor) {
	for (int i = 0; i < n; ++i) {
		if (colors[i] == oldColor) {
			colors[i] = newColor;
		}
	}
}

void join(vi & colors1, vi & colors2, int pos1, int pos2) {
	if (colors1[pos1] != colors2[pos2]) {
		int oldColor = max(colors1[pos1], colors2[pos2]);
		int newColor = min(colors1[pos1], colors2[pos2]);
		updateColor(colors1, oldColor, newColor);
		updateColor(colors2, oldColor, newColor);
	}
}
set<int> adj[10000];
//map<vi, set<vi>> adj;


map<vi, int> profile2num;
vi profiles[10000];
int num(const vi & v) {
	if (profile2num.find(v) == profile2num.end()) {
		int num = profile2num.size();
		profile2num[v] = num;
		profiles[num] = v;
	}
	return profile2num[v];
}
void normalize(vi & colors) {
	vi newColor(2 * n + 1);
	int minColor = 0;
	for (int i = 0; i < n; ++i) {
		if (colors[i]) {
			if (newColor[colors[i]] == 0) {
				newColor[colors[i]] = ++minColor;
			}
			colors[i] = newColor[colors[i]];
		}
	}
}

void output(const vi & colors, bool isEndl = true) {
	for (int i = 0; i < (int)colors.size(); ++i) {
		cout << colors[i];
	}
	if (isEndl) {
		cout << endl;
	}
}

int GLOBAL_CNT = 0;
void genNextProfile(int left, const vi & upProfile, int pos, int downCnt, queue<vi> & q) {
	GLOBAL_CNT++;
	if (pos == n) {
		if (downCnt & 1) return;

		vi upColors = upProfile;
		int cnt = *max_element(upColors.begin(), upColors.end());
		for (int i = 0; i < n; ++i) {
			colors[i] = ++cnt;
		}

		// join
		for (int i = 0; i < n; ++i) {
			if (states[i] & LEFT) {
				join(colors, colors, i, i - 1);
			}
			if (upColors[i] && (states[i] & UP)) {
				join(upColors, colors, i, i);
			}
		}

		// check all colors from up go to cur profile
		cnt = *max_element(upColors.begin(), upColors.end());
		memset(metColors, 0, sizeof(metColors));
		for (int i = 0; i < n; ++i) {
			metColors[colors[i]] = true;
		}

		for (int i = 1; i <= cnt; ++i) {
			if (!metColors[i]) {
				return;
			}
		}


		// erase not down jumps
		for (int i = 0; i < n; ++i) {
			if (!(states[i] & DOWN)) {
				colors[i] = 0;
			}
		}

		// normalize
		normalize(colors);
		
		adj[num(upProfile)].insert(num(colors));
		if (used.find(colors) == used.end()) {
			//output(colors);
			used.insert(colors);
			q.push(colors);
		}
		return;
	}

	for (int curState: neibStates[left][upProfile[pos] != 0]) {
		states[pos] = curState;
		genNextProfile(is(states[pos], RIGHT), upProfile, pos + 1, downCnt + is(states[pos], DOWN), q);
	}
}


void initNeibStates() {
           //[LEFT][UP]
	neibStates[0]   [0].push_back(DOWN | RIGHT);

	neibStates[0]   [1].push_back(UP   | DOWN);
	neibStates[0]   [1].push_back(UP   | RIGHT);

	neibStates[1]   [0].push_back(LEFT | DOWN);
	neibStates[1]   [0].push_back(LEFT | RIGHT);

	neibStates[1]   [1].push_back(LEFT | UP);
}
int main() {
//#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
//#endif
	std::ios::sync_with_stdio(false);
	initNeibStates();

	cin >> n >> m;
	if (n > m) swap(n, m);

	states.resize(n);
	colors.resize(n);

	vi begProfile(n);
	num(begProfile); // for begProfileNum == 0

	queue<vi> q;
	q.push(begProfile);
	used.insert(begProfile);
	while (!q.empty()) {
		vi curProfile = q.front(); q.pop();
		states.assign(states.size(), 0);
		genNextProfile(0, curProfile, 0, 0, q);
	}


	for (auto profileInfo : profile2num) {
		
		for (int nextProfileNum : adj[profileInfo.second]) {
			output(profileInfo.first);
			output(profiles[nextProfileNum]);
			cout << "-------------------" << endl;
		}
		cout << "*******************" << endl;
		
	}

	int rows = m;
	int profilesCnt = profile2num.size();
	vector<vi> dp(rows, vi(profilesCnt));

	int numBegProfile = num(begProfile);
	dp[0][numBegProfile] = 1;
	for (int row = 0; row < rows - 1; ++row) {
		for (int curProfileNum = 0; curProfileNum  < profilesCnt; ++curProfileNum ) {
			for (int nextProfileNum : adj[curProfileNum]) {
				//if (nextProfileNum == numBegProfile && row != rows - 2) continue;
				if (dp[row][curProfileNum]) {
					dp[row + 1][nextProfileNum] += dp[row][curProfileNum];				
				}
			}
		}
	}

	cout << "answer: ";
	cout << dp[rows - 1][numBegProfile];

	



	return 0;
}