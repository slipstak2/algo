#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <map>
#include <chrono>
#include <vector>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>
#include <unordered_map>



using namespace std;

const int MAX_V = 3000 + 2;

typedef vector<int> vi;
typedef vector<vi> vvi;

typedef size_t vertex_type;
typedef vector<vertex_type> vt;


int n, r;
vvi adj;
bool is_subtree[MAX_V];
int dist[MAX_V];
int pred[MAX_V];
int max_path[MAX_V];

class TimeWrap {
public:
   using Clock = std::chrono::high_resolution_clock;
   using TimePoint = Clock::time_point;
   using fseconds = std::chrono::duration<float, std::chrono::seconds::period>;

   TimeWrap() : t(Clock::now()) {}

   float get_elapsed_seconds()
   {
      TimePoint tNow = Clock::now();
      fseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(tNow - t);
      t = tNow;
      return elapsed.count();
   }
   TimePoint t;
};

const int TYPE_NONE = -1;
struct TrieNode {
   int type;
   unordered_map<vertex_type, TrieNode*> childs;
   TrieNode(): type(TYPE_NONE){}
   TrieNode* go(vertex_type t) {
      TrieNode* next;
      auto it = childs.find(t);
      if (it == childs.end()) {
         next = new TrieNode();
         childs[t] = next;
      } else {
         next = it->second;
      }
      return next;
   }
};
void color_subtree(int v, int deep) {
   is_subtree[v] = true;
   for (int u: adj[v]) {
      if (!is_subtree[u]) {
         if (deep != 0) {
            color_subtree(u, deep - 1);
         }
      }
   }
}

void dfs_dist(int v, int prv = -1) {
   for (int u: adj[v]) {
      if (u != prv && is_subtree[u]) {
         pred[u] = v;
         dist[u] = dist[v] + 1;
         dfs_dist(u, v);
      }
   }
}

int most_distant_vertex(int v) {
   memset(dist, 0, sizeof(dist));
   memset(pred, 0, sizeof(pred));
   dfs_dist(v);
   return (int)(max_element(dist + 1, dist + n + 1) - dist);
}

void find_root(int v, vi& subtree_root) {
   int u = most_distant_vertex(v);
   int w = most_distant_vertex(u);
   // (u-w) - longest path in subtree

   int plen = 0;
   int cur = w;
   max_path[plen++] = cur;
   while (cur != u) {
      cur = pred[cur];
      max_path[plen++] = cur;
   }
   subtree_root.push_back(max_path[plen / 2]);
   if (plen % 2 == 0) {
      subtree_root.push_back(max_path[plen / 2 - 1]);
   }
}

TrieNode* root = new TrieNode();
int types_cnt = 1;
vertex_type get_type(const vt& children) {
   TrieNode* node = root;
   for (vertex_type t : children) {
      node = node->go(t);
   }
   if (node->type == TYPE_NONE) {
      node->type = types_cnt++;
   }
   return node->type;
}


size_t get_type_old(const vt& children) {
   static map<vt, vertex_type> subtree_types;
   auto it = subtree_types.find(children);
   size_t children_type = -1;
   if (it == subtree_types.end()) {
      children_type = subtree_types.size() + 1;
      subtree_types[children] = children_type;
   }
   else {
      children_type = it->second;
   }
   return children_type;
}

vertex_type dfs_type(int v, int prv = -1) {
   vt children;
   for (int u: adj[v]) {
      if (u != prv && is_subtree[u]) {
         children.push_back(dfs_type(u, v));
      }
   }
   sort(children.begin(), children.end());
   return get_type(children);
}


int main() {
   TimeWrap tw;

#if _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   scanf("%d %d", &n, &r);
   adj.resize(n + 1);
   int u, v;
   for (int i = 0; i < n - 1; ++i) {
      scanf("%d %d", &u, &v);
      adj[u].push_back(v);
      adj[v].push_back(u);
   }

   set<vertex_type> root_subtrees;
   set<pair<vertex_type, vertex_type>> edge_root_subtrees;
   for (int v = 1; v <= n; ++v) {
      memset(is_subtree, 0, sizeof(is_subtree));
      color_subtree(v, r);

      vi subtree_root;
      find_root(v, subtree_root);

      if (subtree_root.size() == 1) {
         root_subtrees.insert(dfs_type(subtree_root[0]));
      }
      else {
         vertex_type root1 = dfs_type(subtree_root[0], subtree_root[1]);
         vertex_type root2 = dfs_type(subtree_root[1], subtree_root[0]);
         if (root1 > root2) swap(root1, root2);
         edge_root_subtrees.insert(make_pair(root1, root2));
      }
   }

   printf("%d", (int)root_subtrees.size() + (int)edge_root_subtrees.size());

   clog << "time = " << tw.get_elapsed_seconds() << " s." << endl;
   return 0;
}
