// https://stepik.org/lesson/221951/step/1?unit=194888
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

ifstream cin("input.txt");
ofstream cout("output.txt");


vector<bool> precalc_can;

inline int bit_val(int mask, int bit) {
   return (mask & (1 << bit)) == 0 ? 0 : 1;
}
void precalc(int n) {
   for (int mask = 0; mask < (1 << n); ++mask) {
      int bit = 0;
      bool is_ok = true;
      while (bit < n) {
         while (bit < n && bit_val(mask, bit) == 1) ++bit;			// skip 1's
         int cnt = 0;
         while (bit < n && bit_val(mask, bit) == 0) ++bit, ++cnt; // calc 0's
         if (cnt & 1) {
            is_ok = false;
            break;
         }
      }
      precalc_can[mask] = is_ok;
   }
}

bool can(int mask, int new_mask) {
   if ((mask & new_mask) != 0) {
      return false;
   }
   return precalc_can[mask | new_mask];
}

int main() {
   int n, m, k;
   cin >> n >> m >> k;
   precalc_can.resize(1 << n);
   precalc(n);

   vvi dp(m + 1, vi(1 << n));
   dp[0][0] = 1;
   for (int i = 0; i < m; ++i) {
      for (int mask = 0; mask < (1 << n); ++mask) {
         for (int new_mask = 0; new_mask < (1 << n); ++new_mask) {
            if (can(mask, new_mask)) {
               dp[i + 1][new_mask] = (dp[i + 1][new_mask] + dp[i][mask]) % k;
            }
         }
      }
   }
   cout << dp[m][0] << endl;

   return 0;
}