#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

#define For(i, st, en) for(int i=(st); i<=(int)(en); i++)
#define forn(i, n) for(int i=0; i<(int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define fori(it, x) for (auto it = (x).begin(); it != (x).end(); it++)

int V, E;
vector<vector<int>> adj;
vector<bool> used;

void dfs(int cur, vector<int> &comp) {
   used[cur] = true;
   comp.push_back(cur);

   for (int i = 0; i < adj[cur].size(); ++i) {
      int nxt = adj[cur][i];
      if (!used[nxt]) {
         dfs(nxt, comp);
      }
   }
};

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   cin >> V >> E;
   adj.resize(V + 1);
   used.resize(V + 1);

   int u, v;
   for (int i = 0 ; i < E; ++i) {
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }

   int res = 0;
   for (int v = 1 ; v <= V; ++v) {
      if (!used[v]) {
         vector<int> comp;
         dfs(v, comp);
         bool isOK = true;
         for (int i = 0; i < comp.size(); ++i) {
            if (adj[comp[i]].size() != 2) {
               isOK = false;
               break;
            }
         }
         if (isOK) {
            res++;
         }
      }
   }
   cout << res;
   return 0;
}