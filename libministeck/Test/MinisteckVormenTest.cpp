#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IMinisteckVormen.h"
#include "libMinisteckBuilder.h"
#include "../RandVorm.h" // ik heb deze echt nodig om snel de randvorm vector te hebben
#include "IBaseplateType.h"

class MinisteckVormenTest: public ::testing::Test
{
public:
   MinisteckVormenTest( )
   {
       // initialization code here
   }

   void SetUp( )
   {
       m_ministeckVormen = LibMiniSteckBuilder::CreateIMinisteckVormen();
   }

   void CheckMatch(const MinisteckMatch &match, int offsetY, int offsetX, int randVormIndex, int lineNumber)
   {
       EXPECT_EQ(offsetX, match.offsetX) << "AT LINE "<<lineNumber;
       EXPECT_EQ(offsetY, match.offsetY) << "AT LINE "<<lineNumber;
       EXPECT_EQ(randVormIndex, match.randVormIndex) << "AT LINE "<<lineNumber;
   }

protected:
   std::unique_ptr<IMinisteckVormen> m_ministeckVormen;
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

TEST_F(MinisteckVormenTest, CheckMachListEmpty)
{
    // after creation the matchlist should be empty
    auto list = m_ministeckVormen->GetMatchTable();
    EXPECT_TRUE(list.empty());
}

TEST_F(MinisteckVormenTest, FoutInRandVorm)
{
    EXPECT_THROW(m_ministeckVormen->CreateMatchTable(std::vector<Color>(),std::vector<cv::Mat>()), std::invalid_argument);
}

TEST_F(MinisteckVormenTest, CreatMatchTable)
{
    std::vector<Color> colors;
    Color color;
    color.naam = "Zwartig";
    color.lab.l = 100;
    color.lab.a = 128;
    color.lab.b = 128;
    colors.emplace_back(color);
    color.naam = "Wittig";
    color.lab.l = 200;
    color.lab.a = 128;
    color.lab.b = 128;
    colors.emplace_back(color);

    auto randVorm = LibMiniSteckBuilder::CreateIRandVorm();

    auto  randVormen = randVorm->GetRandVormen(3);

    m_ministeckVormen->CreateMatchTable(colors,randVormen);
    auto matchTable = m_ministeckVormen->GetMatchTable();
    ASSERT_EQ(2,matchTable.size());  // heb 2 kleuren gedefineerd
    EXPECT_EQ("Zwartig", matchTable[0].color.naam);
    EXPECT_EQ("Wittig", matchTable[1].color.naam);
    ASSERT_EQ(10, matchTable[0].matchVormen.size());
    EXPECT_EQ(Vorm::Enkeltje, matchTable[0].matchVormen[0].vorm);
    ASSERT_EQ(1, matchTable[0].matchVormen[0].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[0].eenEnkeleOrientatie[0], 0, 0, 1, __LINE__);
    ASSERT_EQ(2, matchTable[0].matchVormen[0].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(1,0), matchTable[0].matchVormen[0].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(0,1), matchTable[0].matchVormen[0].enkeltjesReductie[1]);
    std::array<uint8_t, 3*9> inp =
    {
        110,128,128 , 110,128,128 , 110,128,128,
        110,128,128 , 100,128,128 , 110,128,128,
        110,128,128 , 110,128,128 , 110,128,128
    };
    auto image = cv::Mat(3,3,CV_8UC3, inp.data());
    EXPECT_EQ(0.0, cv::norm(image,matchTable[0].matchVormen[0].eenEnkeleOrientatie[0].match,cv::NORM_L1));


    // even de ander kleur testen
    EXPECT_EQ(Vorm::Enkeltje, matchTable[1].matchVormen[0].vorm);
    ASSERT_EQ(1,matchTable[1].matchVormen[0].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[1].matchVormen[0].eenEnkeleOrientatie[0], 0, 0, 1, __LINE__);
    ASSERT_EQ(2, matchTable[1].matchVormen[0].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(1,0), matchTable[1].matchVormen[0].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(0,1), matchTable[1].matchVormen[0].enkeltjesReductie[1]);
    inp =
    {
        180,128,128 , 180,128,128 , 180,128,128,
        180,128,128 , 200,128,128 , 180,128,128,
        180,128,128 , 180,128,128 , 180,128,128
    };
    EXPECT_EQ(0.0, cv::norm(image,matchTable[1].matchVormen[0].eenEnkeleOrientatie[0].match,cv::NORM_L1));

    // nu de rest op 1 kleur
    // tweetje horizontaal
    EXPECT_EQ(Vorm::Tweetje, matchTable[0].matchVormen[1].vorm);
    ASSERT_EQ(2,matchTable[0].matchVormen[1].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[1].eenEnkeleOrientatie[0], 0, 0, 2, __LINE__);
    CheckMatch(matchTable[0].matchVormen[1].eenEnkeleOrientatie[1], 0, 1, 3, __LINE__);
    ASSERT_EQ(3, matchTable[1].matchVormen[1].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(2,0), matchTable[0].matchVormen[1].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(0,1), matchTable[0].matchVormen[1].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(1,1), matchTable[0].matchVormen[1].enkeltjesReductie[2]);

    // tweetje verticaal
    EXPECT_EQ(Vorm::Tweetje, matchTable[0].matchVormen[2].vorm);
    ASSERT_EQ(2,matchTable[0].matchVormen[2].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[2].eenEnkeleOrientatie[0], 0, 0, 4, __LINE__);
    CheckMatch(matchTable[0].matchVormen[2].eenEnkeleOrientatie[1], 1, 0, 5, __LINE__);
    ASSERT_EQ(4, matchTable[1].matchVormen[2].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(1,0), matchTable[0].matchVormen[2].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(-1,1), matchTable[0].matchVormen[2].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(1,1), matchTable[0].matchVormen[2].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(0,2), matchTable[0].matchVormen[2].enkeltjesReductie[3]);

    // drietje horizontaal
    EXPECT_EQ(Vorm::Drietje, matchTable[0].matchVormen[3].vorm);
    ASSERT_EQ(3,matchTable[0].matchVormen[3].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[3].eenEnkeleOrientatie[0], 0, 0, 2, __LINE__);
    CheckMatch(matchTable[0].matchVormen[3].eenEnkeleOrientatie[1], 0, 1, 6, __LINE__);
    CheckMatch(matchTable[0].matchVormen[3].eenEnkeleOrientatie[2], 0, 2, 3, __LINE__);
    ASSERT_EQ(4, matchTable[1].matchVormen[3].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(3,0), matchTable[0].matchVormen[3].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(0,1), matchTable[0].matchVormen[3].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(1,1), matchTable[0].matchVormen[3].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(2,1), matchTable[0].matchVormen[3].enkeltjesReductie[3]);

    // drietje verticaal
    EXPECT_EQ(Vorm::Drietje, matchTable[0].matchVormen[4].vorm);
    ASSERT_EQ(3,matchTable[0].matchVormen[4].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[4].eenEnkeleOrientatie[0], 0, 0, 4, __LINE__);
    CheckMatch(matchTable[0].matchVormen[4].eenEnkeleOrientatie[1], 1, 0, 7, __LINE__);
    CheckMatch(matchTable[0].matchVormen[4].eenEnkeleOrientatie[2], 2, 0, 5, __LINE__);
    ASSERT_EQ(6, matchTable[1].matchVormen[4].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(1,0), matchTable[0].matchVormen[4].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(-1,1), matchTable[0].matchVormen[4].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(1,1), matchTable[0].matchVormen[4].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(-1,2), matchTable[0].matchVormen[4].enkeltjesReductie[3]);
    EXPECT_EQ(cv::Point(1,2), matchTable[0].matchVormen[4].enkeltjesReductie[4]);
    EXPECT_EQ(cv::Point(0,3), matchTable[0].matchVormen[4].enkeltjesReductie[5]);

    // viertje
    EXPECT_EQ(Vorm::Vierkant, matchTable[0].matchVormen[5].vorm);
    ASSERT_EQ(4,matchTable[0].matchVormen[5].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[5].eenEnkeleOrientatie[0], 0, 0,  8, __LINE__);
    CheckMatch(matchTable[0].matchVormen[5].eenEnkeleOrientatie[1], 0, 1,  9, __LINE__);
    CheckMatch(matchTable[0].matchVormen[5].eenEnkeleOrientatie[2], 1, 0, 10, __LINE__);
    CheckMatch(matchTable[0].matchVormen[5].eenEnkeleOrientatie[3], 1, 1, 11, __LINE__);
    ASSERT_EQ(5, matchTable[1].matchVormen[5].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(2,0), matchTable[0].matchVormen[5].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(-1,1), matchTable[0].matchVormen[5].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(2,1), matchTable[0].matchVormen[5].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(0,2), matchTable[0].matchVormen[5].enkeltjesReductie[3]);
    EXPECT_EQ(cv::Point(1,2), matchTable[0].matchVormen[5].enkeltjesReductie[4]);

    // hoekje
    EXPECT_EQ(Vorm::Hoekje, matchTable[0].matchVormen[6].vorm);
    ASSERT_EQ(3,matchTable[0].matchVormen[6].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[6].eenEnkeleOrientatie[0], 0, 0,  4, __LINE__);
    CheckMatch(matchTable[0].matchVormen[6].eenEnkeleOrientatie[1], 1, 0, 12, __LINE__);
    CheckMatch(matchTable[0].matchVormen[6].eenEnkeleOrientatie[2], 1, 1,  3, __LINE__);
    ASSERT_EQ(5, matchTable[1].matchVormen[6].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(1,0), matchTable[0].matchVormen[6].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(-1,1), matchTable[0].matchVormen[6].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(2,1), matchTable[0].matchVormen[6].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(0,2), matchTable[0].matchVormen[6].enkeltjesReductie[3]);
    EXPECT_EQ(cv::Point(1,2), matchTable[0].matchVormen[6].enkeltjesReductie[4]);

    EXPECT_EQ(Vorm::Hoekje, matchTable[0].matchVormen[7].vorm);
    ASSERT_EQ(3,matchTable[0].matchVormen[7].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[7].eenEnkeleOrientatie[0], 0, 0, 13, __LINE__);
    CheckMatch(matchTable[0].matchVormen[7].eenEnkeleOrientatie[1], 0, 1,  3, __LINE__);
    CheckMatch(matchTable[0].matchVormen[7].eenEnkeleOrientatie[2], 1, 0,  5, __LINE__);
    ASSERT_EQ(4, matchTable[1].matchVormen[7].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(2,0), matchTable[0].matchVormen[7].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(-1,1), matchTable[0].matchVormen[7].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(1,1), matchTable[0].matchVormen[7].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(0,2), matchTable[0].matchVormen[7].enkeltjesReductie[3]);

    EXPECT_EQ(Vorm::Hoekje, matchTable[0].matchVormen[8].vorm);
    ASSERT_EQ(3,matchTable[0].matchVormen[8].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[8].eenEnkeleOrientatie[0], 0, 0,  2, __LINE__);
    CheckMatch(matchTable[0].matchVormen[8].eenEnkeleOrientatie[1], 0, 1, 14, __LINE__);
    CheckMatch(matchTable[0].matchVormen[8].eenEnkeleOrientatie[2], 1, 1,  5, __LINE__);
    ASSERT_EQ(4, matchTable[1].matchVormen[8].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(2,0), matchTable[0].matchVormen[8].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(0,1), matchTable[0].matchVormen[8].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(2,1), matchTable[0].matchVormen[8].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(1,2), matchTable[0].matchVormen[8].enkeltjesReductie[3]);

    EXPECT_EQ(Vorm::Hoekje, matchTable[0].matchVormen[9].vorm);
    ASSERT_EQ(3,matchTable[0].matchVormen[9].eenEnkeleOrientatie.size());
    CheckMatch(matchTable[0].matchVormen[9].eenEnkeleOrientatie[0], 0, 0,  4, __LINE__);
    CheckMatch(matchTable[0].matchVormen[9].eenEnkeleOrientatie[1], 1, 0, 15, __LINE__);
    CheckMatch(matchTable[0].matchVormen[9].eenEnkeleOrientatie[2], 1,-1,  2, __LINE__);
    ASSERT_EQ(5, matchTable[1].matchVormen[9].enkeltjesReductie.size());
    EXPECT_EQ(cv::Point(1,0), matchTable[0].matchVormen[9].enkeltjesReductie[0]);
    EXPECT_EQ(cv::Point(-2,1), matchTable[0].matchVormen[9].enkeltjesReductie[1]);
    EXPECT_EQ(cv::Point(1,1), matchTable[0].matchVormen[9].enkeltjesReductie[2]);
    EXPECT_EQ(cv::Point(-1,2), matchTable[0].matchVormen[9].enkeltjesReductie[3]);
    EXPECT_EQ(cv::Point(0,2), matchTable[0].matchVormen[9].enkeltjesReductie[4]);

}


TEST_F(MinisteckVormenTest, CalcParts)
{
    std::vector<Color> colorVec;
    Color col;
    col.lab = Lab(30,128,128); // zwart
    col.rgb = Rgb(0,0,0); // zwart
    colorVec.push_back(col);
    col.lab = Lab(220,128,128); // wit
    col.rgb = Rgb(255,255,255); // wit
    colorVec.push_back(col);
    int decimation = 4;
    int width = 15*decimation;
    int height =7*decimation;
    IBaseplateType baseplate;
    baseplate.imageWidth = width;
    baseplate.imageHeight = height;
    baseplate.baseplateWidth = width/decimation;
    baseplate.baseplateHeight = height/decimation;

    cv::Mat quantImage(baseplate.baseplateHeight, baseplate.baseplateWidth, CV_8UC2);
    for(int y=0;y<baseplate.baseplateHeight;y++)
        for(int x=0;x<baseplate.baseplateWidth;x++)
        {
            quantImage.at<cv::Vec2b>(y,x)[0]=(x<baseplate.baseplateWidth/2) ? 0:1;
            quantImage.at<cv::Vec2b>(y,x)[1]=0;
        }
    cv::Mat inputImage(baseplate.imageHeight, baseplate.imageWidth, CV_8UC3);
    for(int y=0;y<baseplate.imageHeight;y++)
        for(int x=0;x<baseplate.imageWidth;x++)
        {
            inputImage.at<cv::Vec3b>(y,x)=(x<baseplate.imageWidth/2) ? cv::Vec3b(30,128,128) :cv::Vec3b(220,128,128);
        }
    auto randVorm = LibMiniSteckBuilder::CreateIRandVorm();
    auto randVormen = randVorm->GetRandVormen(decimation);
    m_ministeckVormen->CreateMatchTable(colorVec,randVormen);
    m_ministeckVormen->CalcParts(inputImage,quantImage,baseplate,randVormen);
    std::array<uint8_t,7*15*2> refData =
    {
        0,   8,   0,   9,   0,   8,   0,   9,   0,   8,   0,   9,   0,   4,   1,   2,   1,   6,   1,   3,   1,   8,   1,   9,   1,   8,   1,   9,   1,   4,
        0,  10,   0,  11,   0,  10,   0,  11,   0,  10,   0,  11,   0,   7,   1,   2,   1,   6,   1,   3,   1,  10,   1,  11,   1,  10,   1,  11,   1,   7,
        0,   8,   0,   9,   0,   8,   0,   9,   0,   8,   0,   9,   0,   5,   1,   2,   1,   6,   1,   3,   1,   8,   1,   9,   1,   8,   1,   9,   1,   5,
        0,  10,   0,  11,   0,  10,   0,  11,   0,  10,   0,  11,   0,   4,   1,   2,   1,   6,   1,   3,   1,  10,   1,  11,   1,  10,   1,  11,   1,   4,
        0,   8,   0,   9,   0,   8,   0,   9,   0,   8,   0,   9,   0,   7,   1,   2,   1,   6,   1,   3,   1,   8,   1,   9,   1,   8,   1,   9,   1,   7,
        0,  10,   0,  11,   0,  10,   0,  11,   0,  10,   0,  11,   0,   5,   1,   2,   1,   6,   1,   3,   1,  10,   1,  11,   1,  10,   1,  11,   1,   5,
        0,   2,   0,   6,   0,   3,   0,   2,   0,   3,   0,   2,   0,   3,   1,   2,   1,   6,   1,   3,   1,   2,   1,   6,   1,   3,   1,   2,   1,   3
    };
    cv::Mat refImag(baseplate.baseplateHeight, baseplate.baseplateWidth, CV_8UC2, refData.data());
    EXPECT_EQ(0.0, cv::norm(refImag, quantImage, cv::NORM_L1));
    std::cout << quantImage << std::endl;

}
