#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   ios::sync_with_stdio(0);

   long long n;
   cin >> n;   
   while (true) {
      cout << n << ' ';
      if (n == 1) break;
      if (n & 1) n = 3 * n + 1;
      else       n >>= 1;
   }

   return 0;
}