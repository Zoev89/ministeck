#pragma once
#include "gmock/gmock.h"
#include "IColorConverter.h"

class IColorConverterMock: public IColorConverter
{
public:
    MOCK_METHOD( Lab, Rgb2Lab, (Rgb rgb), (const override));
    MOCK_METHOD( Rgb, Lab2Rgb, (Lab lab), (const override));
};
