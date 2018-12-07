#pragma once

#include <GL/glut.h>

typedef unsigned char ubyte;

class RGB;

struct RGBD {
   double r;
   double g;
   double b;
   RGBD(double r, double g, double b);
   RGBD(const RGB& color);
   RGB toRGB();
   static RGBD linearInterpolation(const RGBD& color1, const RGBD& color2, const double p1, const double p, const double p2);
};

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

RGBD operator * (const RGBD& color, const double mul);
RGBD operator + (const RGBD& color1, const RGBD& color2);

extern RGB BLACK;
extern RGB WHITE;

bool operator == (const RGB& a, const RGB& b);
bool operator != (const RGB& a, const RGB& b);