#pragma once

#include <GL/glut.h>

typedef unsigned char ubyte;

struct RGB {
   ubyte r;
   ubyte g;
   ubyte b;
   ubyte gray() {
      return 0.299 * r + 0.587 * g + 0.114 * b;
   }
   bool isGray() {
      return r == g && g == b;
   }
};

extern RGB BLACK;
extern RGB WHITE;

bool operator == (const RGB& a, const RGB& b);
bool operator != (const RGB& a, const RGB& b);