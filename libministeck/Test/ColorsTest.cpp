#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IColors.h"
#include "libMinisteckBuilder.h"
#include "test/IColorConverterMock.h"

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
       auto colorConverter = std::make_unique<::testing::StrictMock<IColorConverterMock>>();
       m_colorConverter = colorConverter.get();
       EXPECT_CALL(*m_colorConverter, Rgb2Lab(testing::_)).WillRepeatedly(testing::Return(Lab(0,0,0)));
       m_colors = LibMiniSteckBuilder::CreateIColorsDependencyInjection(std::move(colorConverter));
   }
protected:
   std::unique_ptr<IColors> m_colors;
   IColorConverterMock* m_colorConverter;

};

TEST_F (ColorsTest, UnitTest1)
{
    auto colors = m_colors->GetColors();
    EXPECT_EQ(2, colors.size());
}




