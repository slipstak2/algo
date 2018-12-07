#include "RGBpixelMap.h"
#include "common.h"

#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void swap(RGBpixelMap& a, RGBpixelMap& b) {
   swap(a.height, b.height);
   swap(a.width, b.width);
   swap(a.pixels, b.pixels);
}

typedef unsigned short ushort;
typedef unsigned long ulong;

RGBpixelMap::RGBpixelMap()
   : pixels(nullptr)
   , height(0)
   , width(0)
{}

RGBpixelMap::RGBpixelMap(int height, int width)
   : height(height)
   , width(width)
{
   pixels = new RGB[height * width];
}

RGBpixelMap::RGBpixelMap(const RGBpixelMap& other)
   : height(other.height)
   , width(other.width)
{
   pixels = new RGB[height * width];
   memcpy(pixels, other.pixels, sizeof(RGB) * height * width);
}

RGBpixelMap& RGBpixelMap::operator = (RGBpixelMap other) {
   swap(*this, other);
   return *this;
}

RGBpixelMap::~RGBpixelMap() {
   delete[] pixels;
}

bool RGBpixelMap::setPixel(int x, int y, RGB color) {
   if (0 <= x && x < width) {
      if ( 0 <= y && y < height)  {
         pixels[width * y + x] = color;
         return true;
      }
   }
   cout << "MISS set" << endl;
   return false;
}

RGB  RGBpixelMap::getPixel(int x, int y) const {
   if (0 <= x && x < width) {
      if ( 0 <= y && y < height)  {
         return pixels[width * y + x];
      }
   }
   cout << "MISS get" << endl;
   return {0, 0, 0};
}

bool RGBpixelMap::inside(const Point2DI& p) const {
   if (0 <= p.x && p.x < width) {
      if (0 <= p.y && p.y < height) {
         return true;
      }
   }
   return false;
}
RGB  RGBpixelMap::getPixelBilinearInter(const Point2DD& p) const {
   Point2DI p1((int)(p.x),     (int)(p.y));
   Point2DI p2((int)(p.x),     (int)(p.y + 1));
   Point2DI p3((int)(p.x + 1), (int)(p.y + 1));
   Point2DI p4((int)(p.x + 1), (int)(p.y));

   if (inside(p1) && inside(p2) && inside(p3) && inside(p4)) {
      RGBD color1 = getPixel(p1.x, p1.y);
      RGBD color2 = getPixel(p2.x, p2.y);
      RGBD color3 = getPixel(p3.x, p3.y);
      RGBD color4 = getPixel(p4.x, p4.y);
      
      RGBD color5 = RGBD::linearInterpolation(color1, color2, p1.y, p.y, p2.y);
      RGBD color6 = RGBD::linearInterpolation(color4, color3, p4.y, p.y, p3.y);
      RGBD color7 = RGBD::linearInterpolation(color5, color6, p1.x, p.x, p4.x);
      return color7.toRGB();
   } else {
      return getPixel(p.x, p.y);
   }
}

void RGBpixelMap::draw(int dx, int sreenHeight, const string& label) {
   int dy = (sreenHeight - height) / 2;
   glRasterPos2i(dx, dy);
   glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
   
   glRasterPos2i(dx + 15, dy - 15);
   for (char c: label) {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
   }
}

int RGBpixelMap::Width() const {
   return width;
}

bool RGBpixelMap::correctX(int x) {
   return 0 <= x && x < width;
}

bool RGBpixelMap::correctY(int y) {
   return 0 <= y && y < height;
}

int RGBpixelMap::Height() const {
   return height;
}

// http://nsucgcourse.github.io/lectures/Lecture04/Slide_04_Tarancev_Filters_Dither.pdf
void RGBpixelMap::toGray() {
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB rgb = getPixel(x, y);
         ubyte G = rgb.gray();
         setPixel(x, y, {G, G, G});
      }
   }
}

