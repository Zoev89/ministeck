#include <gtest/gtest.h>
#include "IColors.h"
#include "libMinisteckBuilder.h"

#include <memory>
class ColorsTest: public ::testing::Test
{
public:
   ColorsTest( )
   {
       // initialization code here


   }

   void SetUp( )
   {
       // code here will execute just before the test ensues
       m_colors = LibMiniSteckBuilder::CreateIColors();
   }
protected:
   std::unique_ptr<IColors> m_colors;
};

TEST_F (ColorsTest, UnitTest1)
{
    Rgb color;
    auto colors = m_colors->GetColors();
    EXPECT_EQ(2, colors.size());
}




