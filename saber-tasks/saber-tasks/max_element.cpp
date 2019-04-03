/*
Дается два различных натуральных числа a и b (1 <= a, b <= 1000)
Нужно найти максимум двух чисел используя операции:
+, -, /, %, * и скобки

P.S: усложенный вариант: числа могут быть равны
*/

#include <iostream>
#include <cassert>

using namespace std;

#define NORM(x) (2 - (x + 2) / (x + 1))

int _MAX_IGOR_UPDATE(int a, int b) {
   return NORM(a / b) * a + (1 - NORM(a / b)) * b;
}

int _MAX_NASTYA(int a, int b) {
   return a + (b - a) * (a % b / a);
}

int _MAX_NASTYA_MIX(int a, int b) {
   return a + (b - a) * NORM(b / a);
}

int _MAX_EUGEN_8(int a, int b) {
   return (a * (a / b) + b * (b / a)) / (a / b + b / a);
}

typedef int (*MAX_FUNC)(int, int); 
void check(MAX_FUNC f) {
   assert(f(2, 7) == 7);
   assert(f(9, 3) == 9);
   assert(f(11, 11) == 11);
}

int main() {
   check(_MAX_IGOR_UPDATE);
   check(_MAX_NASTYA);
   check(_MAX_NASTYA_MIX);
   check(_MAX_EUGEN_8);

   return 0;
}