#define _CRT_SECURE_NO_WARNINGS

#include "GL/freeglut.h"
#include <GL/glut.h>

#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>

#include "geom/point.h"
#include "geom/line.h"
#include "graphics/common.h"

using namespace std;

typedef unsigned char ubyte;

const int W = 800;
const int H = 600;


typedef vector<GLfloatPoint> shape;
typedef vector<shape>        shapes;


struct RGB {
   ubyte r,g,b;
};

bool operator == (const RGB& a, const RGB& b) {
   return memcmp(&a, &b, sizeof(RGB)) == 0;
}

bool operator != (const RGB& a, const RGB& b) {
   return !(a == b);
}

RGB* pixels = new RGB[W * H];

RGB RED   = {255, 0, 0};
RGB GREEN = {0, 255, 0};
RGB BLUE  = {0, 0, 255};

RGB WHITE      = {255, 255, 255};
RGB YELLOW     = {255, 216, 0};
RGB ORANGE     = {255, 106, 0};
RGB LITE_GREEN = {182, 255, 0};
RGB AQUE       = {0, 255, 255};

RGB Lollypop0 = WHITE;
RGB Lollypop1 = {255, 202, 212};
RGB Lollypop2 = {247, 175, 157};
RGB Lollypop3 = {176, 208, 211};
RGB Lollypop4 = {192, 132, 151};

RGB BACKGROUND_COLOR = WHITE;
RGB BORDER_COLOR = RED;

vector<RGB> FILL_COLORS = {Lollypop0, Lollypop1, Lollypop2, Lollypop3, Lollypop4};
int FILL_COLOR_POS = 0;

RGB getFILL_COLOR(RGB clickColor, int attempts = 2) {
   FILL_COLOR_POS = (FILL_COLOR_POS + 1) % FILL_COLORS.size();
   if (attempts && clickColor == FILL_COLORS[FILL_COLOR_POS]) {
      return getFILL_COLOR(clickColor, attempts - 1);
   } else {
      return FILL_COLORS[FILL_COLOR_POS];
   }
}

shapes Shapes;

bool loadShapesFromFile(const char* file_name) {
   FILE* fp = fopen(file_name, "rb");
   if (!fp) {
      std::cerr << "Can't fopen file: '" << file_name << "'" << std::endl;
      return false;
   }
   float x, y;
   int n;
   while (fscanf(fp, "%d\n", &n) != -1) {
      shape s;
      for (int i = 0; i < n; ++i) {
         fscanf(fp, "%f %f\n", &x, &y);
         s.push_back(GLfloatPoint(x,y));
      }      
      Shapes.push_back(s);
   }
   
   fclose(fp);
   return true;
}

void normalizeShapes(int startX, int startY, int W) {
   const GLfloatPoint& p = Shapes[0][0];
   float minX = p.x;
   float maxX = p.x;

   float minY = p.y;
   float maxY = p.y;

   for (const shape &s : Shapes) {
      for (const GLfloatPoint &p : s) {
         minX = min(minX, p.x);
         maxX = max(maxX, p.x);
         minY = min(minY, p.y);
         maxY = max(maxY, p.y);
      }
   }


   float initW = maxX - minX;
   float initH = maxY - minY;

   int H = W * initH / initW;

   for (shape &s : Shapes) {
      for (GLfloatPoint &p : s) {
         p.x = startX + (p.x - minX) / initW * W;
         p.y = startY + (p.y - minY) / initH * H;
         
         p.y = ::H - p.y;
      }
   }

}

inline void setPixel(int x, int y, const RGB& color) {
   if (x < 0 || y < 0) {
      return; 
   }
   if (x >= W || y >= H) {
      return;
   }
   pixels[W *y + x] = color;
}

RGB getPixel(int x, int y) {
   return pixels[W *y + x];
}

