#include "GL/freeglut.h"

#include <iostream>

using namespace std;

void Display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
}

void KeyboardCB(unsigned char key, int x, int y) {
   switch (key) {
      case 27:
         exit(0);
   }
}

int main(int argc, char* argv[]) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(800, 600);
   glutCreateWindow(PROJECT_NAME);

   glutDisplayFunc(Display);
   glutKeyboardFunc(KeyboardCB);

   glutMainLoop();
   return 0;
}