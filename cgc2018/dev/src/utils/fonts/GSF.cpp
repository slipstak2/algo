#include "GSF.h"


namespace fonts  {
   MonoSpacedFont_Ptr GSF::LoadFromFile(const char* file_name) {
      char* fnt_file_content = LoadFileContent(file_name);
      if (!fnt_file_content) {
         return nullptr;
      }
      GSFHeader* header = (GSFHeader*)fnt_file_content;

      return MonoSpacedFont_Ptr(new GSF(fnt_file_content));
   }

   GSF::GSF(const char* file_content) : MonoSpacedFont(file_content) {
      _header = (GSFHeader*)file_content;
      _font_table = &file_content[sizeof(GSFHeader)];
   }


   unsigned short GSF::characterWidth() {
      return _header->charPixWidth;
   }

   unsigned short GSF::characterHeight() {
      return _header->charPixHeight;
   }

   bool GSF::DrawTerminal(unsigned char c, unsigned char border, unsigned char background) {
      return ScanBitmap(c, [this, border, background](unsigned short row, unsigned short col, bool isSetPixel) {
         std::cout << (isSetPixel ? border : background);
         if (col == _header->charPixWidth - 1) {
            std::cout << std::endl;
         }
      });
   }

   bool GSF::ScanBitmap(unsigned char c, scanFontVisitor visitor) {
      if (_header->firstCharCode <= c && c <= _header->firstCharCode + _header->charsCnt) {
         unsigned short charH = characterHeight();
         unsigned short charW = characterWidth();
         const char* charOffset = _font_table + (c - _header->firstCharCode) * charH;

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