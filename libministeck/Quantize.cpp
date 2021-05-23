#include "Quantize.h"
#include <climits>
#include <cmath>

cv::Mat Quantize::QuantizeImage(const cv::Mat& inputImage,  const IBaseplateType &baseplate, const std::vector<Color>& colorVec) const
{
    int decimation = baseplate.GetDecimation();
    cv::Scalar_<uint8_t> scaler = 255;
    auto retImage = cv::Mat(baseplate.baseplateHeight, baseplate.baseplateWidth, CV_8UC1, scaler);
    for (int gatY=0; gatY < baseplate.baseplateHeight; gatY++)
    {
        for (int gatX=0; gatX < baseplate.baseplateWidth; gatX++)
        {
            std::vector<unsigned> distances(colorVec.size(),0);
            for(int y=0;y<decimation;y++)
                for(int x=0;x<decimation;x++)
                {
                    auto pixel =inputImage.at<cv::Vec3b>(gatY*decimation+baseplate.imageOffsetY,gatX*decimation+baseplate.imageOffsetX);
                    for (unsigned i=0;i<colorVec.size();i++)
                    {
                        int d = distances[i];
                        d += std::pow(pixel[0] - colorVec[i].lab.l, 2);
                        d += std::pow(pixel[1] - colorVec[i].lab.a, 2);
                        d += std::pow(pixel[2] - colorVec[i].lab.b, 2);
                        distances[i] = d;
                    }
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
            retImage.at<uint8_t>(gatY,gatX)= index;
        }
    }
    return retImage;
}
