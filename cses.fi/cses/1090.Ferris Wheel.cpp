#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
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

   int n, x;
   cin >> n >> x;
   vi a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }
   sort(a.begin(), a.end());

   int minPos = 0, cnt = 0;
   for (int i = a.size() - 1; i >=0; --i) {
      if (minPos > i) {
         break;
      }
      if (a[minPos] <= x - a[i]) {
         minPos++;
      }
      ++cnt;
   }
   cout << cnt;

   return 0;
}