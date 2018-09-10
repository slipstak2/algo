#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll>  vll;
typedef pair<int, int> pi;

#define F first
#define S second
#define PB push_back
#define MP make_pair

#define REP(i, a, b) for (int i = a; i <= b; ++i)

int input_time() {
   int h, m;
   scanf("%d:%d", &h, &m);
   return h * 60 + m;
}

enum EVENT_TYPE {
   OPEN =  -1,
   CLOSE = 1,
};

struct event {
   event(int type, int time) 
      : type(type)
      , time(time)
   {}

   int type;
   int time;
};

bool operator < (const event &a, const event &b) {
   if (a.time == b.time) {
      return a.type < b.type;
   } 
   return a.time < b.time;
}


int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   int n;
   cin >> n;
   vector<event> events;
   events.reserve(2 * n);
   for (int i = 0; i < n; ++i) {
      events.push_back(event(EVENT_TYPE::OPEN,  input_time()));
      events.push_back(event(EVENT_TYPE::CLOSE, input_time()));
   }
   sort(events.begin(), events.end());

   int result = 0, cnt = 0;
   for (const event& e:events) {
      if (e.type == EVENT_TYPE::OPEN) {
         cnt++;
         result = max(result, cnt);
      } else {
         cnt--;
      }
   }

   cout << result;
   return 0;
}