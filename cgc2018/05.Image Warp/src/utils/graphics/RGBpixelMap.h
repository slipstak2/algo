#pragma once

#include <GL/glut.h>
#include <string>
#include <vector>

#include "RGBLutFilter.h"
#include "math/point2.h"
#include "geom/point.h"

typedef unsigned char ubyte;

class RGBpixelMap {
public:
   RGBpixelMap();
   RGBpixelMap(int height, int width);
   RGBpixelMap(const RGBpixelMap& other);
   RGBpixelMap& operator = (RGBpixelMap other);
   ~RGBpixelMap();
   bool setPixel(int x, int y, RGB color);
   RGB  getPixel(int x, int y) const;
   RGB  getPixelBilinearInter(const Point2D& p) const;
   bool readBmpFile(const char* fname);

   void draw(int dx, int sreenHeight, const std::string& label);
   void drawGridTriangle(const std::vector<int>& t, int dx, int dy);

   void trySetClickPoint(int x, int y);

   int Width() const;
   int Height() const;

   bool correctX(int x);
   bool correctY(int y);

   void toGray();
   RGBpixelMap toOrderedDither();
   RGBpixelMap toErrorDiffusion();

   RGBpixelMap applyFilter(RGBLutFilterBase* filter);

   void clear();
   bool inside(const Point2I& p) const;
   void drawImage(const RGBpixelMap& image, double alpha);
   void drawImageNearestNeib(const RGBpixelMap& image, double alpha);
   void drawImageBilinearInter(const RGBpixelMap& image, double alpha);

   friend void swap(RGBpixelMap& first, RGBpixelMap& second);

public:
   bool isGridImage = false;
   std::vector<GLintPoint>          gridPoints;
   std::vector<std::vector<int>>    gridTriangles;
   int selectedPoint = -1;
   RGB* gridPixels = nullptr;


private:
   RGB* pixels;
   int height;
   int width;
};

void swap(RGBpixelMap& a, RGBpixelMap& b);
