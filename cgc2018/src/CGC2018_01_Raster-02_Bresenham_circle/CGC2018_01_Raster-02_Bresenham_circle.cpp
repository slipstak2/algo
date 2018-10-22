#include "GL/freeglut.h"
#include <GL/glut.h>

#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

const int W = 800;
const int H = 600;
const int ZOOM = 2;

float buffer[H][W];

class GLintPoint {
public:
   GLintPoint(GLint x, GLint y) 
      : x(x)
      , y(y)
   {}

public:
   GLint x, y;
};


class GLVector {
public:
   GLVector(float x, float y) 
      : x(x)
      , y(y)
   {}
   GLVector(int x, int y) 
      : x((GLfloat)x)
      , y((GLfloat)y)
   {}
   void turn(float alpha) {
      GLfloat nextX = x * cos(alpha) - y * sin(alpha);
      GLfloat nextY = x * sin(alpha) + y * cos(alpha);
      x = nextX;
      y = nextY;
   }

public:
   GLfloat x, y;
};

void myInit() {
   glClearColor(1.0, 1.0, 1.0, 1.0);      // background color = white
   glColor3f(1.0, 0.0, 0.0);              // drawing color    = red
   glPointSize((GLfloat)ZOOM);            // point size       = 4
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   gluOrtho2D(
      W / 2 - W / (2 * ZOOM),
      W / 2 + W / (2 * ZOOM),
      H / 2 - H / (2 * ZOOM),
      H / 2 + H / (2 * ZOOM)
   );
  
}

void myMouse(int button, int state, int x, int y) {
   printf("button = %d; button = %d, x = %d; y = %d\n", button, state, x, y);
}

void myReshape(int width, int height) {
   printf("width = %d; height=%d\n", width, height);
}

void drawDot(GLint x, GLint y) {
   glBegin(GL_POINTS);
      glVertex2i(x, y);
   glEnd();
}

void _drawDots4(GLintPoint center, GLint R) {
   drawDot(center.x, center.y - R);
   drawDot(center.x, center.y + R);
   drawDot(center.x - R, center.y);
   drawDot(center.x + R, center.y);
}

void _drawDots8(GLintPoint center, GLint x, GLint y) {
   drawDot(center.x + x, center.y + y);
   drawDot(center.x - x, center.y + y);
   drawDot(center.x - x, center.y - y);
   drawDot(center.x + x, center.y - y);
   drawDot(center.x + y, center.y + x);
   drawDot(center.x - y, center.y + x);
   drawDot(center.x - y, center.y - x);
   drawDot(center.x + y, center.y - x);
}

void drawCircleBresenham(GLintPoint center, GLint R) {
   int x = 0, y = R;
   int f = 1 - R;
   int incrE = 3;
   int incrSE = 5 - 2 * R;
   _drawDots4(center, R);
   while (x <= y) {
      if (f > 0) {
         y--;
         f += incrSE;
         incrSE = incrSE + 4;
      } else {
         f += incrE;
         incrSE += 2;
      }
      incrE += 2;
      x++;
      _drawDots8(center, x, y);

   }
}
void drawCircles(GLintPoint center, GLint R) {
   for (int r = R - 10; r >= 10; r -= 10) {
      drawCircleBresenham(center, r);
   }
}

void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   drawCircles(GLintPoint(W / 2, H / 2), min(W, H) / (2 * ZOOM));

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
   glutInitWindowPosition(300, 300);
   glutCreateWindow(PROJECT_NAME);

   myInit();

   glutDisplayFunc(myDisplay);
   glutMouseFunc(myMouse);
   glutKeyboardFunc(myKeyBoard);
   glutReshapeFunc(myReshape);

   glutMainLoop();
   return 0;
}