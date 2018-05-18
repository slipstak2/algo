#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   int n, e;
   cin >> n >> e;
   vector<int> r(n);
   for (int i = 0; i < n; ++i) {
      cin >> r[i];
   }
   vector<int> delta(n);
   int u, v;
   for (int j = 0; j < e; ++j) {
      cin >> u >> v;
      --u; --v;
      if (r[u] < r[v]) {
         swap(u, v);
      }
      if (r[u] > r[v]) {
         delta[u]++;
      }
   }

   vector<int> sr = r;
   sort(sr.begin(), sr.end());

   for (int i = 0; i < n; ++i) {
      auto it = upper_bound(sr.begin(), sr.end(), r[i] - 1);
      int lessR = it - sr.begin();
      cout << lessR - delta[i] << ' ';
   }



   return 0;
}