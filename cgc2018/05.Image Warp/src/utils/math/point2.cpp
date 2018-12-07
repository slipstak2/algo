#include <cmath>
#include "point2.h"

void tranform(double v[3], double M[3][3], double vR[3]) {
   const int K = 3;
   const int J = 3;
   for (int k = 0; k < 3; ++k) {
      for (int j = 0; j < 3; ++j) {
         vR[j] += v[k] * M[k][j];
      }
   }
}
Point2DD Rotate(const Point2DI& p, double alpha) {

   double v[3] = { (double)p.x, (double)p.y, 1 };
   double M[3][3] = {
      { cos(alpha), sin(alpha), 0},
      {-sin(alpha), cos(alpha), 0},
      {          0,          0, 1}
   };

   double vR[3] = { 0, 0, 0 };

   tranform(v, M, vR);
   return Point2DD(vR[0], vR[1]);
}

Point2DD ReverseRotate(const Point2DI& p, double alpha) {
   double v[3] = { (double)p.x, (double)p.y, 1 };
   double a =  cos(alpha);
   double b = -sin(alpha);
   double c =  sin(alpha);
   double d =  cos(alpha);
   double l = 0;
   double m = 0;


   double MRT[3][3] = {
      {         d,       -c,          0 },
      {        -b,        a,          0 },
      { b*m - l*d, l*c - a*m, a*d - b*c }
   };

   double mul = 1 / (a * d - b * c);
   for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
         MRT[i][j] *= mul;
      }
   }

   double vR[3] = { 0, 0, 0 };
   tranform(v, MRT, vR);
   return Point2DD(vR[0], vR[1]);
}