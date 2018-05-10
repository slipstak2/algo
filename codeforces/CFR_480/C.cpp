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

   int n, k, x;
   cin >> n >> k;
   
   vector<int> value(256, -1);
   for (int i = 0; i < n; ++i) {
      cin >> x;
      if (value[x] == -1) {
         int begin = max(x - k + 1 , 0);
         int usedPos = -1;
         for (int i = x - 1; i >= begin; --i) {
            if (value[i] != -1) {
               usedPos = i;
               break;
            }
         }
         if (usedPos == -1) { // not found group
            for (int i = begin; i <= x; ++i) {
               value[i] = begin;
            }
         } else { // found group
            int begin = value[usedPos];
            
            int fillValue = -1;
            if (x <= begin + k - 1) { // inc group
               fillValue = value[usedPos];
            } else { // new group
               fillValue = usedPos + 1;
            }
            for (int i = usedPos + 1; i <= x; ++i) {
               value[i] = fillValue;
            }
         }
      }
      cout << value[x] << ' ';
   }



   return 0;
}