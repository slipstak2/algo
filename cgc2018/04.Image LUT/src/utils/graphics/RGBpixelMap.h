#pragma once

#include <GL/glut.h>
#include <string>

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
   RGB negative() {
      return {ubyte(255 - r), ubyte(255 - g), ubyte(255 - b)};
   }
};

extern RGB BLACK;
extern RGB WHITE;

bool operator == (const RGB& a, const RGB& b);
bool operator != (const RGB& a, const RGB& b);


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

   RGBpixelMap toNegative();

   friend void swap(RGBpixelMap& first, RGBpixelMap& second);

private:
   RGB* pixels;
   int height;
   int width;
};

void swap(RGBpixelMap& a, RGBpixelMap& b);