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

#include "geom/circle.h"
#include "graphics/common.h"


using namespace std;

typedef unsigned char ubyte;

const double pi = 2 * acos(0.0);

int W;
int H;
int screenWidth;
int screenHeight;

struct Image {
   RGBpixelMap* bitmap;
   string label;
};

RGBpixelMap imageOriginal;
RGBpixelMap imageWarping;

vector<Image> images;
double alpha = 0;

const int DX = 15;
const int DY = 20;


vector<GLintPoint> gridPoints;

void myInit(const int W, const int H) {
   glClearColor(1.0, 1.0, 1.0, 1.0);
   glColor3f(0, 0, 0);
   glClear(GL_COLOR_BUFFER_BIT);
   glPointSize(1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluOrtho2D(0, W, 0, H);
}

void getImageWarpingCoord(int mx, int my, int &x, int &y) {
   int correctWarpingX = 2 * DX + imageOriginal.Width();
   int correctWarpingY = DY;

   x = mx - correctWarpingX;
   y = (H - my)- correctWarpingY;
}
void myMouse(int button, int state, int mx, int my) {

   if (button == GLUT_LEFT_BUTTON) {
      if (state == GLUT_DOWN) {
         int x, y;
         getImageWarpingCoord(mx, my, x, y);
         imageWarping.trySetClickPoint(x, y);
         //gridPoints.push_back({x, y});
      } else if (state == GLUT_UP) {
         imageWarping.drawTriangles(true);
         imageWarping.selectedPoint = -1;
      }
   }
   printf("button = %d; state = %d, x = %d; y = %d\n", button, state, mx, my);
}

int prvDrawX = 0, prvDrawY = 0;
void myMouseMove(int mx, int my) {
   if(imageWarping.selectedPoint != -1) {
      int x, y;
      getImageWarpingCoord(mx, my, x, y);
      imageWarping.gridPoints[imageWarping.selectedPoint] = GLintPoint(x, y);
      if (abs(prvDrawX - mx) + abs(prvDrawY - my) >= 5) {
         imageWarping.drawTriangles(false);
         prvDrawX = mx;
         prvDrawY = my;
      }     
   }
}

void myReshape(int width, int height) {
   printf("width = %d; height=%d\n", width, height);
   screenWidth = width;
   screenHeight = height;
}


void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);
 
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

void initImageWarping(RGBpixelMap& image) {
   image.isGridImage = true;
   image.gridPixels = new RGB[image.Height() * image.Width()];
   memset(image.gridPixels, 200, sizeof(RGB) * image.Height() * image.Width());

   image.gridInitPoints   = {
      {   0,  512 }, // 0
      { 256,  512 }, // 1
      { 512,  512 }, // 2
      {   0,  463 }, // 3
      { 247,  448 }, // 4
      { 512,  461 }, // 5
      {   0,  169 }, // 6
      { 169,  167 }, // 7
      { 300,  170 }, // 8
      { 512,  178 }, // 9
      {   0,  118 }, // 10
      { 153,  119 }, // 11
      { 238,  134 }, // 12
      { 330,  113 }, // 13
      { 512,  114 }, // 14
      { 237,   69 }, // 15
      {   0,    0 }, // 16
      { 243,    0 }, // 17
      { 511,    0 }  // 18
   };

   image.gridPoints = image.gridInitPoints;

   image.gridTriangles.push_back({4, 7, 8});
   image.gridTriangles.push_back({7, 8, 12});
   image.gridTriangles.push_back({8, 12, 13});
   image.gridTriangles.push_back({12, 13, 15});
   image.gridTriangles.push_back({12, 15, 11});
   image.gridTriangles.push_back({7, 12, 11});

   for (int i = 0; i < image.gridTriangles.size(); ++i) {
      image.drawTriangle(i);
   }
}
int main(int argc, char* argv[]) {

   const char* imageFileName = "data/mandrill.bmp";

   imageOriginal.readBmpFile(imageFileName);
   imageWarping = RGBpixelMap(imageOriginal);
   if (imageOriginal.Width() != imageOriginal.Height()) {
      cerr << "Image must be square" << endl;
      return -1;
   }

   initImageWarping(imageWarping);

   images.push_back({&imageOriginal, "Original"});
   images.push_back({&imageWarping,  "Image Warping"});
   
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

   W = DX * ((int)images.size() + 1);
   H = 2 * DY;
   for (auto const &image: images) {
      W += image.bitmap->Width();
      H = max(H, 2 * DY + image.bitmap->Height());
   }
   glutInitWindowSize(W, H);
   glutInitWindowPosition(100, 100);

   glutCreateWindow(PROJECT_NAME);

   myInit(W, H);
   
   glutMouseFunc(myMouse);
   glutMotionFunc(myMouseMove);
   glutKeyboardFunc(myKeyBoard);
   glutReshapeFunc(myReshape);

   glutDisplayFunc(myDisplay);
   glutMainLoop();
   return 0;
}
