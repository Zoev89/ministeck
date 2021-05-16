#pragma once

#include <vector>
#include <string>
#include "IColorTypes.h"


class IColors
{
public:
    virtual ~IColors() = default;
    virtual std::vector<Color> GetColors() = 0;
protected:
    IColors() = default;
};


class IColorConverter
{
public:
    virtual ~IColorConverter() = default;
    virtual Lab Rgb2Lab(Rgb rgb) = 0;
    virtual Rgb Lab2Rgb(Lab lab) = 0;
protected:
    IColorConverter() = default;

};
