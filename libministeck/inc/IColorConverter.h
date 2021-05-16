#pragma once

#include "IColorTypes.h"

class IColorConverter
{
public:
    virtual ~IColorConverter() = default;
    virtual Lab Rgb2Lab(Rgb rgb) const = 0;
    virtual Rgb Lab2Rgb(Lab lab) const = 0;
protected:
    IColorConverter() = default;
};
