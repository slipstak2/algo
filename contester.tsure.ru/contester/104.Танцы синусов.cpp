#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> A;

void outputAn(int n, int k=1) {
   if (k > n) {
      return;
   }
   if (k != 1) {
      printf("%c", k % 2 ? '+' : '-');
   }
   printf("sin(%d", k);
   outputAn(n, k + 1);
   printf(")");
}

void printSn(int n, int tail = 1) {
   if (n != 1) {
      printf("(");
      printSn(n - 1, tail + 1);
      printf(")");
   }
   outputAn(n);
   printf("+%d", tail);
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(false);
   int n;
   scanf("%d", &n);
   printSn(n);

   return 0;
}