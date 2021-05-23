#include "ScaledOutputImage.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


std::shared_ptr<cv::Mat> ScaledOutputImage::ScaleImage(const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const
{
    cv::Mat outputImage(quantizedImage.rows * baseplate.GetDecimation(), quantizedImage.cols * baseplate.GetDecimation(), CV_8UC1);
    cv::Mat colormap(256, 1, CV_8UC3,cv::Vec3b(0,128,128));

    // first opscale the index map
    int decimation = baseplate.GetDecimation();
    for(int y=0;y<quantizedImage.rows; y++)
        for(int x=0;x<quantizedImage.cols;x++)
        {
            uint8_t index = quantizedImage.at<uint8_t>(y,x);
            for(int decy=0; decy<decimation;decy++)
                for(int decx=0;decx<decimation;decx++)
                {
                    outputImage.at<uint8_t>(y*decimation+decy,x*decimation+decx) = index;
                }
        }



    for (size_t i=0;i<colorVec.size();i++)
    {
        colormap.at<cv::Vec3b>(i) = cv::Vec3b(colorVec[i].rgb.r,colorVec[i].rgb.g,colorVec[i].rgb.b);
    }
    auto  resizedImage = std::make_shared<cv::Mat>();
    cv::applyColorMap(outputImage, *resizedImage, colormap);
    return resizedImage;
}
