#include "gtest/gtest.h"
#include "IQuantize.h"
#include "libMinisteckBuilder.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class QuantizeTest: public ::testing::Test
{
public:
   QuantizeTest( )
   {
       // initialization code here
   }

   void SetUp( )
   {
       // code here will execute just before the test ensues
       m_quantize = LibMiniSteckBuilder::CreateIQuantize();
   }
protected:
   std::unique_ptr<IQuantize> m_quantize;
};

TEST_F (QuantizeTest, ConvertToBlackAndWhite)
{
    std::vector<Color> colorVec;
    Color col;
    col.lab = Lab(0,128,128); // zwart
    col.rgb = Rgb(0,0,0); // zwart
    colorVec.push_back(col);
    col.lab = Lab(255,128,128); // wit
    col.rgb = Rgb(255,255,255); // wit
    colorVec.push_back(col);
    int decimation = 4;
    int width = 32*decimation;
    int height =16*decimation;
    IBaseplateType baseplate;
    baseplate.imageWidth = width;
    baseplate.imageHeight = height;
    baseplate.baseplateWidth = width/decimation;
    baseplate.baseplateHeight = height/decimation;

    cv::Scalar scaler(100,128,128);
    cv::Mat inputImage(height, width, CV_8UC3, scaler);
    for(int y=0;y<height;y++)
        for(int x=0;x<width;x++)
        {
            inputImage.at<cv::Vec3b>(y,x)=cv::Vec3b((x<width/2) ? 100:200,128,128);
        }
    auto retImg = m_quantize->QuantizeImage(inputImage, baseplate, colorVec);

    for(int y=0;y<baseplate.baseplateHeight;y++)
        for(int x=0;x<baseplate.baseplateWidth;x++)
        {
            EXPECT_EQ((x<baseplate.baseplateWidth/2)? 0:1,retImg.at<uint8_t>(y,x)) << y<< " " <<x;
        }

    //cv::imshow("test", resizedImage);
    //int k = cv::waitKey(0);
}

