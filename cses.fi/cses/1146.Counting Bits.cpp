#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <string>
#include <cstring>
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

   ll n;
   cin >> n;

   ll res = 0;
   for (ll T = 2; T <= 1LL << 50; T *= 2) {
      ll cur = (n + 1) / T * T / 2;
      ll ost = (n + 1) % T - T / 2;
      if (ost > 0) {
         cur += ost;
      }
      res += cur;
   }
   cout << res;

   return 0;
}