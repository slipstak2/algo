#include "MonoSpacedFont.h"

namespace fonts {
   class GSF: public MonoSpacedFont
   {
#pragma pack(push, 1)
      struct GSFHeader {
         unsigned char   firstCharCode;
         unsigned short  charsCnt;
         unsigned char   charPixWidth;
         unsigned char   charPixHeight;
         unsigned char   magic;
      };
#pragma pack(pop)

   public:
      static MonoSpacedFont_Ptr LoadFromFile(const char* file_name);
      unsigned short characterWidth() override;
      unsigned short characterHeight() override;

      bool DrawTerminal(unsigned char c, unsigned char border='X', unsigned char background='.');
      bool ScanBitmap(unsigned char c, scanFontVisitor visitor) override;

   private:
      GSF(const char* file_content);

   private:
      GSFHeader*  _header;
      const char* _font_table;
   };
}