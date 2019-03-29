#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <vector>
using namespace std;

enum VERTEX_TYPE{WHITE,GRAY,BLACK};
int n;
vector<vector<int> > adj;
vector<VERTEX_TYPE> used;
void input() {
   cin>>n;
   adj.resize(n*n);
   used.resize(n*n,WHITE);
   char c;
   int row,col,f,s;
   int len = 2*(n*n-n);
   for (int i=0;i<len;i++) {
      cin>>c;
      row = i / (2*n - 1);
      col = i % (2*n - 1);
      f = row*n + col;
      if (c == '>' || c == '<') {
         s = f + 1;
         if (c == '>')
            adj[f].push_back(s);
         else
            adj[s].push_back(f);
      }
      else {
         f-= n - 1;
         s = f + n;
         if (c == 'v')
            adj[f].push_back(s);
         else
            adj[s].push_back(f);
      }
   }
}
bool dfs(int cur, vector<int> &ans) {
   used[cur] = GRAY;
   for (int i=0;i<adj[cur].size();i++) {
      int next = adj[cur][i];
      if (used[next] == GRAY)
         return false;
      if (used[next] == WHITE) {
         if (!dfs(next,ans))
            return false;
      }
   }
   used[cur] = BLACK;
   ans.push_back(cur);
   return true;
}
bool topological_sort(vector<int> &ans) {
   for (int i=0; i<n*n; i++) {
      if (used[i] == WHITE) {
         if (!dfs(i,ans))
            return false;
      }
   }
   return true;
}
void solve()
{
   vector<int> ans;
   vector<int> out;
   if (!topological_sort(ans)) {
      cout<<-1;
      return;
   } else {

      out.resize(ans.size());
      for (int i=0;i<ans.size();i++)
         out[ans[i]] = i+1;
   }
   int pos = 0;
   for (int i=0;i<n;i++){
      for (int j=0;j<n;j++)
         cout<<out[pos++]<<' ';
      cout<<endl;
   }
}
int main() {
#ifdef _DEBUG
   freopen("input.txt","r",stdin);
   freopen("output.txt","w",stdout);
#endif

   input();
   solve();
   return 0;
}