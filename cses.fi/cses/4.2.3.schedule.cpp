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

struct lecture {
   lecture(int beg, int end)
      : beg(beg)
      , end(end)
   {}

   int beg, end;
};


bool operator < (const lecture &a, const lecture &b) {
   if (a.end == b.end) {
      return a.beg < b.beg;
   }
   return a.end< b.end;
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n, beg, end;
   cin >> n;
   vector<lecture> lectures;
   lectures.reserve(n);
   for (int i = 0 ; i < n; ++i) {
      cin >> beg >> end;
      lectures.push_back(lecture(beg, end));
   }

   sort(lectures.begin(), lectures.end());

   int cnt = 1;
   int last = lectures[0].end;
   for (size_t i = 1; i < lectures.size(); ++i) {
      lecture &cur = lectures[i];
      if (last <= cur.beg) {
         cnt++;
         last = cur.end;
      }
   }

   cout << cnt;


   return 0;
}