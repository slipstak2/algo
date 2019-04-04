/*
https://informatics.mccme.ru/moodle/mod/statements/view3.php?chapterid=2958

Дается два различных натуральных числа a и b (1 <= a, b <= 1000)
Нужно найти максимум двух чисел используя операции:
+, -, /, %, * и скобки

P.S: усложенный вариант: числа могут быть равны
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

//            | 0, if (x = 0)
// norm(x) = <
//            | 1, if (x != 0)
int norm(int x) {
   return 2 - (x + 2) / (x + 1);
}

//              | 0, if (a >= b)
// cmp(a, b) = <
//              | 1, if (a < b)
int cmp(int a, int b) {
   return (a % b) / a;
}

// |a - b|
int abs_a_minus_b(int a, int b) {
   return cmp(b, a) * (a - b) + cmp(a, b) * (b - a);
}

int _MAX_IGOR(int a, int b) {
   return norm(a / b) * a + (1 - norm(a / b)) * b;
}

int _MAX_NASTYA(int a, int b) {
   return a + (b - a) * (a % b / a);
}

int _MAX_NASTYA_MIX(int a, int b) {
   return a + (b - a) * norm(b / a);
}

int _MAX_EUGEN_8(int a, int b) {
   return (a * (a / b) + b * (b / a)) / (a / b + b / a);
}

int _MAX_ABS(int a, int b) {
   return (abs_a_minus_b(a, b) + a + b) / 2;
}

typedef int (*MAX_FUNC)(int, int); 

vector<MAX_FUNC> funcs = {
   _MAX_IGOR,
   _MAX_NASTYA,
   _MAX_NASTYA_MIX,
   _MAX_EUGEN_8,
   _MAX_ABS
};

void check(MAX_FUNC f) {
   assert(f(2, 7) == 7);
   assert(f(9, 3) == 9);
   assert(f(11, 11) == 11);
}

int solve(int a, int b) {
   vector<int> answers;

   for (auto func: funcs) {
      answers.push_back(func(a, b));
   }

   assert(all_of(answers.begin(), answers.end(), 
      [a, b](int ans) { 
         return ans == max(a, b); 
      })
   );
   return _MAX_IGOR(a, b);
}
int main() {
   for (auto func: funcs) {
      check(func);
   }

   int a, b;
   cin >> a >> b;

   cout << solve(a, b);

   return 0;
}