#include <gtest/gtest.h>
#include "IColorConverter.h"
#include "libMinisteckBuilder.h"

#include <memory>
class ColorConverterTest: public ::testing::Test
{
public:
   ColorConverterTest( )
   {
       // initialization code here


   }

   void SetUp( )
   {
       // code here will execute just before the test ensues
       m_colorConverter = LibMiniSteckBuilder::CreateIColorConverter();
   }
protected:
   std::unique_ptr<IColorConverter> m_colorConverter;
};

TEST_F (ColorConverterTest, Rgb2Lab)
{
    //
    // notes voor
    // https://www.nixsensor.com/free-color-converter/
    // werkt leuk maar bedenk dat lab voor l is de range 0..100
    // en de ab geld -128..127
    // dus voor l moet je *255/100 doen
    // en de ab +128
    // Dit doet opencv ook intern zodat je maximale range van aan uint8 kan gebruiken
    //
    Rgb color;
    // zwart
    auto lab = m_colorConverter->Rgb2Lab(color);
    EXPECT_EQ(0, lab.l);
    EXPECT_EQ(128, lab.a);
    EXPECT_EQ(128, lab.b);

    color = Rgb(255,255,255);
    // wit
    lab = m_colorConverter->Rgb2Lab(color);
    EXPECT_EQ(255, lab.l);
    EXPECT_EQ(128, lab.a);
    EXPECT_EQ(128, lab.b);

    color = Rgb(255,0,0);
    // rood
    lab = m_colorConverter->Rgb2Lab(color);
    // https://www.nixsensor.com/free-color-converter/   geeft me 138, 208,197
    EXPECT_NEAR(138, lab.l, 2);
    EXPECT_EQ(208, lab.a);
    EXPECT_NEAR(197, lab.b, 2);

    color.r = 0;
    color.g = 255;
    // groen
    lab = m_colorConverter->Rgb2Lab(color);
    // https://www.nixsensor.com/free-color-converter/   geeft me 223, 49,208
    EXPECT_NEAR(223, lab.l, 2);
    EXPECT_NEAR(49, lab.a, 7);
    EXPECT_NEAR(208, lab.b, 3);

    color.g = 0;
    color.b = 255;
    // blauw
    lab = m_colorConverter->Rgb2Lab(color);
    // https://www.nixsensor.com/free-color-converter/   geeft me 75, 196, 16
    EXPECT_NEAR(75, lab.l, 7);
    EXPECT_NEAR(196, lab.a, 11);
    EXPECT_NEAR(16, lab.b, 4);
}

TEST_F (ColorConverterTest, Lab2Rgb)
{
    Lab color;
    // donker blauw
    auto rgb = m_colorConverter->Lab2Rgb(color);
    // https://www.nixsensor.com/free-color-converter/   geeft me 0, 59, 195
    EXPECT_NEAR(0, rgb.r, 0);
    EXPECT_NEAR(59, rgb.g, 5);
    EXPECT_NEAR(195, rgb.b, 1);

    color = Lab(255,255,255);
    // orangje achtig
    // https://www.nixsensor.com/free-color-converter/   geeft me 255, 67, 0
    rgb = m_colorConverter->Lab2Rgb(color);
    EXPECT_NEAR(255, rgb.r, 0);
    EXPECT_NEAR(67, rgb.g, 3);
    EXPECT_NEAR(0, rgb.b, 1);

    color = Lab(255,0,0);
    // licht blauw
    rgb = m_colorConverter->Lab2Rgb(color);
    // https://www.nixsensor.com/free-color-converter/   geeft me 0, 255, 255
    EXPECT_NEAR(0, rgb.r, 0);
    EXPECT_NEAR(255, rgb.g, 0);
    EXPECT_NEAR(255, rgb.b, 0);

    color.l = 0;
    color.a = 255;
    // vette blauw
    rgb = m_colorConverter->Lab2Rgb(color);
    // https://www.nixsensor.com/free-color-converter/   geeft me 0, 0, 196
    EXPECT_NEAR(0, rgb.r, 0);
    EXPECT_NEAR(0, rgb.g, 0);
    EXPECT_NEAR(196, rgb.b, 1);

    color.a = 0;
    color.b = 255;
    // bijna zwart zeer donker bruin
    rgb = m_colorConverter->Lab2Rgb(color);
    // https://www.nixsensor.com/free-color-converter/   geeft me 0, 47, 0
    EXPECT_NEAR(0, rgb.r, 0);
    EXPECT_NEAR(47, rgb.g, 2);
    EXPECT_NEAR(0, rgb.b, 0);
}
