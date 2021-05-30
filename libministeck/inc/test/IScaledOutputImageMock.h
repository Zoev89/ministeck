#pragma once

#include "gmock/gmock.h"
#include "IScaledOutputImage.h"


class IScaledOutputImageMock: public IScaledOutputImage
{
public:
    MOCK_METHOD( std::shared_ptr<cv::Mat>, ScaleImage, (const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec), (const override));
    MOCK_METHOD( std::shared_ptr<cv::Mat>, RenderImage, (const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec, const std::vector<cv::Mat>& randVormen), (const override));

};
