#pragma once

#include "gmock/gmock.h"
#include "IColors.h"

class IColorsMock: public IColors
{
public:
    MOCK_METHOD(std::vector<Color>, GetColors, (), (override));
};

