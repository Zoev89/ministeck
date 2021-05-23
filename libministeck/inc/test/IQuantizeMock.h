#pragma once

#include "gmock/gmock.h"
#include "IQuantize.h"


class IQuantizeMock: public IQuantize
{
public:
    MOCK_METHOD( cv::Mat, QuantizeImage, (const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec), (const override));
};
