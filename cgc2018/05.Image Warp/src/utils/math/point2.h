#pragma once 

template<class T>
class Point2{
public:
   Point2()
      : x()
      , y()
   {}
   Point2(T x, T y) 
      : x(x)
      , y(y)
   {}

public:
   T x, y;
};

typedef Point2<int> Point2I;
typedef Point2<double> Point2D;


Point2D TransformPoint(const Point2I& p, double T[][3]);
Point2D Rotate(const Point2I& p, double alpha);
Point2D ReverseRotate(const Point2I& p, double alpha);
void getTransfromCoord(
   double x0,  double y0,  double x1,  double y1,  double x2,  double y2,
   double x0_, double y0_, double x1_, double y1_, double x2_, double y2_,
   double M[][3]
);