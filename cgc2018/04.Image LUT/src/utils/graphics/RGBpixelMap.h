#pragma once

#include <GL/glut.h>
#include <string>

#include "RGBLutFilter.h"

typedef unsigned char ubyte;

class RGBpixelMap {
public:
   RGBpixelMap();
   RGBpixelMap(int height, int width);
   RGBpixelMap(const RGBpixelMap& other);
   RGBpixelMap& operator = (RGBpixelMap other);
   ~RGBpixelMap();
   bool setPixel(int x, int y, RGB color);
   RGB  getPixel(int x, int y);
   bool readBmpFile(const char* fname);
   void draw(int dx, int sreenHeight, const std::string& label);

   int Width();
   int Height();

   bool correctX(int x);
   bool correctY(int y);

   void toGray();
   RGBpixelMap toOrderedDither();
   RGBpixelMap toErrorDiffusion();

   RGBpixelMap applyFilter(RGBLutFilterBase* filter);

   friend void swap(RGBpixelMap& first, RGBpixelMap& second);

private:
   RGB* pixels;
   int height;
   int width;
};

void swap(RGBpixelMap& a, RGBpixelMap& b);