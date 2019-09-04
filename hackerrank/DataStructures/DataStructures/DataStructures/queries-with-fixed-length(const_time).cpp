#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <stack>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<int>     vi;

vi ans;
vi a;

int n;
struct Item {
   int val, pos;
   Item():val(0), pos(0){};
   Item(int val, int pos): val(val), pos(pos){}
};

void find_left_max(vi &left, const vi& a) {
   left.resize(n);
   stack<Item> s;
   for (int i = 0; i < n; ++i) {
      while (!s.empty() && s.top().val <= a[i]) {
         s.pop();
      }
      if (s.empty()) {
         left[i] = -1;
      }
      else {
         left[i] = s.top().pos;
      }
      s.push(Item(a[i], i));
   }
}
void precalc() {
   vi left;
   find_left_max(left, a);
   vi a_reverse(a.begin(), a.end());
   reverse(a_reverse.begin(), a_reverse.end());
   vi right;
   find_left_max(right, a_reverse);
   
   for (int i = 0; i < n; ++i) {
      right[i] = n - 1 - right[i];
   }
   reverse(right.begin(), right.end());
   vi len(n);
   for (int i = 0; i < n; ++i) {
      len[i] = right[i] - left[i] - 1;
   }

   const int INF = (int) 1e9;
   
   ans.resize(n + 1, INF);
   for (int i = 0; i < n; ++i) {
      ans[len[i]] = min(ans[len[i]], a[i]);
   }

   ans[n] = *max_element(a.begin(), a.end());
   for (int i = n - 1; i >= 0; --i) {
      if (ans[i] == INF) {
         ans[i] = ans[i + 1];
      }
      ans[i] = min(ans[i], ans[i + 1]);
   }
}


int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int q, d;
   cin >> n >> q;
   a.resize(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }

   precalc();

   while (q --> 0) {
      cin >> d;
      cout << ans[d] << '\n';
   }

   return 0;
}