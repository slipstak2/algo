#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
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

vi s;
vi dp;
vvi prvPos;
vi  prvLetter;


const int A = 0;
const int C = 1;
const int G = 2;
const int T = 3;

const char LET[5] = "ACGT";
int lastPos[4];


int get(const vi& a, int pos) {
   if (pos < 0) {
      return -1;
   }
   return a[pos];
}

void go(int pos) {
   string answer;

   while (pos != -1) {
      answer += LET[s[pos]];
      pos = prvPos[pos][prvLetter[pos]];
   }
   reverse(answer.begin(), answer.end());
   cout << answer;
}


int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   
   string str;
   cin >> str;
   s.resize(str.size());
   for (size_t i = 0; i < str.size(); ++i) {
      switch(str[i]) {
      case 'A': s[i] = A; break;
      case 'C': s[i] = C; break;
      case 'G': s[i] = G; break;
      case 'T': s[i] = T; break;
      }
   }

   s.insert(s.begin(), {A, C, G, T});
   dp.resize(s.size());
   prvPos.resize(s.size(), vi(4));
   prvLetter.resize(s.size());


   prvPos[0] = {-1, -1, -1, -1};

   for (size_t i = 0; i < s.size(); ++i) {
      if (i != 0) {
         prvPos[i] = prvPos[i - 1];
         prvPos[i][s[i-1]] = i - 1;
      }

      lastPos[s[i]] = i;
      dp[i] = get(dp, prvPos[i][A]);
      prvLetter[i] = A;

      if (dp[i] > get(dp, prvPos[i][C])) {
         dp[i] = get(dp, prvPos[i][C]);
         prvLetter[i] = C;
      } else if (dp[i] > get(dp, prvPos[i][G])) {
         dp[i] = get(dp, prvPos[i][G]);
         prvLetter[i] = G;
      } else if (dp[i] > get(dp, prvPos[i][T])) {
         dp[i] = get(dp, prvPos[i][T]);
         prvLetter[i] = T;
      }
      dp[i]++;
   }

   auto cmpLen = [](const string &a, const string &b) {
      return a.size() < b.size();
   };

   int resLen = min(
      min(dp[lastPos[A]], dp[lastPos[C]]), 
      min(dp[lastPos[G]], dp[lastPos[T]])
   );

   if (resLen == dp[lastPos[A]]) {
      go(lastPos[A]);
   } else if (resLen == dp[lastPos[C]]) {
      go(lastPos[C]);
   } else if (resLen == dp[lastPos[G]]) {
      go(lastPos[G]);
   } else if (resLen == dp[lastPos[T]]) {
      go(lastPos[T]);
   }
   return 0;
}