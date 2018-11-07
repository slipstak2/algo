#include "common.h"

void drawDot(GLint x, GLint y) {
   glBegin(GL_POINTS);
      glVertex2i(x, y);
   glEnd();
}

int clamp(int value, int minValue, int maxValue) {
   if (value < minValue) value = minValue;
   if (value > maxValue) value = maxValue;
   return value;
}