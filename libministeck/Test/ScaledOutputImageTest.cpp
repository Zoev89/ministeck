#include "gtest/gtest.h"
#include "IScaledOutputImage.h"
#include "libMinisteckBuilder.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ScaledOutputImageTest: public ::testing::Test
{
public:
   ScaledOutputImageTest( )
   {
       // initialization code here
   }

   void SetUp( )
   {
       // code here will execute just before the test ensues
       m_scaledOutputImage = LibMiniSteckBuilder::CreateIScaledOutputImage();
   }
protected:
   std::unique_ptr<IScaledOutputImage> m_scaledOutputImage;
};

TEST_F (ScaledOutputImageTest, emptyCreation)
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

    cv::Mat inputImage(baseplate.baseplateHeight, baseplate.baseplateWidth, CV_8UC1);
    for(int y=0;y<baseplate.baseplateHeight;y++)
        for(int x=0;x<baseplate.baseplateWidth;x++)
        {
            inputImage.at<uint8_t>(y,x)=(x<baseplate.baseplateWidth/2) ? 0:1;
        }
    auto retImg = m_scaledOutputImage->ScaleImage(inputImage, baseplate, colorVec);

    for(int y=0;y<baseplate.imageHeight;y++)
        for(int x=0;x<baseplate.imageWidth;x++)
        {
            EXPECT_EQ((x<baseplate.imageWidth/2)? 0:255,retImg->at<cv::Vec3b>(y,x)(0)) << y<< " " <<x;
        }

    //cv::imshow("test", *retImg);
    //int k = cv::waitKey(0);

}

