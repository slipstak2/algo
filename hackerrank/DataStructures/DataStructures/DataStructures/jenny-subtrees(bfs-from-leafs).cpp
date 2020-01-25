#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <map>
#include <cmath>
#include <queue>
#include <chrono>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<int>     vi;
typedef vector<vi>     vvi;

class TimeWrap {
public:
   using Clock = std::chrono::high_resolution_clock;
   using TimePoint = Clock::time_point;
   using fseconds = std::chrono::duration<float, std::chrono::seconds::period>;

   TimeWrap(): t(Clock::now()) {}

   float get_elapsed_seconds()
   {
      TimePoint tNow = Clock::now();
      fseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(tNow - t);
      t = tNow;
      return elapsed.count();
   }
   TimePoint t;
};


const int MAX_V = 3000 + 5;

const int TYPE_NONE = 0;

int n;
vvi adj;


int used[MAX_V];
int dist[MAX_V];

void get_sub_tree(int v, int r, vvi& adj_sub_tree) {
   memset(used, 0, sizeof(used));
   memset(dist, 0, sizeof(dist));

   queue<int> q;
   q.push(v);
   used[v] = 1;
   
   while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (int nxt : adj[cur]) {
         if (!used[nxt] && dist[cur] + 1 <= r) {
            dist[nxt] = dist[cur] + 1;
            adj_sub_tree[cur].push_back(nxt);
            adj_sub_tree[nxt].push_back(cur);
            q.push(nxt);
            used[nxt] = 1;
         }
      }
   }
}

map<vi, int> sub_tree_type;

int get_type(vi& children) {
   sort(children.begin(), children.end());

   int t = -1;
   auto it = sub_tree_type.find(children);
   if (it == sub_tree_type.end()) {
      t = sub_tree_type.size() + 1;
      sub_tree_type[children] = t;
   }
   else {
      t = it->second;
   }
   return t;
}

int add_sub_tree(const vvi& adj_sub_tree) {
   queue<int> leafs;
   vi t(n + 1, TYPE_NONE);
   
   vvi children(n + 1);
   queue<int> next_leafs;

   int no_colored_vertex = 0;
   for (int v = 1; v <= n; ++v) {
      if (!adj_sub_tree[v].empty()) {
         no_colored_vertex++;
      }
      if (adj_sub_tree[v].size() == 1) {
         next_leafs.push(v);
      }
   }   

   while (!next_leafs.empty()) {
      leafs.swap(next_leafs);

      if (leafs.size() == 1) {
         int root = leafs.front();
         return get_type(children[root]);
      }

      if (leafs.size() == 2 && no_colored_vertex == 2) {
         int u = leafs.front(); leafs.pop();
         int v = leafs.front();
         // edge (u-v) is a tree root
         vi child({ -1, get_type(children[u]), get_type(children[v]) });
         return get_type(child);
      }

      while (!leafs.empty()) {
         int leaf = leafs.front(); leafs.pop();
         
         t[leaf] = get_type(children[leaf]);
         no_colored_vertex--;

         for (int pred : adj_sub_tree[leaf]) {
            if (t[pred] == TYPE_NONE) {
               children[pred].push_back(t[leaf]);
               if (adj_sub_tree[pred].size() - children[pred].size() == 1) {
                  next_leafs.push(pred);
               }
            }
         }
      }      
   }
   return -1;
}

int main() {
   TimeWrap tw;

//#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
//#endif

   int r, u, v;
   scanf("%d %d", &n, &r);
   adj.resize(n + 1);
   for (int i = 0; i < n; ++i) {
      scanf("%d %d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
   }

   sub_tree_type[vi()] = 1;
   set<int> types;

   for (int v = 1; v <= n; ++v) {
      vvi adj_sub_tree(n + 1);
      get_sub_tree(v, r, adj_sub_tree);
      types.insert(add_sub_tree(adj_sub_tree));
   }

   printf("%d", types.size());

   clog << "time = " << tw.get_elapsed_seconds() << " s." << endl;
   
   return 0;
}