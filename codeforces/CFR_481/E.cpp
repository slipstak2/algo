#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long INT;

int n, w;
vector<INT> delta;

int can(INT first) {
   INT cur = first;
   for (int i = 0; i < delta.size(); ++i) {
      cur += delta[i];
      if(cur < 0) {
         return 1;
      } else if (w < cur) {
         return -1;
      }
   }
   return 0;
}
INT find_min() {
   INT l = 0, r = w;
   INT res = -1;
   while (l <= r) {
      INT m = (l + r) / 2;
      INT canR = can(m);
      if (canR == 0) {
         res = m;
         r = m - 1;
      } else if (canR == 1) {
         l = m + 1;
      } else if (canR == -1) {
         r = m - 1;
      }
   }
   return res;
}

INT find_max() {
   INT l = 0, r = w;
   INT res = -1;
   while (l <= r) {
      INT m = (l + r) / 2;
      INT canR = can(m);
      if (canR == 0) {
         res = m;
         l = m + 1;
      }
      else if (canR == 1) {
         l = m + 1;
      }
      else if (canR == -1) {
         r = m - 1;
      }
   }
   return res;
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   cin >> n >> w;
   delta.resize(n);

   for (int i = 0; i < n; ++i) {
      cin >> delta[i];
   }

   INT first = find_min();
   INT last = find_max();
   if (first == -1 || last == -1) {
      cout << 0;
   } else {
      cout << last - first + 1;
   }
   
   return 0;
}