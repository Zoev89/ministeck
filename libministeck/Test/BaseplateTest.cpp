#include "gtest/gtest.h"
#include "IBaseplateType.h"

class BaseplateTest: public ::testing::Test
{
public:
   BaseplateTest( )
   {
       // initialization code here


   }

   void SetUp( )
   {
       // code here will execute just before the test ensues
       m_baseplate = std::make_unique<IBaseplateType>();
   }
protected:
   std::unique_ptr<IBaseplateType> m_baseplate;
};

TEST_F (BaseplateTest, emptyCreation)
{
    EXPECT_EQ(1, m_baseplate->GetDecimation());
}

TEST_F (BaseplateTest, Decimation2)
{
    m_baseplate->baseplateWidth = 10;
    m_baseplate->baseplateHeight = 10;
    m_baseplate->imageWidth = 20; // decimation 2 by width
    m_baseplate->imageHeight = 200;
    EXPECT_EQ(2, m_baseplate->GetDecimation());

    m_baseplate->imageWidth = 200;
    m_baseplate->imageHeight = 20; // decimation 2 by height
    EXPECT_EQ(2, m_baseplate->GetDecimation());

    m_baseplate->imageWidth = 20;
    m_baseplate->imageOffsetX = 1; // little offset and decimation should be 1
    EXPECT_EQ(1, m_baseplate->GetDecimation());

    m_baseplate->imageOffsetX = 0;
    m_baseplate->imageOffsetY = 2;
    m_baseplate->imageHeight = 22; // decimation 2 by height
    EXPECT_EQ(2, m_baseplate->GetDecimation());

}
