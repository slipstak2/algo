#include "common.h"

void drawDot(GLint x, GLint y) {
   glBegin(GL_POINTS);
      glVertex2i(x, y);
   glEnd();
}