RGBpixelMap RGBpixelMap::toOrderedDither() {
   RGBpixelMap result(height, width);
   int pattern[8][8] = {
      { 0, 32,  8, 40,  2, 34, 10, 42},
      {48, 16, 56, 24, 50, 18, 58, 26},
      {12, 44,  4, 36, 14, 46,  6, 38},
      {60, 28, 52, 20, 62, 30, 54, 22},
      { 3, 35, 11, 43,  1, 33,  9, 41},
      {51, 19, 59, 27, 49, 17, 57, 25},
      {15, 47,  7, 39, 13, 45,  5, 37},
      {63, 31, 55, 23, 61, 29, 53, 21} 
   };

   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB p = getPixel(x, y);
         assert(p.isGray());
         if (p.r / 4 < pattern[x & 7][y & 7]) {
            result.setPixel(x, y, BLACK);
         } else {
            result.setPixel(x, y, WHITE);
         }
      }
   }
   return result;
}
RGBpixelMap RGBpixelMap::toErrorDiffusion() {
   /*
      * 7   * 1/16
    3 5 1 
   */
   const int MOVES = 4;
   static const int dx[MOVES] = {1, -1, 0, 1};
   static const int dy[MOVES] = {0,  1, 1, 1};
   static const int de[MOVES] = {7,  3, 5, 1};
   double div = 16.0;


   vector<vector<double>> bitmap(width, vector<double>(height));
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB pixel = getPixel(x,y);
         assert(pixel.isGray());
         bitmap[x][y] = pixel.r;
      }
   }
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         double oldPixel = bitmap[x][y];
         double newPixel = oldPixel < 128 ? 0 : 255;
         bitmap[x][y] = newPixel;
         double quant_error = oldPixel - newPixel;

         for (int m = 0; m < MOVES; ++m) {
            int ny = y + dy[m];
            int nx = x + dx[m];
            if (correctX(nx) && correctY(ny)) {
               bitmap[nx][ny] += quant_error * de[m] / div;
            }
         }
      }
   }

   RGBpixelMap result(height, width);
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         ubyte g = (ubyte)bitmap[x][y];
         result.setPixel(x, y, {g, g, g});
      }
   }
   return  result;
}

RGBpixelMap RGBpixelMap::applyFilter(RGBLutFilterBase* filter) {
   RGBpixelMap result(height, width);
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB pixel = getPixel(x,y);
         filter->apply(pixel);
         result.setPixel(x, y, pixel);
      }
   }
   return result;
}

void RGBpixelMap::clear() {
   memset(pixels, -1, sizeof(RGB) * width * height);
}
void RGBpixelMap::drawImage(const RGBpixelMap& image, double alpha) {
   
   clear();   
   int offsetX = (width - image.width) / 2;
   int offsetY = (height - image.height) / 2;
   for (int x = 0; x < image.width; ++x) {
      for (int y = 0; y < image.height; ++y) {
         Point2DI p1(x - image.width / 2, y - image.height / 2);
         Point2DD p2 = Rotate(p1, alpha);
         Point2DI p (round(p2.x + image.width / 2.0), round(p2.y + image.height / 2.0));
         setPixel(offsetX + p.x, offsetX + p.y, image.getPixel(x, y));
      }
   }
}

void RGBpixelMap::drawImageNearestNeib(const RGBpixelMap& image, double alpha) {

   clear();

   int offsetX = (width - image.width) / 2;
   int offsetY = (height - image.height) / 2;
   
   for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
         Point2DI p(x - width / 2, y - height / 2);
         Point2DD p2 = ReverseRotate(p, alpha);
         Point2DI p1(round(p2.x + image.width / 2.0), round(p2.y + image.height / 2.0));
         if (0 <= p1.x && p1.x < image.width) {
            if (0 <= p1.y && p1.y < image.height) {
               setPixel(x, y, image.getPixel(p1.x, p1.y));
            }
         }
      }
   }
}


