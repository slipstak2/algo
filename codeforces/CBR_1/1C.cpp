#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>

using namespace std;

typedef double ld;

const ld PI = 3.1415926535897932384626433832795;
const ld EPS = 1e-4;

struct point {
   ld x,y;
   point(){}
   point(ld x, ld y) : x(x), y(y)
   {}
};

istream & operator >> (istream& is, point& p) {
   is >> p.x >> p.y;
   return is;
}

inline ld sqr(ld a) {return a * a;}

ld dist(point &p1, point &p2) {
   return sqrt(sqr(p1.x - p2.x) + sqr(p1.y - p2.y));
}
point operator - (const point &a, const point &b) {
   return point(a.x - b.x, a.y - b.y);
}
ld vp(point p, point p1, point p2) {
   p1 = p1 - p;
   p2 = p2 - p;
   return p1.x*p2.y - p1.y*p2.x;
}
ld sp(point p, point p1, point p2) {
   p1 = p1 - p;
   p2 = p2 - p;
   return p1.x*p2.x + p1.y*p2.y;
}

ld alpha(const point& a, const point& b, const point& c) {
   return fabs(atan2(vp(a, b, c), sp(a, b, c)));
}

ld S(point p1, point p2, point p3) {
   return fabs(vp(p1, p2, p3) / 2.0);
}

ld findR(point p1, point p2, point p3) {
   ld a = dist(p1, p2);
   ld b = dist(p2, p3);
   ld c = dist(p3, p1);
   return a*b*c / (4.0 * S(p1, p2, p3));
}

bool isInt(double val) {
   return fabs(val - (int)(val + EPS)) <= EPS;
}

int main() {
#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   point a[3];
   for (int i = 0; i < 3; ++i) {
      cin >> a[i];
   }

   ld A = alpha(a[0], a[1], a[2]) * 2;
   ld B = alpha(a[1], a[2], a[0]) * 2;
   ld C = alpha(a[2], a[0], a[1]) * 2;

   for (int n = 3; n <= 100; ++n) {
      ld nA = A * n / (2 * PI);
      ld nB = B * n / (2 * PI);
      ld nC = C * n / (2 * PI);
      if (isInt(nA) && isInt(nB) && isInt(nC)) {
         ld phi = 2 * PI / n;
         ld R = findR(a[0], a[1], a[2]);
         printf("%0.8lf", 0.5 * sqr(R) * sin(phi) * n);
         break;
      }
   }
   return 0;
}