#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
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

void output(const vi& a) {
   cout << a.size() << endl;
   for (int i = 0; i < a.size(); ++i) {
      cout << a[i] << ' ';
   }
   cout << endl;
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   ll n;
   cin >> n;
   ll Sn = (1 + n) * n / 2;
   if (Sn & 1) {
      cout << "NO";
   } else {
      cout << "YES" << endl;
      vi a, b;
      a.reserve(n);
      b.reserve(n);

      ll t = Sn / 2;
      for (int i = n; i >= 1; --i) {
         if (i <= t) {
            a.push_back(i);
            t -= i;
         } else {
            b.push_back(i);
         }
      }
      output(a);
      output(b);
   }
   return 0;
}