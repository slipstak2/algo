// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=114&page=show_problem&problem=293
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

void output(ll ways, int cents) {
   if (ways == 1) {
      printf("There is only %lld way to produce %d cents change.\n", ways, cents);
   } else {
      printf("There are %lld ways to produce %d cents change.\n", ways, cents);
   }
}

const int COINS_CNT = 5;
int coins[COINS_CNT] = {1, 5, 10, 25, 50};
const int MAX_COST = 3e4;
ll dp[MAX_COST + 1];
bool calc[MAX_COST + 1];

int solve(int cost, int last_coin_pos) {
   if(cost < 0) {
      return 0;
   }
   if (calc[cost]) {
      return dp[cost];
   }

   ll& res = dp[cost];
   for (int pos = last_coin_pos; pos >= 0; --pos) {
      res += solve(cost - coins[pos], pos);
   }
   calc[cost] = true;
   return res;
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   dp[0] = 1;
   calc[0] = true;

   int cost;
   while (cin >> cost) {
      output(solve(cost, COINS_CNT - 1), cost);
   }

   return 0;
}