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

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   int len;
   string str;
   cin >> len;
   cin >> str;
   map<string, int> mem;
   for (int i = 0; i < len - 1; ++i) {
      string cur = str.substr(i, 2);
      mem[cur] ++;
   }
   int max_cnt = -1;
   string res = "";
   for (map<string, int>::iterator it = mem.begin(); it != mem.end(); ++it) {
      if (it->second > max_cnt) {
         max_cnt = it->second;
         res = it->first;
      }
   }

   cout << res;
   return 0;
}