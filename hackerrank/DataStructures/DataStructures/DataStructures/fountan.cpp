#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
* Complete the 'fountainActivation' function below.
*
* The function is expected to return an INTEGER.
* The function accepts INTEGER_ARRAY a as parameter.
*/

struct segment {
   int l, r;
   segment() :l(0), r(0) {}
   segment(int l, int r) : l(l), r(r) {}
};

bool cmp(const segment& a, const segment& b) {
   if (a.l != b.l) return a.l < b.l;
   return a.r > b.r;
}

int fountainActivation(vector<int> a) {
   int n = a.size();
   vector<segment> s;
   for (int i = 0; i < n; ++i) {
      s.push_back(segment(
         max(i - a[i], 1),
         min(i + a[i], n)
      )
      );
   }
   sort(s.begin(), s.end(), cmp);

   int pos = 0;
   int nxt = 0;

   int cnt = 0;
   while (pos < n) {
      cnt++;
      int border = s[cur].r;
      nxt = cur;      
      while (pos < n && s[pos].l <= border) {
         if (s[pos].r > s[nxt].r) {
            nxt = pos;
         }
         pos++;
      }
      if (cur == nxt) {
         cur = pos;
      } else {
         cur = nxt;
      }
   }
   return cnt;
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n;
   cin >> n;
   vector<int> a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }
   cout << fountainActivation(a);

   return 0;
}
