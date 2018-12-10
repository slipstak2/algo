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

ll f(const vi&sticks, int m) {
   ll res = 0;
   for (int len: sticks) {
      res += abs(len - m);
   }
   return res;
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n;
   cin >> n;
   vi sticks(n);
   for (int i = 0; i < n; ++i) {
      cin >> sticks[i];
   }

   int l = 0, r = 1e9 + 10;
   while (r - l >= 3) {
      int a = l + (r - l) / 3;
      int b = r - (r - l) / 3;
      if (f(sticks, a) <= f(sticks, b)) {
         r = b;
      } else {
         l = a;
      }
   }
   ll res = f(sticks, l);
   for (int i = l; i <= r; ++i) {
      res = min(res, f(sticks, i));
   }
   cout << res;
   return 0;
}