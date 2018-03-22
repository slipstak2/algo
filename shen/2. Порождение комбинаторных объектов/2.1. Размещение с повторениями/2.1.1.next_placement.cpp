// https://informatics.mccme.ru/mod/statements/view3.php?id=211&chapterid=82

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> vi;
typedef vi::iterator Iter;

int n, k;
bool next_placement(Iter first, Iter last) {
   if (first == last) {
      return false;
   }
   Iter it = --last;
   do {
      (*it)++;
      if (*it == n) {
         *it = 0;
         if (it == first) {
            return false;
         }
         --it;
      }
      else {
         break;
      }
   } while (first <= it);
   return true;
}

int main() {
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);

   cin >> k >> n;
   vector<int> placement(k, 0);

   do {
      for (auto item: placement) {
         cout << item;
      }
      cout << endl;
   } while (next_placement(placement.begin(), placement.end()));

   return 0;
}