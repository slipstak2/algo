#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <string.h>
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

const ll INF = 72340172838076673LL;

struct matrix {
   int rows, cols;
};

vector<matrix> m;

const int MAX_N = 10 + 1;
ll dp[MAX_N][MAX_N];
int sep[MAX_N][MAX_N];


ll solve(int l, int r) {
   if (l == r) {
      return 0;
   }
   ll &ref = dp[l][r];
   if (ref != INF) {
      return ref;
   }

   for (int i = l; i + 1 <= r; ++i) {
      ll cur = solve(l, i) + solve(i + 1, r) + m[l].rows * m[i].cols * m[r].cols;
      if (ref > cur) {
         ref = cur;
         sep[l][r] = i;
      }
   }
   return ref;
}

void ans(int l, int r) {
   if (l == r) {
      printf("A%d", l + 1);
   } else {
      printf("(");   ans(l, sep[l][r]);   printf(" x "); ans(sep[l][r] + 1, r);  printf(")");
   }
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n;
   for (int test = 1; ; ++test) {
      scanf("%d", &n);
      if (!n) {
         break;
      }
      m.resize(n);
      for (int i = 0; i < n; ++i) {
         scanf("%d %d", &m[i].rows, &m[i].cols);
      }
      memset(sep, 0, sizeof(sep));
      memset(dp, 1, sizeof(dp));

      solve(0, n- 1);
      printf("\nCase %d: ", test);
      ans(0, n - 1);
   }
   return 0;
}