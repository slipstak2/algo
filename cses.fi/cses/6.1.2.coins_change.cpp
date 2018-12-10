// http://acmp.ru/index.asp?main=task&id_task=407

#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
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

const int INF = 1e9;

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);
   int n;
   cin >> n;
   vi coins(n);
   for (int i = 0; i < n; ++i) {
      cin >> coins[i];
   }
   int cost;
   cin >> cost;
   vi dp(cost + 1, INF);
   dp[0] = 0;
   for (int i = 1; i < dp.size(); ++i) {
      for (int coin: coins) {
         if (i - coin >= 0) {
            dp[i] = min(dp[i], dp[i-coin] + 1);
         }
      }
   }

   cout << (dp[cost] == INF ? -1 : dp[cost]);



   return 0;
}