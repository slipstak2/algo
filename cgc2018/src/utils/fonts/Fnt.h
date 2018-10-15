// http://www.undocprint.org/formats/font_formats#microsoft_windows_r_font_formats
// http://justsolve.archiveteam.org/wiki/FNT_(Windows_Font)
// http://www.os2museum.com/files/docs/win10sdk/windows-1.03-sdk-prgref-1986.pdf

#include <memory>
#include <functional>

namespace fonts  {

   class Fnt;
   typedef std::shared_ptr<Fnt> Fnt_Ptr;

   class Fnt
   {
#pragma pack(push, 1)
      struct FntHeader {
         unsigned short  dfVersion;
         unsigned long   dfSize;
         char            dfCopyright[60];
         unsigned short  dfType;
         unsigned short  dfPoints;
         unsigned short  dfVertRes;
         unsigned short  dfHorizRes;
         unsigned short  dfAscent;
         unsigned short  dfInternalLeading;
         unsigned short  dfExternalLeading;
         unsigned char   dfItalic;
         unsigned char   dfUnderline;
         unsigned char   dfStrikeOut;
         unsigned short  dfWeight;
         unsigned char   dfCharSet;
         unsigned short  dfPixWidth;
         unsigned short  dfPixHeight;
         unsigned char   dfPitchAndFamily;
         unsigned short  dfAvgWidth;
         unsigned short  dfMaxWidth;
         unsigned char   dfFirstChar;
         unsigned char   dfLastChar;
         unsigned char   dfDefaultChar;
         unsigned char   dfBreakChar;
         unsigned short  dfWidthBytes;
         unsigned long   dfDevice;
         unsigned long   dfFace;
         unsigned long   dfBitsPointer;
         unsigned long   dfBitsOffset;
         unsigned char   dfReserved;
         unsigned long   dfFlags;
      };
#pragma pack(pop)

      typedef std::function<void(unsigned short x, unsigned short y, bool is_set_pixel)> scanFntVisitor;

   public:
      static Fnt_Ptr LoadFromFile(const char* file_name);
      const char* name();
      unsigned short characterWidth();
      unsigned short characterHeight();

      bool DrawTerminal(unsigned char c, unsigned char border='X', unsigned char background='.');
      bool ScanBitmap(unsigned char c, scanFntVisitor visitor);
      
      ~Fnt() {
         delete [] _file_content;
      }
   private:
      Fnt(const char* file_content);
      bool _scanBitmapWidth8(unsigned char c, scanFntVisitor visitor);      // for understanding format
      bool _scanBitmapUniversal(unsigned char c, scanFntVisitor visitor);   // thanks: https://github.com/DisplayCore/FNT/blob/0b266707dd4ac14fd9f34ff9545a136ac0d0d861/FNT.cpp 

      
   private:
      FntHeader*  _header;
      const char* _font_table;

      const char* _file_content;
   };
   
}