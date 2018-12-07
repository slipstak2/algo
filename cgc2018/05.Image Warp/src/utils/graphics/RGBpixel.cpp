#include "RGBpixel.h"

RGB BLACK = {0, 0, 0};
RGB WHITE = {255, 255, 255};


RGBD::RGBD(double r, double g, double b)
   : r(r)
   , g(g)
   , b(b)
{}

RGBD::RGBD(const RGB& color)
   : r(color.r)
   , g(color.g)
   , b(color.b)
{}

RGB RGBD::toRGB() {
   return {
      (ubyte)r,
      (ubyte)g,
      (ubyte)b
   };
}


bool operator == (const RGB& a, const RGB& b) {
   return memcmp(&a, &b, sizeof(RGB)) == 0;
}

bool operator != (const RGB& a, const RGB& b) {
   return !(a == b);
}

RGBD operator * (const RGBD& color, const double mul) {
   return {
      color.r * mul,
      color.g * mul,
      color.b * mul
   };
}

RGBD operator + (const RGBD& color1, const RGBD& color2) {
   return {
      color1.r + color2.r,
      color1.g + color2.g,
      color1.b + color2.b
   };
}

RGBD RGBD::linearInterpolation(const RGBD& color1, const RGBD& color2, const double p1, const double p, const double p2) {
   double mul1 = (p2 - p) / (p2 - p1);
   double mul2 = (p - p1) / (p2 - p1);
   return color1 * mul1 + color2 * mul2;
}