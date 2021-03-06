#pragma once
#include "IScaledOutputImage.h"

class ScaledOutputImage : public IScaledOutputImage
{
public:
    ScaledOutputImage() = default;
    virtual ~ScaledOutputImage() = default;
    virtual std::shared_ptr<cv::Mat> ScaleImage(const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const override;
    virtual std::shared_ptr<cv::Mat> RenderImage(const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec, const std::vector<cv::Mat>& randVormen) const override;

};


