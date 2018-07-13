#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<int> vi;

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   ios::sync_with_stdio(0);
   ll n;
   cin >> n;
   ll sum = 0, cur;
   for (int i = 0; i < n - 1; ++i) {
      cin >> cur;
      sum += cur;
   }
   cout << n * (1 + n) / 2 - sum;

   return 0;
}