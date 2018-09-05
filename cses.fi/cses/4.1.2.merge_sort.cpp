// https://informatics.mccme.ru/mod/statements/view3.php?id=1121&chapterid=766
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

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


class MergeSorting
{
public:
   MergeSorting(vi &mas) 
      : a(mas)
   {}

   void run() {
      if (a.size() > 1) {
         vi buf(a.begin(), a.end());
         merge_sort(a, buf, 0, a.size() - 1);
         a.swap(buf);
      }
   }
private:
   void insertion_sort(vi &src, int l, int r) {
      for (int i = l + 1; i <= r; ++i) {
         for (int j = i; j > l; j--) {
            if (src[j - 1] > src[j]) {
               swap(src[j - 1], src[j]);
            } else {
               break;
            }
         }
      }
   }

   void merge_sort(vi& src, vi& dst, int l, int r) {
      if (r - l <= 32) {
         insertion_sort(dst, l, r);
      }
      else {
         int m = l + (r - l) / 2;
         merge_sort(dst, src, l, m);
         merge_sort(dst, src, m + 1, r);
         merge(&src[0], &dst[0], l, m, r);
      }
   }

   void merge(int* src, int* dst, int l, int m, int r) {
      int i = l, j = m + 1;
      for (int p = l; p <= r; ++p) {
         if (i == m + 1)      dst[p] = src[j++];
         else if (j == r + 1) dst[p] = src[i++];
         else                 dst[p] = src[i] < src[j] ? src[i++] : src[j++];
      }
   }

private:
   vi& a;
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
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }

   MergeSorting(a).run();

   for (int i = 0; i < n; ++i) {
      cout << a[i] << ' ';
   }

   return 0;
}