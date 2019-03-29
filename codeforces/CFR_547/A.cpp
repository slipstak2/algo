#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   const int INF = (int)1e9;
   int n, m;
   cin >> n >> m;

   map<int, int> dp;
   dp[n] = 0;
   set<int> q;
   q.insert(n);
   while (!q.empty()) {
	   int cur = *q.begin();
	   q.erase(cur);
	   if (cur != n) {
		   if (dp.find(cur) == dp.end()) {
			   dp[cur] = INF;
		   }
		   if (cur % 2 == 0) {
			   if (dp.find(cur / 2) == dp.end()) {
				   dp[cur / 2] = INF;
			   }
			   dp[cur] = min(dp[cur], dp[cur / 2] + 1);
		   }
		   if (cur % 3 == 0) {
			   if (dp.find(cur / 3) == dp.end()) {
				   dp[cur / 3] = INF;
			   }
			   dp[cur] = min(dp[cur], dp[cur / 3] + 1);
		   }
	   }
	   if (cur * 2 <= m) q.insert(cur * 2);
	   if (cur * 3 <= m) q.insert(cur * 3);
   }


   if (dp.find(m) == dp.end()) {
	   cout << -1;
   }
   else {
	   cout << dp[m];
   }



   return 0;
}