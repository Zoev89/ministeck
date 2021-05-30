#pragma once

#include <opencv2/core.hpp>
#include <vector>
#include "IColorTypes.h"
#include "IBaseplateType.h"
#include <memory>
class IScaledOutputImage
{
public:
    virtual ~IScaledOutputImage() = default;
    virtual std::shared_ptr<cv::Mat> ScaleImage(const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const = 0;
    virtual std::shared_ptr<cv::Mat> RenderImage(const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec, const std::vector<cv::Mat>& randVormen) const = 0;
protected:
    IScaledOutputImage() = default;
};
