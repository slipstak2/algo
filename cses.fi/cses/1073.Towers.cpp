#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
typedef pair<int, int> pi;
typedef set<int>      si;
typedef multiset<int> msi;

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

   int n, x;
   msi cubes;
   cin >> n;
   for (int i = 0; i < n; ++i) {
      cin >> x;
      auto it = cubes.upper_bound(x);
      if (it == cubes.end()) {
         cubes.insert(x);
      } else {
         cubes.erase(it);
         cubes.insert(x);
      }
   }
   cout << cubes.size();
   return 0;
}