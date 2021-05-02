#include <gtest/gtest.h>
#include "IMinisteck.h"
#include "libMinisteckBuilder.h"

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
   }

   void CreateLib(const std::filesystem::path &path)
   {
       m_ministeck = LibMiniSteckBuilder::CreateIMinisteck(path, [this](bool value)
       {
           m_hasImageFile.set_value(value);
       });
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
        output << "<doc><imagefile>aapje.jpg</imagefile></doc>" << std::endl;
    }
    CreateLib(path);
    CheckHasImageFile(true);
    m_ministeck.reset();
    std::ifstream input(path);
    std::string string;
    std::getline(input, string); // skip de header
    std::getline(input, string);
    EXPECT_EQ("<doc><imagefile>aapje.jpg</imagefile></doc>",string);
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
    {
        std::ofstream jpg("aapje.jpg");
    }
    m_hasImageFile = std::promise<bool>();  // make a new promise
    m_ministeck->AddImageFile("bah"); // does not exist
    m_hasImageFile = std::promise<bool>();  // make a new promise
    m_ministeck->AddImageFile("aapje.jpg");

    m_ministeck.reset();
    ASSERT_TRUE(std::filesystem::exists(path));
    std::ifstream input(path);
    std::string string;
    std::getline(input, string); // skip de header
    std::getline(input, string);
    EXPECT_EQ("<doc><imagefile>aapje.jpg</imagefile></doc>",string);
}
