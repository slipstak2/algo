#pragma once

#include <GL/glut.h>

class GLintPoint {
public:
   GLintPoint()
      : x(0)
      , y(0) 
   {}
   GLintPoint(GLint x, GLint y) 
      : x(x)
      , y(y)
   {}
   double dist(GLint x2, GLint y2);

public:
   GLint x, y;
};

GLintPoint toVector(int begX, int begY, int endX, int endY);

GLintPoint toVector(int begX, int begY, const GLintPoint& pEnd);

long long mulVect(const GLintPoint& v1, const GLintPoint& v2);

class GLfloatPoint {
public:
   GLfloatPoint(GLfloat x, GLfloat y) 
      : x(x)
      , y(y)
   {}
   operator GLintPoint() const { return GLintPoint((GLint)x, (GLint)y);}

public:
   GLfloat x, y;
};

