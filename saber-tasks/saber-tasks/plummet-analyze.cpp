#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;
typedef  vector<int> vi;
typedef  vector<vi> vvi;
typedef pair<vi, vi> pvi;
typedef vector<pvi> vpvi;
typedef vector<set<int>> vsi;
typedef long long ll;

typedef map<ll, pair<ll, ll>> mllpii;


const ll CALC_ITEMS = 1e9;

int main() {
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);


   vi w1, w2;
   ll cur = 1;
   while (cur <= CALC_ITEMS) {
      w1.push_back(cur);
      w2.push_back(cur * 2);
      cur *= 3;
   }

   mllpii res;

   int s1 = 0, s2 = 0;
   for (int i = 0; i < w1.size(); ++i) {
      s1 += w1[i]; res[s1].first  = i + 1;
      s2 += w2[i]; res[s2 + 1].second = i + 1;
   }

   for (mllpii::iterator it = res.begin(); it != res.end(); ++it) {
      if ((*it).second.first == 0 && next(it) != res.end()) {
         (*it).second.first = (*next(it)).second.first;
      }
   
      if ((*it).second.second == 0 && next(it) != res.end()) {
         (*it).second.second = (*next(it)).second.second;
      }
      printf("%10lld: %lld - %lld\n", (*it).first, (*it).second.first, (*it).second.second);
   }




   return 0;
}