#define _CRT_SECURE_NO_WARNINGS

#include "GL/freeglut.h"
#include <GL/glut.h>

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

#include "geom/point.h"

using namespace std;

const int W = 800;
const int H = 600;
const int ZOOM = 1;

class Shape {

};

std::vector<GLfloatPoint>  points;

void readShapeFromFile() {
   //russia-min-polyline.txt
}

void myInit() {
   glClearColor(1.0, 1.0, 1.0, 1.0);      // background color = white
   glColor3f(1.0, 0.0, 0.0);              // drawing color    = red
   glPointSize((GLfloat)ZOOM);            // point size       = 4
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   
   gluOrtho2D(0, W, H, 0);
  
}

void myMouse(int button, int state, int x, int y) {
   printf("button = %d; button = %d, x = %d; y = %d\n", button, state, x, y);
}

void myReshape(int width, int height) {
   printf("width = %d; height=%d\n", width, height);
}

void drawLine(GLfloatPoint p1, GLfloatPoint p2) {
   glBegin(GL_LINES);
      glVertex2f(p1.x, p1.y);
      glVertex2f(p2.x, p2.y);
   glEnd();
}


void drawShape() {
   for (int i = 0; i < points.size(); ++i) {
      drawLine(points[i], points[(i + 1) % points.size()]);
   }
}

void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   drawShape();

   glFlush();
}

void myKeyBoard(unsigned char key, int x, int y) {
   switch (key) {
   case 27:
      exit(0);
   }
}

using namespace std;
int main(int argc, char* argv[]) {
   freopen("data/russia-min-polyline.txt", "r", stdin);
   float x, y;
   
   while (cin >> x >> y) {
      points.push_back(GLfloatPoint(x / 1.5, y / 1.5));
   }
   float minX = points[0].x;
   float maxX = points[0].x;

   float minY = points[0].y;
   float maxY = points[0].y;

   for (const GLfloatPoint &p : points) {
      minX = min(minX, p.x);
      maxX = max(maxX, p.x);
      minY = min(minY, p.y);
      maxY = max(maxY, p.y);
   }

   for (GLfloatPoint &p : points) {
      p.x -= minX;
      p.y -= minY;
   }


   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(W, H);
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