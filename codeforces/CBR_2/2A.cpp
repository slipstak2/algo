#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define fori(it, x) for (auto it = (x).begin(); it != (x).end(); it++)


const int MAXN = 1000 + 5;

string name [MAXN];
int    score[MAXN];

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   int n;
   cin >> n;

   map<string, int> res;
   forn(i ,n) {
      cin >> name[i] >> score[i];
      res[name[i]] += score[i];
   }

   int max_score = res.begin()->second;
   fori (it, res) {
      max_score = max(max_score, it->second);
   }

   set<string> winners;
   fori(it, res) {
      if (it->second == max_score) {
         winners.insert(it->first);
      }
   }
   
   if (winners.size() == 1) {
      cout << *winners.begin();
      return 0;
   }

   res.clear();
   forn(i, n) {
      int& cur_score = res[name[i]];
      cur_score += score[i];
      if (cur_score >= max_score) {
         if (find(all(winners), name[i]) != winners.end()) {
            cout << name[i];
            return 0;
         }
      }
   }

   return 0;
}
