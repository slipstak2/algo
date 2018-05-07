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

map<int, int> dp, ind, prv;

void go(int pos) {
   if (prv[pos] != -1) {
      go(prv[pos]);
   }
   cout << pos + 1 << ' ';
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   int n;
   cin >> n;
   vector<int> a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }
   for (int i = 0; i < n; ++i) {
      map<int, int>::iterator it = dp.find(a[i] - 1);
      if (it == dp.end()) {
         dp[a[i]] = 1;
         ind[a[i]] = i;
         prv[i] = -1;
      } else {
         if (dp[a[i]] < dp[a[i]-1] + 1) {
             dp[a[i]] = dp[a[i]-1] + 1;
             ind[a[i]] = i;
             prv[i] = ind[a[i]-1];
         }         
      }
   }

   int maxCount = -1;
   int pos = -1;
   for (map<int, int>::iterator it = dp.begin(); it != dp.end(); ++it) {
      if (maxCount < it->second) {
         maxCount = it->second;
         pos = ind[it->first];
      }
   }

   cout << maxCount << endl;
   go(pos);

   return 0;
}