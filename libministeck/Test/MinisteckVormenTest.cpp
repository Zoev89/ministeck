#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <IMinisteckVormen.h>

class MinisteckVormenTest: public ::testing::Test
{
public:
   MinisteckVormenTest( )
   {
       // initialization code here
   }

   void SetUp( )
   {
       // code here will execute just before the test ensues

   }
};

TEST_F (MinisteckVormenTest, GTestPrintVorm)
{
    EXPECT_EQ("Enkeltje", testing::PrintToString(Vorm::Enkeltje)) << Vorm::Enkeltje;
    EXPECT_EQ("Tweetje", testing::PrintToString(Vorm::Tweetje)) << Vorm::Tweetje;
    EXPECT_EQ("Drietje", testing::PrintToString(Vorm::Drietje)) << Vorm::Drietje;
    EXPECT_EQ("Vierkant", testing::PrintToString(Vorm::Vierkant)) << Vorm::Vierkant;
    EXPECT_EQ("Hoekje", testing::PrintToString(Vorm::Hoekje)) << Vorm::Hoekje;
    // check ook of we out off enum kunnen printen zonder elende
    Vorm vorm(static_cast<Vorm>(5));
    EXPECT_EQ("Unknown 5", testing::PrintToString(vorm)) <<vorm;
}

