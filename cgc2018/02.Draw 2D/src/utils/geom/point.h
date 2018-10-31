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

public:
   GLint x, y;
};


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

