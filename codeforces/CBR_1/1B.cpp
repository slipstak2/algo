#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int ALPH = 26;

string toStr(int n) {
   string res;
   do {
      n--;
      res += 'A' + n % ALPH;
      n  /= ALPH;
   } while (n);
   reverse(res.begin(), res.end());
   return res;
}

int toInt(string s) {
   int n = 0;
   for (int i = 0; i < s.size(); ++i) {
      n *= ALPH;
      n += s[i] - 'A' + 1;
   }
   return n;
}


int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

  
   char buf[1000], COL[15];
   char ans[1000];
   int row, col;
   int t;
   scanf("%d", &t);
   while (t--) {
      scanf("%s", buf);
      if (sscanf(buf, "R%dC%d", &row, &col) == 2) {
         printf("%s%d\n", toStr(col).c_str(), row);
      }
      else {
         sscanf(buf, "%[A-Z]%d", &COL, &row);
         printf("R%dC%d\n", row, toInt(COL));
      }
   }

   return 0;
}