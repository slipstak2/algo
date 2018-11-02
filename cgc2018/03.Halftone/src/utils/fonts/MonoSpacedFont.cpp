#include "MonoSpacedFont.h"


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
