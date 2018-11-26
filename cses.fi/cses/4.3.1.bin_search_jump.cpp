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


bool bin_search_jump(const vi &a, int x) {
   int pos = 0;
   int n = a.size();
   for (int jump = n / 2; jump >= 1; jump >>= 1) {
      while (pos + jump < n && a[pos + jump] <= x) {
         pos += jump;
      }
   }
   return a[pos] == x;
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
      cout << (bin_search_jump(a, x) ? "YES" : "NO") << endl;
   }

   return 0;
}