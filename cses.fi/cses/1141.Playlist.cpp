#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <unordered_set>

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

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int beg = 0;
   size_t cnt = 0;
   int n;
   cin >> n;
   vi a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }

   unordered_set <int> s;
   for (int i = 0; i < n; ++i) {
      const int &x = a[i];
      if (s.find(x) != s.end()) {
         do {
            s.erase(a[beg]);
         } while (a[beg++] != x);
      }
      s.insert(x);
      cnt = max(cnt, s.size());
   }
   cout << cnt;

   return 0;
}