#include "line.h"

void _drawSegmentBresenham(GLintPoint p1, GLintPoint p2, std::function<void(GLint, GLint)> draw) {
   int dx = p2.x - p1.x;
   int dy = p2.y - p1.y;

   int e = 2 * abs(dy) - abs(dx);
   int incrE  = 2 * abs(dy);
   int incrNE = 2 * abs(dy) - 2 * abs(dx);

   int x = p1.x, y = p1.y;
   int dirX = p2.x - p1.x > 0 ? 1 : -1;
   int dirY = p2.y - p1.y > 0 ? 1 : -1;
   draw(x, y);
   while (x != p2.x) {
      if (e > 0) {
         y += dirY;
         e += incrNE;
      }
      else {
         e += incrE;
      }
      x += dirX;
      draw(x, y);
   }
}

void drawSegmentBresenham(GLintPoint p1, GLintPoint p2, std::function<void(GLint, GLint)> drawDot) {
   int dx = p2.x - p1.x;
   int dy = p2.y - p1.y;
   if (abs(dy) <= abs(dx)) {
      _drawSegmentBresenham(p1, p2, [drawDot](GLint x, GLint y) {
         drawDot(x, y);
      });
   } else {
      _drawSegmentBresenham(GLintPoint(p1.y, p1.x), GLintPoint(p2.y, p2.x), [drawDot](GLint x, GLint y) {
         drawDot(y, x);
      });
   }
}