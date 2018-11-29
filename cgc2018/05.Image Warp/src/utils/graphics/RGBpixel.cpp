#include "RGBpixel.h"

RGB BLACK = {0, 0, 0};
RGB WHITE = {255, 255, 255};

bool operator == (const RGB& a, const RGB& b) {
   return memcmp(&a, &b, sizeof(RGB)) == 0;
}

bool operator != (const RGB& a, const RGB& b) {
   return !(a == b);
}
