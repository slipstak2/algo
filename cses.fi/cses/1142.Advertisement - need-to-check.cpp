#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <stack>
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


struct item {
   int pos;
   int val;
};

inline void find_less(const vi& a, vi&l ,int beg, int end, int delta) {
   stack<item> s;
   s.push({beg - delta , -1});

   for (int i = beg; i != end + delta; i += delta) {
      while (s.top().val >= a[i]) {
         s.pop();
      }
      l[i] = s.top().pos;
      s.push({i, a[i]});
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   int n;
   scanf("%d", &n);
   vi a(n);
   for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
   }
   vi l(n), r(n);
   find_less(a, l,     0, n - 1, +1);
   find_less(a, r, n - 1,     0, -1);

   ll res = 0;
   for (int i = 0; i < n; ++i) {
      res = max(res, (ll)a[i] * (r[i] - l[i] - 1));
   }
   printf("%lld", res);

   return 0;
}