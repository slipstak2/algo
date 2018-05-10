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

   string str;
   cin >> str;
   int items = 0, links = 0;
   for (int i = 0; i < str.size(); ++i) {
      if (str[i] == 'o') {
         items++;
      } else {
         links++;
      }
   }
   bool isOK = false;
   if (items == 1) {
      isOK = true;
   } else {
      if (items != 0) {
      isOK = (links % items == 0);
      } else {
         isOK = true;
      }
   }
   cout << ( isOK ? "YES": "NO");
   return 0;
}