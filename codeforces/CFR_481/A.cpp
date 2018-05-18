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

   int n;
   cin >> n;
   vector<int> a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }

   vector<int> res;
   for (int i = 0; i < n; ++i) {
      bool isFind = false;
      for (int j = i + 1; j < n; ++j) {
         isFind |= a[i] == a[j];
      }
      if (!isFind) {
         res.push_back(a[i]);
      }
   }
   cout << res.size() << endl;
   for (int i = 0; i < res.size(); ++i) {
      cout << res[i] << ' ';
   }
   return 0;
}