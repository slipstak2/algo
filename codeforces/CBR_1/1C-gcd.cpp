#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

typedef double ld;
const ld PI = 3.1415926535897932384626433832795;
ld eps = 2 * PI / 105; // max 100 vertexes

inline ld sqr(ld a) { return a * a; }

struct point {
   ld x, y;
   point() {}
   point(ld X, ld Y) : x(X), y(Y) {}
   void input() {
      cin >> x >> y;
   }
};
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
ld S(point p1, point p2, point p3) {
   return fabs(vp(p1, p2, p3) / 2.0);
}
ld gcd(ld a, ld b) {
   if (b < eps)
      return a;
   return gcd(b, fmod(a, b));
}
ld findR(point p1, point p2, point p3) {
   ld a = dist(p1, p2);
   ld b = dist(p2, p3);
   ld c = dist(p3, p1);
   return a*b*c / (4.0 * S(p1, p2, p3));
}
int main() {

#ifdef _DEBUG
   freopen("input.txt", "r", stdin);
   freopen("output.txt", "w", stdout);
#endif

   point a, b, c;
   a.input();
   b.input();
   c.input();

   ld A = fabs(atan2(vp(a, b, c), sp(a, b, c))) * 2.0;
   ld B = fabs(atan2(vp(b, a, c), sp(b, a, c))) * 2.0;
   ld C = fabs(atan2(vp(c, a, b), sp(c, a, b))) * 2.0;

   ld phi = gcd(gcd(A, B), C);
   double n = 2 * PI / phi;
   ld R = findR(a, b, c);

   printf("%0.8lf", 0.5 * sqr(R) * sin(phi) * n);

   return 0;
}