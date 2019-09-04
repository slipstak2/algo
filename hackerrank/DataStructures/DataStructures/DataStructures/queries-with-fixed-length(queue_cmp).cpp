#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>


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


template<class T, class Predicate = less<T>>
class StackCmp {
   vector<T> data;
   vector<T> pred_data;
   Predicate cmp;

public:
   void push(const T& item) {
      data.push_back(item);
      if (pred_data.empty()) {
         pred_data.push_back(item);
      }
      else {
         pred_data.push_back(cmp(item, pred_data.back()) ? item : pred_data.back());
      }
   }

   void pop() {
      data.pop_back();
      pred_data.pop_back();
   }

   T top() {
      return data.back();
   }

   const T& pred_item() {
      return pred_data.back();
   }

   bool empty() {
      return data.empty();
   }
};

template<class T, class Predicate = greater<T>>
class QueueCmp {
   StackCmp<T, Predicate> push_stack;
   StackCmp<T, Predicate> pop_stack;
   Predicate cmp;

public:
   void push(const T& item) {
      push_stack.push(item);
   }

   void pop() {
      if (!pop_stack.empty()) {
         return pop_stack.pop();
      }
      else {
         fill_pop_stack();
         pop();
      }
   }

   void fill_pop_stack() {
      while (!push_stack.empty()) {
         pop_stack.push(push_stack.top());
         push_stack.pop();
      }
   }

   T pred_item() {
      if (!push_stack.empty() && !pop_stack.empty()) {
         const T& a = push_stack.pred_item();
         const T& b = pop_stack.pred_item();
         return cmp(a, b) ? a : b;
      } else if (push_stack.empty()) {
         return pop_stack.pred_item();
      }
      return push_stack.pred_item();
   }
};

int req(const vi& a, int d) {
   QueueCmp<int> q;
   for (int i = 0; i < d; ++i) {
      q.push(a[i]);
   }
   int ans = q.pred_item();
   for (int i = d; i < a.size(); ++i) {
      q.pop();
      q.push(a[i]);
      ans = min(ans, q.pred_item());
   }
   return ans;
}
int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int n, q, d;
   cin >> n >> q;
   vi a(n);
   for (int i = 0; i < n; ++i) {
      cin >> a[i];
   }
   while (q --> 0) {
      cin >> d;
      cout << req(a, d) << '\n';
   }

   return 0;
}