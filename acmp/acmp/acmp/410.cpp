#define _CRT_SECURE_NO_WARNINGS
 
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> v2i;
 
const int INF = 1e9;
 
const int DIGITS = 1000;
int n, m;
 
struct state {
    int radix;
    int mod;
    int dig;
    state() : radix(-1), mod(-1), dig(-1) {}
    state(int radix, int mod, int dig): radix(radix), mod(mod), dig(dig) {}
};
 
 
int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
 
    cin >> n >> m;
    v2i dp(DIGITS, vi(m, INF));
 
    vector<vector<state>> prv(DIGITS, vector<state>(m));
 
    int pow10 = 1;
    dp[0][n % m] = 0;
    for (int radix = 1; radix < DIGITS; ++radix) {
        dp[radix] = dp[radix - 1];
        prv[radix] = prv[radix - 1];
        for (int mod = 0; mod < m; ++mod) {
            for (int dig = 0; dig <= 9; ++dig) {
                int nextMod = (pow10 * dig + mod) % m; 
                if (dp[radix][nextMod] > dp[radix - 1][mod] + dig) {
                    dp[radix][nextMod] = dp[radix - 1][mod] + dig;
                    prv[radix][nextMod] = state(radix - 1, mod, dig);
                }
            }
        }
        pow10 = (pow10 * 10) % m;
    }
 
    state s = prv[DIGITS - 1][0];
    while (s.radix != -1) {
        cout << s.dig;
        for (int i = 0; i < s.radix - prv[s.radix][s.mod].radix - 1; ++i) {
            cout << 0;
        }
        s = prv[s.radix][s.mod];
    }
 
    return 0;
}