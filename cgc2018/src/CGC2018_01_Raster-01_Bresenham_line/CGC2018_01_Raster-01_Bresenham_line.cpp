#include "GL/freeglut.h"
#include <GL/glut.h>

#include <iostream>
#include <algorithm>

using namespace std;

const int W = 800;
const int H = 600;

float buffer[H][W];

class GLintPoint {
public:
   GLintPoint(GLint x, GLint y) 
      : x(x)
      , y(y)
   {}
   void turn(float alpha) {
      float nextX = x * cos(alpha) - y * sin(alpha);
      float nextY = x * sin(alpha) + y * cos(alpha);
      x = (GLint)nextX;
      y = (GLint)nextY;
   }

public:
   GLint x, y;
};

void myInit() {
   glClearColor(1.0, 1.0, 1.0, 1.0);      // background color = white
   glColor3f(1.0, 0.0, 0.0);              // drawing color    = red
   glPointSize(2);                        // point size       = 4
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //gluOrtho2D(0, 800, 600, 0);


   //glScalef(1.f, 1.f, 2.f);
   gluOrtho2D(W / 4, 3 * W / 4, H / 4, 3 * H / 4);
   
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

void drawSegment(GLintPoint p1, GLintPoint p2) {
   if (p1.x != p2.x) {
      GLint x = p1.x;
      float y = (float)p1.y;

      float slope = ((float)p2.y - p1.y) / ((float)p2.x - p1.x);
      GLint deltaX = p2.x > p1.x ? 1 : -1;
      while (x != p2.x) {
         drawDot(x, (GLint)y);
         y += slope;
         x += deltaX;
      }
   } else if (p1.y != p2.y) {
      float x = (float)p1.x;
      GLint y = p1.y;
      float slope = ((float)p2.x - p1.x) / ((float)p2.y - p1.y);
      GLint deltaY = p2.y > p1.y ? 1 : -1;
      while (y != p2.y) {
         drawDot((GLint)x, y);
         y += deltaY;
         x += slope;
      }
   }
}

void drawSegmets(GLintPoint center, GLint R) {

   GLintPoint v(0, -R);
   const int PARTS = 16;
   const float pi = 2 * acos(0.f);
   float alpha = 2 * pi / PARTS;

   for (int i = 0; i < PARTS; ++i) {
      drawSegment(center, GLintPoint(center.x + v.x, center.y + v.y));
      v.turn(alpha);
   }
}

void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   drawSegmets(GLintPoint(W / 2, H / 2), min(W, H) / 4 - 10);

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