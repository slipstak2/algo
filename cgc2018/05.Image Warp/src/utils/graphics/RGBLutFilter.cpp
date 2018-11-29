#pragma once

#include <cstring>
#include <cmath>

#include "RGBLutFilter.h"
#include "common.h"

RGBLutFilterBase::RGBLutFilterBase() {
   memset(LUT, 0, sizeof(LUT));
}

void RGBLutFilterBase::apply(RGB& pixel) {
   pixel.r = LUT[pixel.r];
   pixel.g = LUT[pixel.g];
   pixel.b = LUT[pixel.b];
}


RGBLutFilterNegative::RGBLutFilterNegative() : RGBLutFilterBase() {
   for (int i = 0; i <= 255; ++i) {
      LUT[i] = 255 - i;
   }
}

RGBLutFilterBrightness::RGBLutFilterBrightness(int deltaBrightness) : RGBLutFilterBase() {
   for (int i = 0; i <= 255; ++i) {
      LUT[i] = clamp(i + deltaBrightness, 0, 255);
   }
}

RGBLutFilterContrast::RGBLutFilterContrast(int deltaContrast) : RGBLutFilterBase() {
   for (int i = 0; i <= 255; ++i) {
      double contrast = deltaContrast;
      double factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
      LUT[i] = clamp(factor * (i  - 128) + 128, 0, 255);
   }
}

RGBLutFilterGammaCorrection::RGBLutFilterGammaCorrection(double gamma) : RGBLutFilterBase() {
   for (int i = 0; i <= 255; ++i) {
      LUT[i] = 255 * pow(i / 255.0, 1 / gamma);
   }
}

