#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int>     vi;
typedef vector<vi>     vvi;
typedef vector<ll>     vll;
typedef set<int>        si;
typedef multiset<int>  msi;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)

int n, SUM;
vi page, cost;

const int INF = (int)1e9;
const int MAX_C = (int)1e5 + 1;
const int MAX_N = (int)1e3 + 1;
int dp[MAX_C][MAX_N];

int solve(int C, int k) {
   if (C < 0) return -INF;
   if (C == 0) return 0;
   if (k == -1) return 0;

   int &res = dp[C][k];
   if (res == -1) {
      res = max(
         solve(C - cost[k], k - 1) + page[k],
         solve(C, k - 1)
      );
   }
   return res;
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   cin >> n >> SUM;
   cost.resize(n);
   for (int i = 0; i < n; ++i) {
      cin >> cost[i];
   }
   page.resize(n);
   for (int i = 0; i < n; ++i) {
      cin >> page[i];
   }

   memset(dp, -1, sizeof(dp));

   cout << solve(SUM, n - 1);

   return 0;
}