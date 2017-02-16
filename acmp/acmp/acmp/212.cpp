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

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;

#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)

const int INF = (int)1e9;

vi adj[151];
vvi dp; // dp[curNode][remNodes]
int n, p;

void go(int cur, int par, int & ans) {
	int childCount = par == 0 ? adj[cur].size() : adj[cur].size() - 1;
	dp[cur][1] = childCount;
	for (int child : adj[cur]) {
		if (child != par) {
			go(child, cur, ans);
			for (int i = n; i >= 1; --i) {
				if (dp[cur][i] != INF) {
					for (int j = 0; j <= n; ++j) {
						if (dp[child][j] != INF) {
							dp[cur][i+j] = min(
								dp[cur][i + j],
								dp[cur][i] - 1 + dp[child][j]
								);
						}
					}
				}			
			}
		}
	}
	if (par == 0) {
		ans = min(ans, dp[cur][p]);
	} else {
		ans = min(ans, dp[cur][p] + 1);
	}
}

int main() {
#ifdef _DEBUG
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	std::ios::sync_with_stdio(false);

	int u, v;
	cin >> n >> p;
	while (cin >> u >> v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dp.resize(n + 1, vi(n + 1, INF));
	int ans = INF;
	go(1, 0, ans);

	cout << ans;

	return 0;
}