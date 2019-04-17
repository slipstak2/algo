// https://informatics.mccme.ru/mod/statements/view3.php?id=766&chapterid=1793#1
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

int fastLIS(const vi& a) {
   vi dp(a.size());
   dp[0] = 1;
   vi v = {a[0]};
   for (int i = 1; i < a.size(); ++i) {
      auto it = lower_bound(v.begin(), v.end(), a[i]);
      if (it == v.end()) {
         v.push_back(a[i]);
         dp[i] = v.size();
      } else if (*it > a[i]){
         *it = a[i];
         dp[i] = it - v.begin();
      }
   }
   return *max_element(dp.begin(), dp.end());
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);
   ll n, a1, k, b, m;
   cin >> n >> a1 >> k >> b >> m;
   vi a(n);
   a[0] = a1;
   for (int i = 1; i < n; ++i) {
      a[i] = (k * a[i - 1] + b) % m;
   }

   cout << fastLIS(a);

   /*
   vi v = {1, 2, 2, 3, 5, 7};
   auto it2 = lower_bound(v.begin(), v.end(), 2);
   int pos2 = it2 - v.begin();

   auto it4 = lower_bound(v.begin(), v.end(), 4);
   int pos4 = it4 - v.begin();

   auto it8 = lower_bound(v.begin(), v.end(), 8);
   int pos8 = it8 - v.begin();
   */
   return 0;
}