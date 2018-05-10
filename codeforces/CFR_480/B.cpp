#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

#define For(i, st, en) for(int i=(st); i<=(int)(en); i++)
#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define fori(it, x) for (auto it = (x).begin(); it != (x).end(); it++)

int n = 4, m, k;
vector<vector<char>> f, s;

struct cell{
   int steps;
   int ways;
   cell() : steps(0), ways(0) {}
   cell(int steps, int ways) : steps(steps), ways(ways) {}
};


const int INF = (int)1e9;

int getSteps(
   const vector<vector<char>> & a, 
   vector<vector<cell> > &dp,
   int x, 
   int y, 
   bool allowHostel
) {
   if(a[x][y]  == '#' && !allowHostel) {
      return INF;
   }
   return dp[x][y].steps;
}
int calc(const vector<vector<char>> & a) {
   vector<vector<cell> > dp(n, vector<cell>(m));

   dp[0][0] = cell(0, 1);
   for (int i = 1; i < n; ++i) dp[i][0] = cell(i, 1);
   for (int j = 1; j < m; ++j) dp[0][j] = cell(j, 1);

   for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
         int upSteps   = getSteps(a, dp, i - 1, j, a[i][j] != '#');
         int leftSteps = getSteps(a, dp, i, j - 1, a[i][j] != '#');

         int minSteps = min(upSteps, leftSteps);
         dp[i][j].steps = minSteps + 1;

         if (upSteps == minSteps) {
            dp[i][j].ways += dp[i - 1][j].ways;
         }
         if (leftSteps == minSteps) {
            dp[i][j].ways += dp[i][j - 1].ways;
         }
      }
   }
   return dp.back().back().ways;
}
void research() {

   cin >> m >> k;
   f.resize(n, vector<char>(m));
   s = f;
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         cin >> f[i][j];
         s[n-i-1][j] = f[i][j];
      }
   }
   cout << calc(f) << ' ' <<calc(s);
}

void fill_row(int left, int right, int row, vector<vector<char> > &field, int &k) {
   while (k > 1 && left != right) {
      field[row][left++] = field[row][right--] = '#';
      k -= 2;
   }
}

void solve() {
   cin >> n >> k;
   vector<vector<char> > field(4, vector<char>(n, '.'));
   int left = 1, right = n - 2;
   fill_row(left, right, 1, field, k);
   if (k >= 2) {
      fill_row(left, right, 2, field, k);
   }
   for (int row = 1; row <= k; ++row) {
      field[row][n/2] = '#';
   }

   cout << "YES" << endl;
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < n; ++j) {
         cout << field[i][j];
      }
      cout << endl;
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   //research();
   solve();

   return 0;
}