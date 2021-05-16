#pragma once
#include "IColorConverter.h"

class ColorConverter : public IColorConverter
{
public:
    ColorConverter();
    virtual Lab Rgb2Lab(Rgb rgb) const override;
    virtual Rgb Lab2Rgb(Lab lab) const override;
};

