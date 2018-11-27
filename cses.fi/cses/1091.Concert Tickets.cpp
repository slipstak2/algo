#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <iostream>
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

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);
   int n, m, t;
   cin >> n >> m;
   multiset<int> ticket;
   for (int i = 0; i < n; ++i) {
      cin >> t;
      ticket.insert(t);
   }

   int x;
   for (int j = 0; j < m; ++j) {
      cin >> x;
      int result = -1;
      if (!ticket.empty()) {
         auto it = ticket.lower_bound(x);
         if (it == ticket.end()) {
            result = *(--it);
            ticket.erase(it);
         } else { 
            if (x < *it) {
               if (it != ticket.begin()) {
                  --it;
               }
            }
            if (*it <= x) {
               result = *it;
               ticket.erase(it);
            }
         }
      }

      cout << result << endl;
      
      
   }

   return 0;
}