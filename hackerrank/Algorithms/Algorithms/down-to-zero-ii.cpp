#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const double eps = 1e-12;
const int MAX_SIZE = 1e6 + 5;
vector<int> prv(MAX_SIZE, 1);
vector<int> dp(MAX_SIZE, MAX_SIZE);

struct fact {
   int num;
   int cnt;
   fact(int num, int cnt): num(num), cnt(cnt)
   {}
};

void add(vector<fact> & facts, int num) {
   for (int i = 0; i < facts.size(); ++i) {
      if (facts[i].num == num) {
         facts[i].cnt++;
         return;
      }
   }
   facts.push_back(fact(num, 1));
}

void getFacts(int n, vector<fact> & facts) {
   int cur = n;
   while (prv[cur] != 1) {
      add(facts, prv[cur]);
      cur = cur / prv[cur];
   }
   add(facts, cur);
}

void rec(int n, vector<fact> & facts, int cur, int pos) {
   if (pos == facts.size()) {
      return;
   }
   if (cur != 1 && cur != n) {
      dp[n] = min(dp[n], dp[max(cur, n / cur)] + 1);
   }
   if (facts[pos].cnt) {
      cur *= facts[pos].num;
      facts[pos].cnt--;
      rec(n, facts, cur, pos);
      facts[pos].cnt++;
      cur /= facts[pos].num;
   }
   rec(n, facts, cur, pos + 1);
}

void sieve() {
   for (int num = 2; num < MAX_SIZE; ++num) {
      if (prv[num] == 1) {
         for (ll mul = 2; num * mul < MAX_SIZE; ++mul) {
            int & cur = prv[num * mul];
            if (cur == 1) {
               cur = num;
            }
         }
      }
   }
}

void precalc() {
   sieve();

   dp[0] = 0;
   vector<fact> facts;
   facts.reserve(10);
   for (int i = 1; i < MAX_SIZE; ++i) {
      getFacts(i, facts);
      rec(i, facts, 1, 0);
      dp[i] = min(dp[i], dp[i - 1] + 1);
      facts.clear();
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   std::ios::sync_with_stdio(false);

   precalc();

   int tests, n;
   cin >> tests;
   while (tests--) {
      cin >> n;
      cout << dp[n] << '\n';
   }

   return 0;
}