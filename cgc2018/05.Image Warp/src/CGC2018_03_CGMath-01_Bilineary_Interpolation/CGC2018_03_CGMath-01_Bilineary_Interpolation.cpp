#define _CRT_SECURE_NO_WARNINGS

#include "GL/freeglut.h"
#include <GL/glut.h>

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>

#include "geom/point.h"
#include "graphics/common.h"
#include "graphics/RGBpixelMap.h"

using namespace std;

typedef unsigned char ubyte;

const double pi = 2 * acos(0.0);

int screenWidth;
int screenHeight;

struct Image {
   RGBpixelMap* bitmap;
   string label;
};

RGBpixelMap imageOriginal;
RGBpixelMap imageRotate;
RGBpixelMap imageRotateNeib;
RGBpixelMap imageRotateBilinearInter;

vector<Image> images;
double alpha = 0;

void myInit(const int W, const int H) {
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glColor3f(0, 0, 0);
   glClear(GL_COLOR_BUFFER_BIT);
   glPointSize(1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluOrtho2D(0, W, 0, H);
}

void myMouse(int button, int state, int mx, int my) {
   printf("button = %d; state = %d, x = %d; y = %d\n", button, state, mx, my);
}

void myReshape(int width, int height) {
   printf("width = %d; height=%d\n", width, height);
   screenWidth = width;
   screenHeight = height;
}

const int DX = 15;
const int DY = 20;
void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);
   imageRotate.drawImage(imageOriginal, alpha);
   imageRotateNeib.drawImageNearestNeib(imageOriginal, alpha);
   imageRotateBilinearInter.drawImageBilinearInter(imageOriginal, alpha);
   alpha += pi / 1800;
 
   int dx = DX;
   for (auto &image : images) {
      image.bitmap->draw(dx, screenHeight, image.label);
      dx += DX + image.bitmap->Width();
   }

   glutSwapBuffers();
   glFinish();
   glutPostRedisplay();
}

void myKeyBoard(unsigned char key, int x, int y) {
   switch (key) {
   case 27:
      exit(0);
   }
}

using namespace std;
int main(int argc, char* argv[]) {

   const char* imageFileName = "data/mandrill300.bmp";

   imageOriginal.readBmpFile(imageFileName);
   if (imageOriginal.Width() != imageOriginal.Height()) {
      cerr << "Image must be square" << endl;
      return -1;
   }
   imageRotate              =  RGBpixelMap(imageOriginal.Height() * sqrt(2.0) + 4, imageOriginal.Width() * sqrt(2.0) + 4);
   imageRotateNeib          =  RGBpixelMap(imageOriginal.Height() * sqrt(2.0) + 4, imageOriginal.Width() * sqrt(2.0) + 4);
   imageRotateBilinearInter =  RGBpixelMap(imageOriginal.Height() * sqrt(2.0) + 4, imageOriginal.Width() * sqrt(2.0) + 4);
   

   images.push_back({&imageOriginal, "Original"});
   images.push_back({&imageRotate,   "Transform: original -> rotate"});
   images.push_back({&imageRotateNeib, "Nearest neighbor"});
   images.push_back({&imageRotateBilinearInter, "Bilinear interpolation"});
   
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

   int W = DX * ((int)images.size() + 1);
   int H = 2 * DY;
   for (auto const &image: images) {
      W += image.bitmap->Width();
      H = max(H, 2 * DY + image.bitmap->Height());
   }
   glutInitWindowSize(W, H);
   glutInitWindowPosition(100, 100);

   glutCreateWindow(PROJECT_NAME);

   myInit(W, H);
   
   glutMouseFunc(myMouse);
   glutKeyboardFunc(myKeyBoard);
   glutReshapeFunc(myReshape);

   glutDisplayFunc(myDisplay);
   glutMainLoop();
   return 0;
}