void setBackgroundColor(const RGB &color) {
   for (int i = 0; i < W; ++i) {
      for (int j = 0; j < H; ++j) {
         setPixel(i, j, color);
      }
   }
}
void myInit() {
 
   glClearColor(1.0, 1.0, 1.0, 1.0);      // background color = white
   glColor3f(1.0, 0.0, 0.0);              // drawing color    = red
   glClear(GL_COLOR_BUFFER_BIT);
   glPointSize(2);                        // point size       = 1
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void drawHorizonalLine(int left, int right, int y, const RGB& color) {
   for (int i = left; i <= right; ++i) {
      setPixel(i, y, color);
   }
}

const int DIR_UP   = 1;
const int DIR_DOWN = 2;
const int DIR_ALL = DIR_UP | DIR_DOWN;

struct SearchLine {
   int x0, x1;
   int y;
   int dir;
   SearchLine(int x0=0, int x1=0, int y=0, int dir=0)
      : x0(x0)
      , x1(x1)
      , y(y)
      , dir(dir)
   {}
};

void initClickLine(SearchLine& line, int clickX, int clickY, RGB clickColor) {
   int left = clickX;
   while (left - 1 >= 0 && getPixel(left - 1, clickY) == clickColor) {
      left--;
   }
   int right = clickX;
   while (right + 1 < W && getPixel(right + 1, clickY) == clickColor) {
      right++;
   }
   line.x0 = left;
   line.x1 = right;
   line.y = clickY;
   line.dir = DIR_ALL;
}

void ScanNeibLines(int x0, int x1, int y, RGB clickColor, int nxtDir, queue<SearchLine>& q) {
   int curX = x0;
   int nxtX0 = 0;
   int nxtX1 = 0;
   while (curX <= x1) {
      bool isSinglDir = true;
      while (curX <= x1 && getPixel(curX, y) != clickColor) {
         curX++;
      }
      if (curX <= x1 && getPixel(curX, y) == clickColor) {
         nxtX0 = curX;
         while (nxtX0 - 1 >= 0 && getPixel(nxtX0 - 1, y) == clickColor) {
            nxtX0--;
            isSinglDir = false;
         }
      } else {
         break;
      }
      while (curX < W && getPixel(curX, y) == clickColor) {
         curX++;
      }
      nxtX1 = curX - 1;
      if (nxtX1 > x1) {
         isSinglDir = false;
      }
      q.push(SearchLine(nxtX0, nxtX1, y, isSinglDir ? nxtDir : DIR_ALL));
   }
}


void Flood_Fill(int clickX, int clickY) {
   RGB clickColor = getPixel(clickX, clickY);
   if (clickColor == BORDER_COLOR) {
      return;
   }
   RGB fillColor = getFILL_COLOR(clickColor);
   if (fillColor == clickColor) {
      return;
   }
   SearchLine startLine;
   initClickLine(startLine, clickX, clickY, clickColor);
   queue<SearchLine> q;
   q.push(startLine);
   
   while (!q.empty()) {
      SearchLine curLine = q.front(); q.pop();
      drawHorizonalLine(curLine.x0, curLine.x1, curLine.y, fillColor);
      glutPostRedisplay();
      if (curLine.dir & DIR_UP) {
         if (curLine.y - 1 >= 0) {
            ScanNeibLines(curLine.x0, curLine.x1, curLine.y - 1, clickColor, DIR_UP, q);
         }
      }
      if (curLine.dir & DIR_DOWN) {
         if (curLine.y + 1 < H) {
            ScanNeibLines(curLine.x0, curLine.x1, curLine.y + 1, clickColor, DIR_DOWN, q);
         }
      }
   }
}

void myMouse(int button, int state, int x, int y) {
   printf("button = %d; state = %d, x = %d; y = %d\n", button, state, x, y);
   if (state == GLUT_UP) {
      Flood_Fill(x, H - y);
      glutPostRedisplay();
   }
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


void drawShape(const shape &s) {
   for (int i = 0; i < s.size(); ++i) {
      drawSegmentBresenham(s[i], s[(i + 1) % s.size()], [](GLint x, GLint y) {
         setPixel(x, y, BORDER_COLOR);
      });
   }
}

void myDisplay(void) {
  
   glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, pixels);
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
   loadShapesFromFile("data/russia-min-polyline.txt");
   normalizeShapes(10, 10, W - 20);
   setBackgroundColor(BACKGROUND_COLOR);

   for (const shape &s : Shapes) {
      drawShape(s);
   }

   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(W, H);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(PROJECT_NAME);

   myInit();

   glutDisplayFunc(myDisplay);
   glutMouseFunc(myMouse);
   glutKeyboardFunc(myKeyBoard);
   glutReshapeFunc(myReshape);

   glutMainLoop();
   return 0;
}