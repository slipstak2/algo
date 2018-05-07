#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

#define For(i, st, en) for(int i=(st); i<=(int)(en); i++)
#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define fori(it, x) for (auto it = (x).begin(); it != (x).end(); it++)

bool correctAns(int ans) {
   return 1 <= ans && ans <= (int)1e9;
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   int n, k;
   cin >> n >> k;
   vector<int> a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }

   sort(a.begin(), a.end());
   if (k != 0) {
      int ans = a[k - 1];

      int cnt = upper_bound(a.begin(), a.end(), ans) - a.begin();
      if (cnt == k && correctAns(ans)) {
         cout << ans;
      }
      else {
         cout << -1;
      }
   } else { // k == 0
      int ans = a[0] - 1;
      if (correctAns(ans)) {
         cout << ans;
      } else {
         cout << -1;
      }
   }

   return 0;
}