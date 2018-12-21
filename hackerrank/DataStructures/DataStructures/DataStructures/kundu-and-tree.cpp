#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
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

struct DisjointSet {
   DisjointSet(int n) {
      parent.resize(n);
      capacity.resize(n);
      for (int i = 0; i < n; ++i) {
         parent[i] = i;
         capacity[i] = 1;
      }
   }
   int find(int v) {
      if (parent[v] == v) {
         return v;
      }
      return parent[v] = find(parent[v]);
   }
   void join(int u, int v) {
      u = find(u);
      v = find(v);
      if (u != v) {
         if (capacity[u] < capacity[v]) {
            swap(u, v);
         }
         parent[v] = u;
         capacity[u] += capacity[v];
      }
   }
   int size(int u) {
      return capacity[u];
   }

private:
   vector<int> parent;
   vector<int> capacity;
};


const long long MOD = 1000000007;


int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);
   ll V;
   int u, v;
   char c;
   cin >> V;

   DisjointSet dsu(V + 1);

   for (int i = 0; i < V; ++i) {
      cin >> u >> v >> c;
      if (c != 'r') {
         dsu.join(u, v);
      }
   }

   ll U = (V * (V - 1) * (V - 2)) / 6;
   
   vector<int> used(V + 1);
   for (int v = 1; v <= V; ++v) {
      int p = dsu.find(v);
      if (!used[p]) {
         used[p] = true;
         ll N = dsu.size(p);
         U -= ((N * (N - 1)) / 2) * (V - N);
         U -= (N * (N - 1) * (N - 2)) / 6;
      }
   }

   cout << U % MOD;

   return 0;
}