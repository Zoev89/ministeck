#include "gtest/gtest.h"
#include "IRandVorm.h"
#include "libMinisteckBuilder.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class RandVormTest: public ::testing::Test
{
public:
   RandVormTest( )
   {
       // initialization code here
   }

   void SetUp( )
   {
       // code here will execute just before the test ensues
       m_randVorm = LibMiniSteckBuilder::CreateIRandVorm();
   }
protected:
   std::unique_ptr<IRandVorm> m_randVorm;
};

TEST_F (RandVormTest, CheckDeRanden)
{
    auto vec = m_randVorm->GetRandVormen(4);
    ASSERT_EQ(16, vec.size());
    std::array<uint8_t,16>data = { 0, 0, 0, 0,
                                  0, 0, 0, 0,
                                  0, 0, 0, 0,
                                  0, 0, 0, 0};
    auto vorm = cv::Mat(4, 4, CV_8UC1, data.data());
    EXPECT_EQ(0.0, cv::norm(vorm,vec[0],cv::NORM_L1)); // calc de som of absolute differences

    // maak gebruik van het feit dat het cv::Mat object naar data staat te wijzen
    // v1
    data = { 1, 1, 1, 1,
             1, 0, 0, 1,
             1, 0, 0, 1,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[1],cv::NORM_L1));

    // v2
    data = { 1, 1, 1, 1,
             1, 0, 0, 0,
             1, 0, 0, 0,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[2],cv::NORM_L1));

    // v3
    data = { 1, 1, 1, 1,
             0, 0, 0, 1,
             0, 0, 0, 1,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[3],cv::NORM_L1));

    // v4
    data = { 1, 1, 1, 1,
             1, 0, 0, 1,
             1, 0, 0, 1,
             1, 0, 0, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[4],cv::NORM_L1));

    // v5
    data = { 1, 0, 0, 1,
             1, 0, 0, 1,
             1, 0, 0, 1,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[5],cv::NORM_L1));

    // v6
    data = { 1, 1, 1, 1,
             0, 0, 0, 0,
             0, 0, 0, 0,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[6],cv::NORM_L1));

    // v7
    data = { 1, 0, 0, 1,
             1, 0, 0, 1,
             1, 0, 0, 1,
             1, 0, 0, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[7],cv::NORM_L1));

    // v8
    data = { 1, 1, 1, 1,
             1, 0, 0, 0,
             1, 0, 0, 0,
             1, 0, 0, 0};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[8],cv::NORM_L1));

    // v9
    data = { 1, 1, 1, 1,
             0, 0, 0, 1,
             0, 0, 0, 1,
             0, 0, 0, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[9],cv::NORM_L1));

    // v10
    data = { 1, 0, 0, 0,
             1, 0, 0, 0,
             1, 0, 0, 0,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[10],cv::NORM_L1));

    // v11
    data = { 0, 0, 0, 1,
             0, 0, 0, 1,
             0, 0, 0, 1,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[11],cv::NORM_L1));

    // v12
    data = { 1, 0, 0, 1,
             1, 0, 0, 0,
             1, 0, 0, 0,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[12],cv::NORM_L1));

    // v13
    data = { 1, 1, 1, 1,
             1, 0, 0, 0,
             1, 0, 0, 0,
             1, 0, 0, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[13],cv::NORM_L1));

    // v14
    data = { 1, 1, 1, 1,
             0, 0, 0, 1,
             0, 0, 0, 1,
             1, 0, 0, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[14],cv::NORM_L1));

    // v15
    data = { 1, 0, 0, 1,
             0, 0, 0, 1,
             0, 0, 0, 1,
             1, 1, 1, 1};
    EXPECT_EQ(0.0, cv::norm(vorm,vec[15],cv::NORM_L1));

}

