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

int screenWidth;
int screenHeight;

struct Image {
   RGBpixelMap* bitmap;
   string label;
};

vector<Image> images;

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
 
   int dx = DX;
   for (auto &image : images) {
      image.bitmap->draw(dx, screenHeight, image.label);
      dx += DX + image.bitmap->Width();
   }

   glutSwapBuffers();
   glFinish();
}

void myKeyBoard(unsigned char key, int x, int y) {
   switch (key) {
   case 27:
      exit(0);
   }
}

using namespace std;
int main(int argc, char* argv[]) {

   const char* imageFileName = "data/head.bmp";

   RGBpixelMap imageOriginal;
   imageOriginal.readBmpFile(imageFileName);

   RGBLutFilterGammaCorrection filterIncGammaCorrection(2.2);
   RGBLutFilterGammaCorrection filterDecGammaCorrection(0.5);

   RGBpixelMap  imageIncGamma = imageOriginal.applyFilter(&filterIncGammaCorrection);
   RGBpixelMap  imageDecGamma = imageOriginal.applyFilter(&filterDecGammaCorrection);
   
   images.push_back({&imageIncGamma, "Gamma correction: 2.2"});
   images.push_back({&imageOriginal, "Original"});
   images.push_back({&imageDecGamma, "Gamma correction: 0.5"});
   
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

   const int W = imageOriginal.Width() * images.size() + (images.size() + 1) * DX;
   const int H = imageOriginal.Height() + 2 * DY;
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