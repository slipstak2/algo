#include <iostream>

using namespace std;

int rnd5() {
   return 1 + rand() % 5;
}

int rnd4() {
   while (true) {
      int x = rnd5();
      if (x <= 4) return x;
   }
}

int rnd25() {
   return 5 *(rnd5() - 1) + rnd5();
}

int rnd2() {
   while (true) {
      int x = rnd5() - 1;
      if (x != 4) return x % 2 + 1;
   }
}

int rnd8() {
   return (rnd2() - 1) * 4 + (rnd2() - 1) * 2 + rnd2();
}

int rnd7() {
   while (true) {
      int x = rnd8() - 1;
      if (x != 0) return x;
   }
}

int main() {

   const int CHECK_CNT = 30;
   int check[CHECK_CNT] = {0};
   const int ITER_CNT = 1000000;
   for (int i = 0; i < ITER_CNT; ++i) {
      check[rnd25()]++;
   }

   for (int i = 0; i < CHECK_CNT; ++i) {
      cout.width(3);
      cout << i << ' ' << check[i] << endl;
   }
   return 0;
}