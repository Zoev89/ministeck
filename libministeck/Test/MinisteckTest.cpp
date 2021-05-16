#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "IMinisteck.h"
#include "libMinisteckBuilder.h"
#include "CImg.h"

#include <memory>
#include <fstream>
#include <iostream>
#include <future>
class MinisteckTest: public ::testing::Test
{
public:
   MinisteckTest( )
   {
       // initialization code here
   }

   void SetUp( )
   {
       // code here will execute just before the test ensues
       m_ministeck = LibMiniSteckBuilder::CreateIMinisteck("", [](const IMinisteck &, bool )
       {
       });
   }

   void CreateLib(const std::filesystem::path &path)
   {
       m_ministeck = LibMiniSteckBuilder::CreateIMinisteck(path, [this](const IMinisteck &, bool value)
       {
           m_hasImageFile.set_value(value);
       });
   }
   void CreateImageFile(const std::string &path)
   {
       int size_x = 640;
       int size_y = 480;
       int size_z = 1;
       int numberOfColorChannels = 3; // R G B
       unsigned char initialValue = 0;

       cimg_library::CImg<unsigned char> image(size_x, size_y, size_z, numberOfColorChannels, initialValue);
       image.save_jpeg(path.c_str());
   }

   void CheckHasImageFile(bool value)
   {
       auto fut=m_hasImageFile.get_future();
       EXPECT_EQ(value,fut.get());
   }
protected:
   std::unique_ptr<IMinisteck> m_ministeck;
   std::promise<bool> m_hasImageFile;
};

TEST_F (MinisteckTest, CreateWithNewFile)
{
    std::filesystem::path path="aap.mini";
    if (std::filesystem::exists(path))
    {
        std::filesystem::remove(path);
    }
    CreateLib(path);
    CheckHasImageFile(false);
    m_ministeck.reset();
    ASSERT_TRUE(std::filesystem::exists(path));
    std::ifstream input(path);
    std::string string;
    std::getline(input, string); // skip de header
    std::getline(input, string);
    EXPECT_EQ("<doc/>",string);
}

TEST_F (MinisteckTest, OpenFile)
{
    std::filesystem::path path="aap.mini";
    {
        std::ofstream output(path);
        output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
        output << "<doc/>" << std::endl;
    }
    CreateLib(path);
    CheckHasImageFile(false);
    m_ministeck.reset();
    std::ifstream input(path);
    std::string string;
    std::getline(input, string); // skip de header
    std::getline(input, string);
    EXPECT_EQ("<doc/>",string);
}

TEST_F (MinisteckTest, OpenWithJpgFile)
{
    std::filesystem::path path="aap.mini";
    {
        std::ofstream jpg("aapje.jpg");
        std::ofstream output(path);
        output << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
        output << "<doc><imagefile>aapje.jpg</imagefile><offsetX>20</offsetX><offsetY>10</offsetY><baseplateWidth>64</baseplateWidth><baseplateHeight>80</baseplateHeight></doc>" << std::endl;
    }
    CreateImageFile("aapje.jpg");
    CreateLib(path);
    CheckHasImageFile(true);
    auto [retOffX, retOffY] = m_ministeck->GetImageOffset();
    EXPECT_EQ(20, retOffX);
    EXPECT_EQ(10, retOffY);
    auto [width, height] = m_ministeck->GetBasePlateSize();
    EXPECT_EQ(64, width);
    EXPECT_EQ(80, height);

    m_ministeck.reset();
    std::ifstream input(path);
    std::string string;
    std::getline(input, string); // skip de header
    std::getline(input, string);
    EXPECT_EQ("<doc>", string);
    std::getline(input, string);
    EXPECT_EQ("    <imagefile>aapje.jpg</imagefile>",string);
    std::getline(input, string);
    EXPECT_EQ("    <offsetX>20</offsetX>",string);
    std::getline(input, string);
    EXPECT_EQ("    <offsetY>10</offsetY>",string);
    std::getline(input, string);
    EXPECT_EQ("    <baseplateWidth>64</baseplateWidth>",string);
    std::getline(input, string);
    EXPECT_EQ("    <baseplateHeight>80</baseplateHeight>",string);
}


TEST_F (MinisteckTest, AddImageFile)
{
    std::filesystem::path path="aap.mini";
    if (std::filesystem::exists(path))
    {
        std::filesystem::remove(path);
    }
    CreateLib(path);
    CheckHasImageFile(false);

    // now check that it has no image file when a wrong name is used
    m_hasImageFile = std::promise<bool>();  // make a new promise
    m_ministeck->AddImageFile("bah"); // does not exist
    CheckHasImageFile(false);

    // generate a jpg and check that it is now reported
    m_hasImageFile = std::promise<bool>();  // make a new promise
    CreateImageFile("aapje.jpg");
    m_ministeck->AddImageFile("aapje.jpg");
    CheckHasImageFile(true);
    //add offset to also test that

    m_ministeck.reset();
    ASSERT_TRUE(std::filesystem::exists(path));
    std::ifstream input(path);
    std::string string;
    std::getline(input, string); // skip de header
    std::getline(input, string);
    EXPECT_EQ("<doc>", string);
    std::getline(input, string);
    EXPECT_EQ("    <imagefile>aapje.jpg</imagefile>",string);
    std::getline(input, string);
    EXPECT_EQ("    <offsetX>0</offsetX>",string);
    std::getline(input, string);
    EXPECT_EQ("    <offsetY>0</offsetY>",string);
    std::getline(input, string);
    EXPECT_EQ("    <baseplateWidth>0</baseplateWidth>",string);
    std::getline(input, string);
    EXPECT_EQ("    <baseplateHeight>0</baseplateHeight>",string);
}

TEST_F(MinisteckTest, BaseplateSize)
{
    auto [initWidth, initHeight] = m_ministeck->GetBasePlateSize();
    EXPECT_EQ(0, initWidth);
    EXPECT_EQ(0, initHeight);

    int width = 100;
    int height = 200;
    m_ministeck->SetBasePlateSize(width,height);
    auto [retWidth, retHeight] = m_ministeck->GetBasePlateSize();
    EXPECT_EQ(width, retWidth);
    EXPECT_EQ(height, retHeight);
}

TEST_F(MinisteckTest, ImageOffset)
{
    auto [initOffX, initOffY] = m_ministeck->GetImageOffset();
    EXPECT_EQ(0, initOffX);
    EXPECT_EQ(0, initOffY);

    int offX = 100;
    int offY = 200;
    m_ministeck->SetImageOffset(offX,offY);
    auto [retOffX, retOffY] = m_ministeck->GetImageOffset();
    EXPECT_EQ(offX, retOffX);
    EXPECT_EQ(offY, retOffY);
}
