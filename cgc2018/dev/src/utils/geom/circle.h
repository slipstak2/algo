#pragma once
#include <functional>
#include "point.h"


void drawCircleBresenham(GLintPoint center, GLint R, std::function<void(GLint, GLint)> drawDot = nullptr);