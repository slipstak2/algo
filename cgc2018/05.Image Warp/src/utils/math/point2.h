
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

typedef Point2<int> Point2DI;
typedef Point2<double> Point2DD;


Point2DD Rotate(const Point2DI& p, double alpha);