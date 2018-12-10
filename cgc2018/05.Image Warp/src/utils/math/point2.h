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


Point2D Rotate(const Point2I& p, double alpha);
Point2D ReverseRotate(const Point2I& p, double alpha);
