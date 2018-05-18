#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   int len;
   string s;
   cin >> len;
   cin >> s;
   int cnt = 0;
   while (true) {
      int pos = s.find("xxx");
      if (pos == -1) {
         break;
      }
      s.erase(s.begin() + pos);
      cnt ++;
   }
   cout << cnt;
   
   return 0;
}