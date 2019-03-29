// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=293

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

vi coins = { 1, 5, 10, 25, 50 };
const int MAX_CNT = 30000 + 1;
ll dp[MAX_CNT][5];

void solve() {
   for (size_t i = 0; i < coins.size(); ++i) {
      dp[0][i] = 1;
   }

   for (int i = 1; i < MAX_CNT; ++i) {
      for (int j = coins.size() - 1; j >= 0; --j) {
         for (int k = 0; k <= j; ++k) {
            if (i - coins[k] >= 0) {
               dp[i][j] += dp[i - coins[k]][k];
            }
         }
      }
   }
}

void output(int sum) {
   const ll& res = dp[sum][coins.size() - 1];
   if (res == 1) {
      printf("There is only 1 way to produce %d cents change.\n", sum);
   }
   else {
      printf("There are %lld ways to produce %d cents change.\n", res, sum);
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   //ios::sync_with_stdio(0);

   solve();
   int sum;
   while (cin >> sum) {
      output(sum);
   }
   return 0;
}