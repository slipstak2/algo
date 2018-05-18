#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int moveD[3] = {-1, 0, 1};
const int INF = (int)1e9;

bool can(vector<int> a, int movePos0, int movePos1, int &cnt) {
   cnt += abs(moveD[movePos0]);
   cnt += abs(moveD[movePos1]);
   a[0] += moveD[movePos0];
   a[1] += moveD[movePos1];
   int d = a[1] - a[0];

   for (int i = 2; i < a.size(); ++i) {
      int curD = a[i] - a[i - 1];
      if (abs(curD - d) <= 1) {
         a[i] = a[i - 1] + d;
         cnt += abs(curD - d);
      } else {
         return false;
      }
   }
   return true;
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   int n;
   cin >> n;
   vector<int> a(n);
   for (int i = 0 ;i < n; ++i) {
      cin >> a[i];
   }

   if (n == 1) {
      cout << 0;
      return 0;
   }

   int minCnt = INF;
   for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
         int cnt = 0;
         if (can(a, i, j, cnt)) {
            minCnt = min(minCnt, cnt);
         }
      }
   }
   if (minCnt != INF) {
      cout << minCnt;
   } else {
      cout << -1;
   }

   return 0;
}