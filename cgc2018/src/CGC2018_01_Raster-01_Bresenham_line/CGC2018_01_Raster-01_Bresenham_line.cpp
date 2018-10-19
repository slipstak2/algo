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

void drawSegmentBresenham(GLintPoint p1, GLintPoint p2, std::function<void(GLint, GLint)> draw) {
   int dx = p2.x - p1.x;
   int dy = p2.y - p1.y;

   int e = 2 * abs(dy) - abs(dx);
   int incrE  = 2 * abs(dy);
   int incrNE = 2 * abs(dy) - 2 * abs(dx);

   int x = p1.x, y = p1.y;
   int dirX = p2.x - p1.x > 0 ? 1 : -1;
   int dirY = p2.y - p1.y > 0 ? 1 : -1;
   draw(x, y);
   while (x != p2.x) {
      if (e > 0) {
         y += dirY;
         e += incrNE;
      }
      else {
         e += incrE;
      }
      x += dirX;
      draw(x, y);
   }
}

void drawSegmentBresenham(GLintPoint p1, GLintPoint p2) {
   int dx = p2.x - p1.x;
   int dy = p2.y - p1.y;
   if (abs(dy) <= abs(dx)) {
      drawSegmentBresenham(p1, p2, [](GLint x, GLint y) {
         drawDot(x, y);
      });
   } else {
      drawSegmentBresenham(GLintPoint(p1.y, p1.x), GLintPoint(p2.y, p2.x), [](GLint x, GLint y) {
         drawDot(y, x);
      });
   }
}

void drawSegmets(GLintPoint center, GLint R) {
   GLVector end(0, -R + 10);
   GLVector beg(0, -R / 8);
   const int PARTS = 48;
   const float pi = 2 * acos(0.f);
   float alpha = 2 * pi / PARTS;

   for (int i = 0; i < PARTS; ++i) {
      drawSegmentBresenham(
         GLintPoint(center.x + (GLint)beg.x, center.y + (GLint)beg.y),
         GLintPoint(center.x + (GLint)end.x, center.y + (GLint)end.y)
      );
      beg.turn(alpha);
      end.turn(alpha);
   }
}

void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   drawSegmets(GLintPoint(W / 2, H / 2), min(W, H) / (2 * ZOOM));

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