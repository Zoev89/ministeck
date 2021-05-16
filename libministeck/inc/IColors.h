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

