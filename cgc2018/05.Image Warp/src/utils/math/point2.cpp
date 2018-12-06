#include <cmath>
#include "point2.h"

Point2DD Rotate(const Point2DI& p, double alpha) {

   double v[3] = { (double)p.x, (double)p.y, 1 };
   double M[3][3] = {
      { cos(alpha), sin(alpha), 0},
      {-sin(alpha), cos(alpha), 0},
      {          0,          0, 1}
   };

   double vR[3] = { 0, 0, 0 };

   const int K = 3;
   const int J = 3;
   for (int k = 0; k < 3; ++k) {
      for (int j = 0; j < 3; ++j) {
         vR[j] += v[k] * M[k][j];
      }
   }
   return Point2DD(vR[0], vR[1]);
}
