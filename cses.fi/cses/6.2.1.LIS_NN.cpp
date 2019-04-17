
//https://informatics.mccme.ru/mod/statements/view3.php?id=766&chapterid=205#1

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

   int n;
   cin >> n;
   vi a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }

   vi dp(n);
   for (int k = 0; k < n; ++k) {
      dp[k] = 1;
      for (int i = 0; i < k; ++i) {
         if (a[i] < a[k]) {
            dp[k] = max(dp[k], dp[i] + 1);
         }
      }
   }

   cout << *max_element(dp.begin(), dp.end());
   
   return 0;
}