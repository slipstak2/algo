// https://informatics.mccme.ru/mod/statements/view.php?id=1115#1
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)


class CountingSort {
public:
   CountingSort(vi &mas)
      : a(mas)
   {}

   void run() {
      counting_sort();
   }
private:
   void counting_sort() {
      const int MIN_VALUE = (int)-1e4;
      const int MAX_VALUE = (int)1e4;

      vi met(MAX_VALUE - MIN_VALUE + 1);
      for (size_t i = 0; i < a.size(); ++i) {
         met[a[i] - MIN_VALUE]++;
      }
      int p = 0;
      for (int j = MIN_VALUE ; j <= MAX_VALUE; ++j) {
         for (int i = 0; i < met[j - MIN_VALUE]; ++i) {
            a[p++] = j;
         }
      }

   }
private:
   vi &a;
};

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n;
   cin >> n;
   vi a(n);
   for (size_t i = 0; i < a.size(); ++i) {
      cin >> a[i];
   }
   CountingSort(a).run();
   for (size_t i = 0; i < a.size(); ++i) {
      cout << a[i] << ' ';
   }

   return 0;
}