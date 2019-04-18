//https://informatics.mccme.ru/mod/statements/view3.php?id=813&chapterid=3089

#pragma comment (linker, "/STACK:256000000")
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

int n, W;
vi w, c;

const int INF = (int)1e9;
const int MAX_C = (int)1e4 + 1;
const int MAX_N = (int)1e2 + 1;
int dp[MAX_C][MAX_N];

int solve(int W, int k) {
   if (W < 0) return -INF;
   if (W == 0) return 0;
   if (k == -1) return 0;

   int &res = dp[W][k];
   if (res == -1) {
      res = max(
         solve(W - w[k], k - 1) + c[k],
         solve(W, k - 1)
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

   cin >> n >> W;
   w.resize(n);
   for (int i = 0; i < n; ++i) {
      cin >> w[i];
   }
   c.resize(n);
   for (int i = 0; i < n; ++i) {
      cin >> c[i];
   }

   memset(dp, -1, sizeof(dp));
   cout << solve(W, n - 1);

   return 0;
}