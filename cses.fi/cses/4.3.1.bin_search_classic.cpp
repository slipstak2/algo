// https://informatics.mccme.ru/mod/statements/view3.php?id=192&chapterid=4#1
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)


bool bin_search(const vi &a, int x) {
   int l = 0, r = a.size() - 1;
   while (l <= r) {
      int m = (l + r) >> 1;
      if (a[m] < x) {
         l = m + 1;
      } else if (x < a[m]) {
         r = m - 1;
      } else {
         return true;
      }
   }
   return false;
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n, m, x;
   cin >> n >> m;
   vi a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }

   for (int j = 0; j < m; ++j) {
      cin >> x;
      cout << (bin_search(a, x) ? "YES" : "NO") << endl;
   }

   return 0;
}