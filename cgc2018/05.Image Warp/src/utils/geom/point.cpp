#include "geom/point.h"
#include "cmath"


double GLintPoint::dist(GLint x2, GLint y2) {
   return sqrt(double(x2 - x)*(x2 - x) + double(y2 - y)*(y2 - y));
}

GLintPoint toVector(int begX, int begY, int endX, int endY) {
   return GLintPoint(endX - begX, endY - begY);
}

GLintPoint toVector(int begX, int begY, const GLintPoint& pEnd) {
   return GLintPoint(pEnd.x - begX, pEnd.y - begY);
}

long long mulVect(const GLintPoint& v1, const GLintPoint& v2)
{
   return (long long)v1.x * v2.y - (long long)v1.y * v2.x;
}