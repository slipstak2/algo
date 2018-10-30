#pragma once

#include <functional>
#include "point.h"

void drawSegmentBresenham(GLintPoint p1, GLintPoint p2, std::function<void(GLint, GLint)> drawDot = nullptr);