#include <iostream>
#include <vector>
#include <array>
#include <assert.h>

using namespace std;

typedef vector<int>     vi;
typedef vector<vi>      vvi;

const int V = 8;
vi E;

int pack(int i, int j) {
   return i * V  + j;
}
void unpack(int p, int& i, int& j) {
   i = p / V;
   j = p % V;
}

bool isClick4(vvi& adj, const array<int, 4>& a, vi* e_stat) {
   for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
         if (i != j) {
            if (!adj[a[i]][a[j]]) {
               return false;
            }
         }
      }
   }
   if (e_stat) {
      for (int i = 0; i < 4; ++i) {
         for (int j = 0; j < 4; ++j) {
            if (i != j) {
               (*e_stat)[pack(a[i], a[j])]++;
            }
         }
      }
   }
   return true;
}

int cntClick4(vvi& adj, vi* e_stat) {
   int cnt = 0;
   for (int i = 0; i < V; ++i) {
      for (int j = i + 1; j < V; ++j) {
         for (int k = j + 1; k < V; ++k) {
            for (int p = k + 1; p < V; ++p) {
               if (isClick4(adj, {i, j, k, p}, e_stat)) {
                  cnt++;
               }
            }
         }
      }
   }
   return cnt;
}

void test_pack(int i, int j) {
   int pi, pj;
   unpack(pack(i, j), pi, pj);
   assert(i == pi);
   assert(j == pj);
}
void test() {
   test_pack(0, 7);
   test_pack(7, 0);
   test_pack(4, 3);
   test_pack(2, 5);
}

void output_e_stat(const vi& e_stat) {
   for (int i = 0; i < V; ++i) {
      for (int j = i + 1; j < V; ++j) {
         cout << i << ", " << j << " = " << e_stat[pack(i,j)] << endl;
      }
   }
}

int calc_steps(vi& perm) {
   vvi adj(V, vi(V, 1));
   vi e_stat(V * V, 0);

   for (int i = 0; i < perm.size(); ++i) {
      if (perm[i]) {
         int u, v;
         unpack(E[i], u, v);
         adj[u][v] = adj[v][u] = 0;
      }
   }

   return cntClick4(adj, &e_stat);
}


void output_bat(const vi &perm) {
   static int answers = 0;
   answers++;
   cout << answers << " | ";
   for (int i = 0; i < perm.size(); ++i) {
      if (perm[i]) {
         int u, v;
         unpack(E[i], u, v);
         cout << u <<'-' << v << ", ";
      }
   }
}
int main() {
   test();

   for (int i = 0; i < V; ++i) {
      for (int j = i + 1; j < V; ++j) {
         E.push_back(pack(i,j));
      }
   }


   vi perm(E.size(), 0);
   for (int i = 0; i < 7; ++i) {
      perm[i] = 1;
   }
   reverse(perm.begin(), perm.end());

   int cnt = 0;
   do {
      ++cnt;
      int click_cnt = calc_steps(perm);
      if (click_cnt == 0) {
         output_bat(perm);
         cout << endl;
      }
   } while (next_permutation(perm.begin(), perm.end()));

   cout << endl;
   cout << cnt;
   cout << endl;
   return 0;
}