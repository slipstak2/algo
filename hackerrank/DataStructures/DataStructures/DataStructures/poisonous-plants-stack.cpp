#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <cmath>
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

const int INF = 1e9;
struct plant {
   int val;
   int day;
   plant()
      : val(0)
      , day(-1)
   {}
   plant(int val, int day)
      : val(val)
      , day(day)
   {}
   static plant createRoot(int val) {
      return plant(val, INF);
   }
};


int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n, val;
   cin >> n;

   vector<plant> s;
   vi a;
   
   cin >> val;
   s.push_back(plant::createRoot(val));

   int res = 0;
   for (int i = 1; i < n; ++i) {
      cin >> val;
      if (val > s.back().val) {
         s.push_back(plant(val, 1));
         res = max(res, 1);
      } else {
         int day = s.back().day + 1;
         while (!s.empty() && (s.back().day < day || val <= s.back().val)) {
            day = max(day, s.back().day + 1);
            s.pop_back();            
         }
         if (s.empty()) {
            s.push_back(plant::createRoot(val));
         } else {
            s.push_back(plant(val, day));
            res = max(res, day);
         }
      }
   }

   cout << res;
   return 0;
}