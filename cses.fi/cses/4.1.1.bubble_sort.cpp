// https://informatics.mccme.ru/mod/statements/view3.php?id=271&chapterid=233
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

int n;
void bubble_sort(vector<int>& a) {
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n - 1; ++j) {
         if (a[j] > a[j + 1]) {
            swap(a[j], a[j + 1]);
         }
      }
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   cin >> n;
   vi a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }
   bubble_sort(a);
   for (int i = 0; i < n; ++i) {
      cout << a[i] << ' ';
   }

   return 0;
}