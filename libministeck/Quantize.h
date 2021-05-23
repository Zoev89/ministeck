#pragma once
#include "IQuantize.h"

class Quantize : public IQuantize
{
public:
    Quantize()= default;
    virtual ~Quantize() = default;

    cv::Mat QuantizeImage(const cv::Mat& inputImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const override;

};


