#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>

using namespace std;


vector<string> A;

void genA(int n) {
   // An=sin(1–sin(2+sin(3–sin(4+...sin(n))...) 
   A[1] = "sin(1";
   char tail[100];
   for (int i = 2; i <= n; ++i) {
      sprintf(tail, "sin(%d", i);
      A[i] = A[i - 1] + (i % 2 ? "+" : "-") + tail;
   }
   for (int i = 1; i <= n; ++i) {
      A[i] += string(i, ')');
   }
}

void outputSn(int n, int tail) {
   if (n != 1) {
      cout << '(';
      outputSn(n - 1, tail + 1);
      cout << ')';
   }
   cout << A[n] << '+' << tail;
}
void genSn(int n) {
   // Sn=(...(A1+n)A2+n-1)A3+...+2)An+1 
   char tail[100];
   string Sn;
   for (int i = 1; i <= n; ++i) {
      sprintf(tail, "+%d", n + 1 - i);
      Sn = "(" + Sn + A[i] + tail + ")";
   }
   Sn.resize(Sn.size() - 1);
   cout << Sn.c_str() + 1;
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   int n;
   cin >> n;
   A.resize(n + 1);
   genA(n);
   //genSn(n);
   outputSn(n, 1);

   return 0;
}