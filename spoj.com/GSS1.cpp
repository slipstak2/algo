#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <cmath>
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

const int MAX_N = 50000 + 10;
const double EPS = 1e-6;
int pow2[31];
int minPow2[MAX_N];

class SparseTable {
public:
   SparseTable(const vi &a) {
      int n = a.size();
      int logN = int(ceil(log(n) / log(2)) + EPS);
      data.resize(n, vi(logN + 1));

      
      for (int i = 0; i < n; ++i) {
         data[i][0] = a[i];
      }
      for (int j = 1; j <= logN; ++j) {
         for (int i = 0; i + pow2[j - 1] < n; ++i) {
            int l = i;
            int r = i + pow2[j - 1];
            data[i][j] = max(data[i][j - 1], data[i + pow2[j - 1]][j - 1]);
         }
      }     
   }
   int query(int l, int r) {
      int len = minPow2[r - l + 1];
      return max(data[l][len], data[r - pow2[len] + 1][len]);
   }
private:
   vvi data;
};


void calc_pow2() {
   pow2[0] = 1;
   for (int i = 1; i <= 31; ++i) {
      pow2[i] = pow2[i - 1] * 2;
   }
}

void calc_min_pow2() {
   for (int i = 1, j = 0; i < MAX_N; i*=2, ++j) {
      minPow2[i] = j;
   }
   for (int i = 3; i < MAX_N; ++i) {
      if (!minPow2[i]) {
         minPow2[i] = minPow2[i - 1];
      }
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   calc_pow2();
   calc_min_pow2();
   
   int n;
   cin >> n;
   vi a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }
   SparseTable st(a);

   int tests, l, r;
   cin >> tests;
   while (tests --> 0) {
      cin >> l >> r;
      cout << st.query(l - 1, r - 1) << '\n';
   }
   return 0;
}