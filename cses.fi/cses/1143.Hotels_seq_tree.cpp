#define _CRT_SECURE_NO_WARNINGS

#include <set>
#include <vector>
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

struct HotelInfo {
   int num;
   int capacity;
   HotelInfo() 
      : num(0)
      , capacity(0)
   {}
   HotelInfo(int num, int capacity)
      : num(num)
      , capacity(capacity)
   {}
};

bool operator < (const HotelInfo& x, const HotelInfo& y) {
   return x.capacity < y.capacity;
}

const int MAX_SIZE = (int)2e5 + 10;
HotelInfo t[4 * MAX_SIZE];

int hotel[MAX_SIZE];

void build(int v, int tl, int tr) {
   if (tl == tr) {
      t[v] = HotelInfo(tl, hotel[tl]);
   } else {
      int tm = (tl + tr) >> 1;
      build(2 * v,     tl,     tm);
      build(2 * v + 1, tm + 1, tr);
      t[v] = max(t[2 * v], t[2 * v + 1]);
   }
}

HotelInfo get_hotel(int group, int v, int tl, int tr) {
   if (tl == tr) {
      return t[v];
   }
   int tm = (tl + tr) >> 1;
   if (t[2 * v].capacity >= group) {
      return get_hotel(group, 2 * v, tl, tm);
   }
   if (t[2 * v + 1].capacity >= group) {
      return get_hotel(group, 2 * v + 1, tm + 1, tr);
   }
   return HotelInfo();
}

void update_hotel(int v, int tl, int tr, int num, int capacity) {
   if (tl == tr) {
      t[v] = HotelInfo(num, capacity);
#if _DEBUG
      hotel[num] = capacity;
#endif
   } else {
      int tm = (tl + tr) >> 1;
      if (num <= tm) {
         update_hotel(2 * v, tl, tm, num, capacity);
      } else {
         update_hotel(2 * v + 1, tm + 1, tr, num, capacity);
      }
      t[v] = max(t[2 * v], t[2 * v + 1]);
   }
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif
   ios::sync_with_stdio(0);

   int hotels, groups, group;
   cin >> hotels >> groups;
   for (int i = 1; i <= hotels; ++i) {
      cin >> hotel[i];
   }
   build(1, 1, hotels);
   for (int i = 0; i < groups; ++i) {
      cin >> group;
      auto hotel_info = get_hotel(group, 1, 1, hotels);
      cout << hotel_info.num << ' ';
      if (hotel_info.num) {
         update_hotel(1, 1, hotels, hotel_info.num, hotel_info.capacity - group);
      }
   }

   return 0;
}