void RGBpixelMap::drawImageBilinearInter(const RGBpixelMap& image, double alpha) {

   clear();

   int offsetX = (width - image.width) / 2;
   int offsetY = (height - image.height) / 2;

   for (int x = 0; x < width; ++x) {
      for (int y = 0; y < height; ++y) {
         Point2DI p(x - width / 2, y - height / 2);
         Point2DD p2 = ReverseRotate(p, alpha);
         Point2DD p1(p2.x + image.width / 2.0, p2.y + image.height / 2.0);
         if (0 <= p1.x && p1.x < image.width) {
            if (0 <= p1.y && p1.y < image.height) {
               setPixel(x, y, image.getPixelBilinearInter(p1));
            }
         }
      }
   }
}


ushort getShort(fstream& inf)
{ //BMP format uses little-endian integer types
  // get a 2-byte integer stored in little-endian form
   char ic;
   ushort ip;
   inf.get(ic); ip = ic;
   inf.get(ic); ip |= ((ushort)ic << 8);
   return ip;
}

ulong getLong(fstream& inf)
{  //BMP format uses little-endian integer types
   // get a 4-byte integer stored in little-endian form
   ulong ip = 0;
   char ic = 0;
   unsigned char uc = ic;
   inf.get(ic); uc = ic; ip = uc;
   inf.get(ic); uc = ic; ip |=((ulong)uc << 8);
   inf.get(ic); uc = ic; ip |=((ulong)uc << 16);
   inf.get(ic); uc = ic; ip |=((ulong)uc << 24);
   return ip;
}

bool RGBpixelMap::readBmpFile(const char* fname) 
{     
   fstream inf;
   inf.open(fname, ios::in | ios::binary);
   if (!inf) {
      cout << " can't open file: " << fname << endl; 
      return false; 
   }
   int k, row, col, numPadBytes, nBytesInRow;

   char ch1, ch2;
   inf.get(ch1); inf.get(ch2); //type: always 'BM'
   ulong fileSize       = getLong(inf);
   ushort reserved1     = getShort(inf);  // always 0
   ushort reserved2     = getShort(inf);  // always 0 
   ulong offBits        = getLong(inf);   // offset to image - unreliable
   ulong headerSize     = getLong(inf);   // always 40
   ulong numCols        = getLong(inf);   // number of columns in image
   ulong numRows        = getLong(inf);   // number of rows in image
   ushort planes        = getShort(inf);  // always 1 
   ushort bitsPerPixel  = getShort(inf);  // 8 or 24; allow 24 here
   ulong compression    = getLong(inf);   // must be 0 for uncompressed 
   ulong imageSize      = getLong(inf);   // total bytes in image 
   ulong xPels          = getLong(inf);   // always 0 
   ulong yPels          = getLong(inf);   // always 0 
   ulong numLUTentries  = getLong(inf);   // 256 for 8 bit, otherwise 0 
   ulong impColors      = getLong(inf);   // always 0 
   if (bitsPerPixel != 24) { 
      cerr << "not a 24 bit/pixelimage, or is compressed!\n";
      inf.close(); 
      return false;
   }
   // add bytes at end of each row so total # is a multiple of 4
   // round up 3*numCols to next mult. of 4
   nBytesInRow = ((3 * numCols + 3) / 4) * 4;
   numPadBytes = nBytesInRow - 3 * numCols; // need this many
   
   height = numRows; // set class's data members
   width = numCols;
   pixels = new RGB[height * width]; //make space for array
   if (!pixels){
      return false; // out of memory!
   }
   long count = 0;
   char dum;
   for (row = 0; row < height; row++) // read pixel values
   {
      for (col = 0; col < width; col++)
      {
         char r, g, b;
         inf.get(b); inf.get(g); inf.get(r);
         pixels[count].r = r;
         pixels[count].g = g;
         pixels[count].b = b;
         ++count;
      }
      for (k = 0; k < numPadBytes; k++) //skip pad bytes at row's end
         inf >> dum;
   }
   inf.close(); 
   return true;
}