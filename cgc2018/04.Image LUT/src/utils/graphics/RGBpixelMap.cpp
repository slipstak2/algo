#include "RGBpixelMap.h"
#include "common.h"

#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

RGB BLACK = {0, 0, 0};
RGB WHITE = {255, 255, 255};

bool operator == (const RGB& a, const RGB& b) {
   return memcmp(&a, &b, sizeof(RGB)) == 0;
}

bool operator != (const RGB& a, const RGB& b) {
   return !(a == b);
}

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

RGB  RGBpixelMap::getPixel(int x, int y) {
   if (0 <= x && x < width) {
      if ( 0 <= y && y < height)  {
         return pixels[width * y + x];
      }
   }
   cout << "MISS get" << endl;
   return {0, 0, 0};
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

int RGBpixelMap::Width() {
   return width;
}

bool RGBpixelMap::correctX(int x) {
   return 0 <= x && x < width;
}

bool RGBpixelMap::correctY(int y) {
   return 0 <= y && y < height;
}

int RGBpixelMap::Height() {
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

int RGBpixelMap::middleBrightness() {
   long long middleBrightnessRed = 0, middleBrightnessGreen = 0, middleBrightnessBlue = 0;
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB pixel = getPixel(x,y);
         middleBrightnessRed   += pixel.r;
         middleBrightnessGreen += pixel.g;
         middleBrightnessBlue  += pixel.b;
      }
   }
   // 0.299 * r + 0.587 * g + 0.114 * b;
   return ((middleBrightnessRed * 77 + middleBrightnessGreen * 150 + middleBrightnessBlue * 29) >> 8) / (width * height);
}

RGBpixelMap RGBpixelMap::toNegative() {
   int LUT[256];
   memset(LUT, 1, sizeof(LUT));
   for (int i = 0; i <= 255; ++i) {
      LUT[i] = 255 - i;
   }

   RGBpixelMap negative(height, width);
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB oldPixel = getPixel(x,y);
         RGB newPixel = { LUT[oldPixel.r], LUT[oldPixel.g], LUT[oldPixel.b] };
         negative.setPixel(x, y, newPixel);
      }
   }
   return negative;
}

// deltaBrightness in [0, 255]
RGBpixelMap RGBpixelMap::changeBrightness(int deltaBrightness) {
   int LUT[256];
   memset(LUT, 0, sizeof(LUT));
   for (int i = 0; i <= 255; ++i) {
      LUT[i] = clamp(i + deltaBrightness, 0, 255);
   }

   RGBpixelMap result(height, width);
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB oldPixel = getPixel(x,y);
         RGB newPixel = { LUT[oldPixel.r], LUT[oldPixel.g], LUT[oldPixel.b] };
         result.setPixel(x, y, newPixel);
      }
   }
   return result;
}

// deltaContrast in [0, 255]
RGBpixelMap RGBpixelMap::changeContrast(int deltaContrast) {
   int LUT[256];
   memset(LUT, 0, sizeof(LUT));
   for (int i = 0; i <= 255; ++i) {
      double contrast = deltaContrast;
      double factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
      LUT[i] = clamp(factor * (i  - 128) + 128, 0, 255);
    }

   RGBpixelMap result(height, width);
   for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
         RGB oldPixel = getPixel(x,y);
         RGB newPixel = { LUT[oldPixel.r], LUT[oldPixel.g], LUT[oldPixel.b] };
         result.setPixel(x, y, newPixel);
      }
   }

   return result;
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