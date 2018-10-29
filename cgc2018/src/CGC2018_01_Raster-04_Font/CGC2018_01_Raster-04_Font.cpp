#define _CRT_SECURE_NO_WARNINGS

#include "GL/freeglut.h"
#include <GL/glut.h>

#include <iostream>
#include <string>
#include <map>

#include "fonts/Fnt.h"
#include "fonts/GSF.h"
#include "graphics/common.h"

using namespace std;

const int W = 800;
const int H = 600;

float buffer[H][W];

fonts::MonoSpacedFont_Ptr fntConsolas = fonts::Fnt::LoadFromFile("fonts/Consolas-20.fnt");
fonts::MonoSpacedFont_Ptr fntFkp = fonts::Fnt::LoadFromFile("fonts/fkpmedium-16.fnt");
fonts::MonoSpacedFont_Ptr fntPixelCarnage = fonts::Fnt::LoadFromFile("fonts/PixelCarnageMonospace-12.fnt");

fonts::MonoSpacedFont_Ptr gsf08x08 = fonts::GSF::LoadFromFile("fonts/fnt/VGA2.GSF");
fonts::MonoSpacedFont_Ptr gsfANK8X16 = fonts::GSF::LoadFromFile("fonts/fnt/ANK8X16.GSF");


map<fonts::MonoSpacedFont_Ptr, string> strings = {
   {fntPixelCarnage, "The quick brown fox jumps over the lazy dog. 0123456789"},
   {fntFkp,      "Jackdaws love my big sphinx of quartz. 0123456789"},
   {fntConsolas, "The five boxing wizards jump quickly. 0123456789"},
   {gsf08x08,    "How razorback-jumping frogs can level six piqued gymnasts!. 0123456789"},
   {gsfANK8X16,  "Cozy sphinx waves quart jug of bad milk.. 0123456789"}
};

class GLintPoint {
public:
   GLint x, y;
};

void myInit() {
   glClearColor(1.0, 1.0, 1.0, 1.0);      // background color = white
   glColor3f(0.0, 0.0, 0.0);              // drawing color    = red
   glPointSize(1);                        // point size       = 4
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, 800, 600, 0);
}

void myMouse(int button, int state, int x, int y) {
   printf("button = %d; button = %d, x = %d; y = %d\n", button, state, x, y);
}

void myReshape(int width, int height) {
   printf("width = %d; height=%d\n", width, height);
}

void drawCharacter(unsigned char c, fonts::MonoSpacedFont_Ptr fnt, GLint x, GLint y) {
   fnt->ScanBitmap(c, [x, y](unsigned short row, unsigned short col, bool isSetPixel) {
      if (isSetPixel) {
         drawDot(x + col, y + row);
      }
   });
}
void drawString(const string &s, fonts::MonoSpacedFont_Ptr fnt, GLint x, GLint y) {
   unsigned short h = fnt->characterHeight();
   unsigned short w = fnt->characterWidth();

   for (size_t i = 0; i < s.size(); ++i) {
      drawCharacter(s[i], fnt, x + (GLint)i * w, y);
   }
}

void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   int y = 10;
   for (auto item : strings) {
      drawString(item.second, item.first, 10, y);
      y += item.first->characterHeight() * 2;
   }

   glFlush();
}

void myKeyBoard(unsigned char key, int x, int y) {
   switch (key) {
   case 27:
      exit(0);
   }
}


int main(int argc, char* argv[]) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(800, 600);
   glutInitWindowPosition(100, 150);
   glutCreateWindow(PROJECT_NAME);

   glutDisplayFunc(myDisplay);
   glutMouseFunc(myMouse);
   glutKeyboardFunc(myKeyBoard);
   glutReshapeFunc(myReshape);


   myInit();
   glutMainLoop();
   return 0;
}