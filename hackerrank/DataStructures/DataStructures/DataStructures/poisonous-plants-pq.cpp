#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int>     vi;
typedef vector<vi>     vvi;
typedef vector<ll>     vll;
typedef set<int>        si;
typedef multiset<int>  msi;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)

int n;
vi a;
vi nxt;
vi used;

class cmp
{
public:
   bool operator() (int i, int j)
   {
      return a[i] > a[j];
   }
};
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);
   cin >> n;
   a.resize(n);
   nxt.resize(n);

   used.resize(n);

   priority_queue<int, vector<int>, cmp> pq, pqNext;
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
      nxt[i] = i != n - 1 ? i + 1 : -1;
      pq.push(i);
   }

   int days = 0;
   while (!pq.empty()) {
      days++;
      while (!pq.empty()) {
         int cur = pq.top();
         pq.pop();
         if (used[cur]) continue;
         int pos = cur, cnt = 0;;
         while(nxt[pos] != -1) {
            if (a[pos] < a[nxt[pos]]) {
               used[nxt[pos]] = true;
               pos = nxt[pos];
               nxt[cur] = nxt[pos];
               
               cnt++;
            } else {
               break;
            }
         }

         if (cnt) {
            pqNext.push(cur);
         }
      }
      pq.swap(pqNext);
   }
   cout << days - 1;
   return 0;
}