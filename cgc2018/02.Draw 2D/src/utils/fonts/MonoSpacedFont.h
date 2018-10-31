#pragma once

#include <iostream>
#include <memory>
#include <functional>

char* LoadFileContent(const char* file_name);

namespace fonts {
   typedef std::function<void(unsigned short x, unsigned short y, bool is_set_pixel)> scanFontVisitor;

   class MonoSpacedFont;
   typedef std::shared_ptr<MonoSpacedFont> MonoSpacedFont_Ptr;

   class MonoSpacedFont {
   public:
      MonoSpacedFont(const char* file_content)
         : _file_content(file_content)
      {}
      virtual ~ MonoSpacedFont() {
         delete [] _file_content;
      }

      virtual unsigned short characterWidth() = 0;
      virtual unsigned short characterHeight() = 0;
      virtual bool ScanBitmap(unsigned char c, scanFontVisitor visitor) = 0;

   protected:
      const char* _file_content;
   };

};