#define _CRT_SECURE_NO_WARNINGS
 
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <iostream>
#include <algorithm>
 
using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;
 
#define all(c) c.begin(),c.end()
#define STR(c) string(1, c)
 
const int INF = (int)1e9;
const int MAX_N = (int)1e5;
 
int solve_slow(int n) {
    vi dp(max(3, n + 1), INF);
    dp[0] = 0;
    dp[1] = 0;
    dp[2] = 2;
 
    for (int i = 3; i <= n; ++i) {
        int & res = dp[i];
        for (int f = 1; f < i; ++f) {
            int cur = max(2 + dp[f], 1 + dp[i - f]);
            res = min(res, cur);
        }
    }
    return dp[n];
}
int solve_fast(int n) {
    if (n == 1) return 0;
    n -= 2;
    vi F(30), prefix(30);
    F[0] = 1; prefix[0] = 1;
    F[1] = 1; prefix[1] = prefix[0] + F[1];
    for (int i = 2; F[i-1] <= MAX_N ;++i) {
        F[i] = F[i-1] + F[i-2];
        prefix[i] = prefix[i-1] + F[i];
    }
    return 2 + (upper_bound(prefix.begin(), prefix.end(), n) - prefix.begin());
 
}
int main() {
#ifdef _DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    std::ios::sync_with_stdio(false);
 
    int n;
    while (cin >> n) {
        cout << solve_fast(n) << endl;
    }
 
    return 0;
}