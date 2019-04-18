#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <string>
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

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n, SUM;
   cin >> n >> SUM;
   vi cost(n);
   for (int i = 0; i < n; ++i) {
      cin >> cost[i];
   }
   vi page(n);
   for (int i = 0; i < n; ++i) {
      cin >> page[i];
   }

   vi dp(SUM + 1, -1);


   dp[0] = 0;
   for (int i = 0; i < n; ++i) {
      for (int x = SUM - cost[i]; x >= 0; --x) {
         if (dp[x] != -1) {
            dp[x + cost[i]] = max(dp[x + cost[i]], dp[x] + page[i]);
         }
      }
   }
   cout << *max_element(dp.begin(), dp.end());


   return 0;
}