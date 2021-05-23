#pragma once
#include <opencv2/core.hpp>
#include <vector>
#include "IColorTypes.h"
#include "IBaseplateType.h"

class IQuantize
{
public:
    virtual ~IQuantize() = default;
    virtual cv::Mat QuantizeImage(const cv::Mat& inputImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const = 0;
protected:
    IQuantize() = default;
};
