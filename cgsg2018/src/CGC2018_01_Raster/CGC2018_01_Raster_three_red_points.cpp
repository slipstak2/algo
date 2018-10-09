#include "GL/freeglut.h"

#include <iostream>

using namespace std;

const int W = 800;
const int H = 600;

float buffer [H][W];

void myInit() {
   glClearColor(1.0, 1.0, 1.0, 1.0);      // background color = white
   glColor3f(1.0, 0.0, 0.0);              // drawing color    = red
   glPointSize(4);                        // point size       = 4
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, 800, 0, 600);            
}

void myMouse(int button, int state, int x, int y) {
   printf("button = %d; button = %d, x = %d; y = %d\n", button, state, x, y);
}

void myReshape(int width, int height) {
   printf("width = %d; height=%d\n", width, height);
}

void myDisplay(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   glBegin(GL_POINTS);
      glVertex2i(100, 50);
      glVertex2i(100, 130);
      glVertex2i(150, 130);
   glEnd();

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