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

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

#define POSSIBLE   cout << "Possible";    return 0;
#define IMPOSSIBLE cout << "Impossible";  return 0;

   double h, w, H, W;
   cin >> h >> w;
   cin >> H >> W;
   if (h > w) swap(h, w);
   if (H > W) swap(H, W);
   if (h <= H && w <= W) {
      POSSIBLE;
   }

   if (H < h){
      IMPOSSIBLE;
   }

#define sqr(x) (x) * (x)

   if (sqr((H + W) / (h + w)) + sqr((H - W) / (h - w)) >= 2.0) {
      POSSIBLE;
   } else {
      IMPOSSIBLE;
   }

   return 0;
}