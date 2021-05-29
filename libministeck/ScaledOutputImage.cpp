#include "ScaledOutputImage.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ColorConverter.h"

std::shared_ptr<cv::Mat> ScaledOutputImage::ScaleImage(const cv::Mat& quantizedImage, const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const
{
    cv::Mat outputImage(quantizedImage.rows * baseplate.GetDecimation(), quantizedImage.cols * baseplate.GetDecimation(), CV_8UC1);
    cv::Mat colormap(256, 1, CV_8UC3,cv::Vec3b(0,128,128));

    // first opscale the index map
    int decimation = baseplate.GetDecimation();
    for(int y=0;y<quantizedImage.rows; y++)
        for(int x=0;x<quantizedImage.cols;x++)
        {
            uint8_t index = quantizedImage.at<cv::Vec2b>(y,x)[0];
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

std::shared_ptr<cv::Mat> ScaledOutputImage::RenderImage(const cv::Mat &quantizedImage, const IBaseplateType &baseplate, const std::vector<Color> &colorVec) const
{
    int decimation = baseplate.GetDecimation();
    cv::Mat colormap(256, 1, CV_8UC3,cv::Vec3b(0,128,128));
    cv::Mat outputImage(quantizedImage.rows * decimation, quantizedImage.cols * decimation, CV_8UC1);
    cv::Mat mask(decimation, decimation, CV_8UC1);
    //tijdelijk genereer even een enkeltje
    for (int y=0;y<decimation;y++)
        for (int x=0;x<decimation;x++)
        {
            mask.at<uint8_t>(x,y) = ((x==0) || (y==0) || (x==decimation-1) || (y==decimation-1)) ? 1:0;
        }
    // voor de rand pixels vervang de index door index+colorVec.size()
    for(int y=0;y<quantizedImage.rows; y++)
        for(int x=0;x<quantizedImage.cols;x++)
        {
            uint8_t index = quantizedImage.at<cv::Vec2b>(y,x)[0];
            for(int decy=0; decy<decimation;decy++)
                for(int decx=0;decx<decimation;decx++)
                {
                    outputImage.at<uint8_t>(y*decimation+decy,x*decimation+decx) = (mask.at<uint8_t>(decx,decy) == 1) ? index+colorVec.size(): index;
                }
        }

    // creer de color lut met ook de rand indexen voor de rand voor lichte kleur maak rand donkerder en een donkere kleur maakhem lichter
    for (size_t i=0;i<colorVec.size();i++)
    {
        colormap.at<cv::Vec3b>(i) = cv::Vec3b(colorVec[i].rgb.r,colorVec[i].rgb.g,colorVec[i].rgb.b);
        auto color = colorVec[i];
        color.lab.l = static_cast<uint8_t>((color.lab.l>128) ? color.lab.l*0.9: (color.lab.l>64) ? color.lab.l*1.2: color.lab.l*1.5);
        color.rgb = ColorConverter().Lab2Rgb(color.lab);
        colormap.at<cv::Vec3b>(i+colorVec.size()) = cv::Vec3b(color.rgb.r,color.rgb.g,color.rgb.b);
    }
    auto  resizedImage = std::make_shared<cv::Mat>();
    cv::applyColorMap(outputImage, *resizedImage, colormap);
    return resizedImage;

}
