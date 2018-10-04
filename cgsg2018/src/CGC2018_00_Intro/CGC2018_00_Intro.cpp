#include "GL/freeglut.h"

#include <iostream>

using namespace std;

void Display()
{
   glClear(GL_COLOR_BUFFER_BIT);
   glutSwapBuffers();
}


int main(int argc, char* argv[]) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(800, 600);
   glutCreateWindow("CGC2018_00_Intro");
   glutDisplayFunc(Display);


   glutMainLoop();
   return 0;
}