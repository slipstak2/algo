#include <iostream>

using namespace std;

typedef long long ll;

int main() {
   ll n, m, a;
   cin >> n >> m >> a;

   ll w = (n - 1) / a + 1;
   ll h = (m - 1) / a + 1;
   cout << w * h;

   return 0;
}