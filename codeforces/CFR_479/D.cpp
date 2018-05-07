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

typedef unsigned long long VER_TYPE;
int V;

vector<VER_TYPE> v;
vector<vector<int>> adj;

bool isEdge(int indA, int indB) {
   VER_TYPE a = v[indA];
   VER_TYPE b = v[indB];

   if (a % 3 == 0 && a / 3 == b) {
      return true;
   }
   if (a * 2 == b) {
      return true;
   }
   return false;
}


void go(int cur) {
   cout << v[cur] << ' ';
   VER_TYPE value = v[cur];
   for (int nxt = 0; nxt < V; ++nxt) {
      if (adj[cur][nxt]) {
         go(nxt);
      }
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   iostream::sync_with_stdio(false);

   cin >> V;
   v.resize(V);
   for (int i = 0; i < V; ++i) {
      cin >> v[i];
   }

   adj = vector<vector<int>> (V, vector<int>(V, 0));
   for (int i = 0; i < V; ++i) {
      for (int j = i + 1; j < V; ++j) {
         if (isEdge(i, j)) {
            adj[i][j] = 1;
         } else if (isEdge(j, i)) {
            adj[j][i] = 1;
         }
      }
   }

   int istok = -1;
   for (int j = 0; j < V; ++j) {
      bool isIstok = true;
      for (int i = 0; i < V; ++i) {   
         if (adj[i][j]) {
            isIstok = false;
            break;
         }
      }
      if (isIstok) {
         istok = j;
         break;
      }
   }

   go(istok);



   return 0;
}