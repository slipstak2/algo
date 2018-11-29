#pragma once

#include "RGBpixel.h"

class RGBLutFilterBase {
public:
   RGBLutFilterBase();
   virtual ~RGBLutFilterBase(){};
   void apply(RGB& pixel);
protected:
   int LUT[256];
};

class RGBLutFilterNegative: public RGBLutFilterBase
{
public:
   RGBLutFilterNegative();
};


class RGBLutFilterBrightness: public RGBLutFilterBase
{
public:
   RGBLutFilterBrightness(int deltaBrightness);  // deltaBrightness in [-255, 255]
};


class RGBLutFilterContrast: public RGBLutFilterBase
{
public:
   RGBLutFilterContrast(int deltaContrast);  // deltaContrast in [-255, 255]
};

class RGBLutFilterGammaCorrection: public RGBLutFilterBase
{
public:
   RGBLutFilterGammaCorrection(double gamma);
};
