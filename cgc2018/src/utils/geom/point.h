#pragma once

#include <GL/glut.h>

class GLintPoint {
public:
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

public:
   GLfloat x, y;
};

