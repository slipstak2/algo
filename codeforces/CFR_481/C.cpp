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

   int n, m;
   cin >> n >> m;

   vector<long long> a(n);
   vector<long long> sum(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
      if (i == 0) {
         sum[i] = a[i];
      } else {
         sum[i] = sum[i - 1] + a[i];
      }
   }

   long long num;
   for (int i = 0; i < m; ++i) {
      cin >> num;
      auto it = lower_bound(sum.begin(), sum.end(), num);
      int pos = it - sum.begin();
      cout << pos + 1 << ' '<< a[pos] - (*it - num) << endl;
   }
   return 0;
}