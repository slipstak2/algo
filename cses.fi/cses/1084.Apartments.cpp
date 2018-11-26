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

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n, m, maxDelta;
   cin >> n >> m >> maxDelta;

   vi man(n);
   for (int i = 0; i < n; ++i) {
      cin >> man[i];
   }
   sort(man.begin(), man.end());

   vi apart(m);
   for (int j = 0; j < m; ++j) {
      cin >> apart[j];
   }
   sort(apart.begin(), apart.end());

   int cnt = 0;
   for (int i = 0, j = 0; i < man.size() && j < apart.size(); ) {
      int curMan = man[i];
      int curApart = apart[j];
      if (man[i] - maxDelta <= apart[j] && apart[j] <= man[i] + maxDelta) {
         cnt++;
         ++i; ++j;
      } else if (man[i] - maxDelta < apart[j]) {
         ++i;
      } else if (apart[j] < man[i] + maxDelta) {
         ++j;
      }
   }
   cout << cnt;
   return 0;
}