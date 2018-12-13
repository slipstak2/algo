#include <cmath>
#include "point2.h"
#include "string.h"

void tranform(double v[3], double M[3][3], double vR[3]) {
   const int K = 3;
   const int J = 3;
   for (int k = 0; k < 3; ++k) {
      for (int j = 0; j < 3; ++j) {
         vR[j] += v[k] * M[k][j];
      }
   }
}

Point2D TransformPoint(const Point2I& p, double T[][3]) {
   double v[3] = { (double)p.x, (double)p.y, 1 };
   double vR[3] = { 0, 0, 0 };
   tranform(v, T, vR);
   return Point2D(vR[0], vR[1]);

}
Point2D Rotate(const Point2I& p, double alpha) {

   double v[3] = { (double)p.x, (double)p.y, 1 };
   double M[3][3] = {
      { cos(alpha), sin(alpha), 0},
      {-sin(alpha), cos(alpha), 0},
      {          0,          0, 1}
   };

   double vR[3] = { 0, 0, 0 };

   tranform(v, M, vR);
   return Point2D(vR[0], vR[1]);
}

Point2D ReverseRotate(const Point2I& p, double alpha) {
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
   return Point2D(vR[0], vR[1]);
}

void getTransfromCoord(
   double x0,  double y0,  double x1,  double y1,  double x2,  double y2,
   double x0_, double y0_, double x1_, double y1_, double x2_, double y2_,
   double M[][3]
   ) {

   memset(M, 0, sizeof(double) * 9);

   double detG_ = x0_ * (y1_ - y2_) - y0_ * (x1_ - x2_) + (x1_ * y2_ - x2_ * y1_);

   double A[3][3] = {
      {            y1_ - y2_,             y2_ - y0_,             y0_ - y1_},
      {            x2_ - x1_,             x0_ - x2_,             x1_ - x0_},
      {x1_ * y2_ - x2_ * y1_, x2_ * y0_ - x0_ * y2_,             x0_ * y1_ - x1_ * y0_ /*x2_ * y1_ - x1_ * y2_*/}
   };

   double B[3][3] = {
      {x0, y0, 1},
      {x1, y1, 1},
      {x2, y2, 1}
   };

   for (int i = 0; i < 3; ++i) {
      for (int k = 0; k < 3; ++k) {
         for (int j = 0; j < 3; ++j) {
            M[i][j] += A[i][k] * B[k][j];
         }
      }
   }

   for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
         M[i][j] /= detG_;
      }
   }
}
