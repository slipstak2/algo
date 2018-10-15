#include "Fnt.h"
#include <iostream>

char* LoadFileContent(const char* file_name) {
   FILE* fp = fopen(file_name, "rb");
   if (!fp) {
      std::cerr << "Can't fopen file: '" << file_name << "'" << std::endl;
      return nullptr;
   }
   fseek(fp, 0, SEEK_END);
   long fsize = ftell(fp);
   if (!fsize) {
      std::cerr << "Empty file: '" << file_name << "'" << std::endl;
      return nullptr;
   }
   fseek(fp, 0, SEEK_SET);
   char* file_content = new char[fsize];
   if (!fread(file_content, fsize, 1, fp)) {
      std::cerr << "Error reading file" << std::endl;
      return nullptr;
   }
   fclose(fp);
   return file_content;
}

namespace fonts  {
   Fnt_Ptr Fnt::LoadFromFile(const char* file_name) {
      char* fnt_file_content = LoadFileContent(file_name);
      if (!fnt_file_content) {
         return nullptr;
      }
      FntHeader* header = (FntHeader*)fnt_file_content;
      if (header->dfPixWidth == 0) {
         std::cerr << "class Fnt support only monospace font" << std::endl;
         return nullptr;
      }
      return Fnt_Ptr(new Fnt(fnt_file_content));
   }

   Fnt::Fnt(const char* file_content) : _file_content(file_content) {
      _header = (FntHeader*)file_content;
      _font_table = &file_content[_header->dfBitsOffset];
   }

   const char* Fnt::name() {
      return (const char *)&_file_content[_header->dfFace];
   }

   unsigned short Fnt::characterWidth() {
      return _header->dfPixWidth;
   }

   unsigned short Fnt::characterHeight() {
      return _header->dfPixHeight;
   }
   
   bool Fnt::DrawTerminal(unsigned char c, unsigned char border, unsigned char background) {
      return ScanBitmap(c, [this, border, background](unsigned short row, unsigned short col, bool isSetPixel) {
         std::cout << (isSetPixel ? border : background);
         if (col == _header->dfPixWidth - 1) {
            std::cout << std::endl;
         }
      });
   }

   bool Fnt::ScanBitmap(unsigned char c, scanFntVisitor visitor) {
      if (_header->dfPixWidth <= 8) {
         return _scanBitmapWidth8(c, visitor);
      } else {
         return _scanBitmapUniversal(c, visitor);
      }
   }

   bool Fnt::_scanBitmapUniversal(unsigned char c, scanFntVisitor visitor) {
      if (_header->dfFirstChar <= c && c <= _header->dfLastChar) {
         unsigned short charH = _header->dfPixHeight;
         unsigned short charW = _header->dfPixWidth;

         unsigned short charWBytes = (charW - 1) / 8 + 1;
         const char* charOffset = _font_table + (c - _header->dfFirstChar) * charH * charWBytes;

         for (unsigned short row = 0; row < charH; ++row) {
            for (unsigned short col = 0; col < charW; ++col) {
              if (*(charOffset + (col / 8) * charH) & (0x80 >> (col % 8))) {
                 visitor(row, col, true);
              } else {
                 visitor(row, col, false);
              }
            }
            charOffset++;
         }
         return true;
      }
      else {
         std::cerr << "Unsupported font symbol: '" << c << "'";
         return false;
      }
   }

   bool Fnt::_scanBitmapWidth8(unsigned char c, scanFntVisitor visitor) {
      if (_header->dfFirstChar <= c && c <= _header->dfLastChar) {
         unsigned short charH = _header->dfPixHeight;
         unsigned short charW = _header->dfPixWidth;
         if (charW != 8) {
            std::cerr << "dfPixWidth must be 8";
            return false;
         }
         const char* charOffset = _font_table + (c - _header->dfFirstChar) * charH;

         for (unsigned short row = 0; row < charH; ++row) {
            for (unsigned short col = 0; col < charW; ++col) {
               if (*charOffset & (0x80 >> col)) {
                  visitor(row, col, true);
               } else {
                  visitor(row, col, false);
               }
            }
            charOffset++;
         }
         return true;
      } else {
         std::cerr << "Unsupported font symbol: '" << c << "'";
         return false;
      }
   }
}