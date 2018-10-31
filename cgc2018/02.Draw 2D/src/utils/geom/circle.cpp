#include "circle.h"

void _drawDots4(GLintPoint center, GLint R, std::function<void(GLint, GLint)> drawDot) {
   drawDot(center.x, center.y - R);
   drawDot(center.x, center.y + R);
   drawDot(center.x - R, center.y);
   drawDot(center.x + R, center.y);
}

void _drawDots8(GLintPoint center, GLint x, GLint y, std::function<void(GLint, GLint)> drawDot) {
   drawDot(center.x + x, center.y + y);
   drawDot(center.x - x, center.y + y);
   drawDot(center.x - x, center.y - y);
   drawDot(center.x + x, center.y - y);
   drawDot(center.x + y, center.y + x);
   drawDot(center.x - y, center.y + x);
   drawDot(center.x - y, center.y - x);
   drawDot(center.x + y, center.y - x);
}

void drawCircleBresenham(GLintPoint center, GLint R, std::function<void(GLint, GLint)> drawDot) {
   int x = 0, y = R;
   int f = 1 - R;
   int incrE = 3;
   int incrSE = 5 - 2 * R;
   _drawDots4(center, R, drawDot);
   while (x <= y) {
      if (f > 0) {
         y--;
         f += incrSE;
         incrSE = incrSE + 4;
      } else {
         f += incrE;
         incrSE += 2;
      }
      incrE += 2;
      x++;
      _drawDots8(center, x, y, drawDot);
   }
}