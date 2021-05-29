#include "Quantize.h"
#include <climits>
#include <cmath>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// returns a 2 component image where comp[0]=the color index and comp[1]=the shape index which initialized to 0
cv::Mat Quantize::QuantizeImage(const cv::Mat& inputImage,  const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const
{
    // first roi the image then downscale it and the do pixel matching
    cv::Rect roi(baseplate.imageOffsetX, baseplate.imageOffsetY, baseplate.baseplateWidth*baseplate.GetDecimation(), baseplate.baseplateHeight*baseplate.GetDecimation());
    //Create the cv::Mat with the ROI you need, where "image" is the cv::Mat you want to extract the ROI from
    cv::Mat image_roi = inputImage(roi);
    cv::Mat scaleImg;
    cv::resize(image_roi,scaleImg,cv::Size(baseplate.baseplateWidth,baseplate.baseplateHeight));

    auto retImage = cv::Mat(baseplate.baseplateHeight, baseplate.baseplateWidth, CV_8UC2);
    for (int gatY=0; gatY < baseplate.baseplateHeight; gatY++)
    {
        for (int gatX=0; gatX < baseplate.baseplateWidth; gatX++)
        {
            std::vector<unsigned> distances(colorVec.size(),0);
            auto pixel =scaleImg.at<cv::Vec3b>(gatY,gatX);
            for (unsigned i=0;i<colorVec.size();i++)
            {
                int d = distances[i];
                d += std::pow(pixel[0] - colorVec[i].lab.l, 2);
                d += std::pow(pixel[1] - colorVec[i].lab.a, 2);
                d += std::pow(pixel[2] - colorVec[i].lab.b, 2);
                distances[i] = d;
            }
            unsigned min=UINT_MAX;
            unsigned index = 0;
            for (unsigned i=0;i<distances.size();i++)
            {
                if (distances[i] < min)
                {
                    min = distances[i];
                    index = i;
                }
            }
            retImage.at<cv::Vec2b>(gatY,gatX)= cv::Vec2b(index,0);
        }
    }
    return retImage;
}
