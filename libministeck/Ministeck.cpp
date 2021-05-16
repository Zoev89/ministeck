#include "Ministeck.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

Ministeck::Ministeck(const std::filesystem::path &path, std::function<void(const IMinisteck &,bool)> hasImageFile)
    : m_path(path)
    , m_hasImageFile(hasImageFile)
{
    if (std::filesystem::exists(m_path))
    {
        boost::property_tree::ptree tree;
        std::ifstream input(path);
        boost::property_tree::read_xml(input, tree);
        boost::optional<std::filesystem::path> filename = tree.get_optional<std::filesystem::path>("doc.imagefile");
        if( filename )
        {
            AddImageFileLocal(filename.get());
            boost::optional<int> value = tree.get_optional<int>("doc.offsetX");
            if(value)
            {
                m_imageOffsetX = value.get();
            }
            value = tree.get_optional<int>("doc.offsetY");
            if(value)
            {
                m_imageOffsetY = value.get();
            }
            value = tree.get_optional<int>("doc.baseplateWidth");
            if(value)
            {
                m_baseplateWidth = value.get();
            }
            value = tree.get_optional<int>("doc.baseplateHeight");
            if(value)
            {
                m_baseplateHeight = value.get();
            }

        }
    }
    if (m_hasImageFile)
    {
        m_hasImageFile(*this,!m_img.empty());
    }
}
void Ministeck::AddImageFile(const std::filesystem::path &imageFile)
{
    AddImageFileLocal(imageFile);
    if (m_hasImageFile)
    {
        m_hasImageFile(*this,!m_img.empty());
    }
}

void Ministeck::AddImageFileLocal(const std::filesystem::path &imageFile)
{
    if (std::filesystem::exists(imageFile))
    {
        m_imageFileName = imageFile;
        m_img = cv::imread(imageFile, cv::IMREAD_COLOR);

        m_rgbImg = std::make_shared<cv::Mat>();
        cv::cvtColor(m_img, *m_rgbImg,cv::COLOR_BGR2RGB);
    }
}

void Ministeck::SaveFile()
{
   if(m_path.has_filename())
   {
       boost::property_tree::ptree tree;
       tree.add("doc","");
       if (!m_imageFileName.empty())
       {
           tree.put("doc.imagefile",m_imageFileName.c_str());
           tree.put("doc.offsetX", m_imageOffsetX);
           tree.put("doc.offsetY", m_imageOffsetY);
           tree.put("doc.baseplateWidth", m_baseplateWidth);
           tree.put("doc.baseplateHeight", m_baseplateHeight);
       }
       boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
       boost::property_tree::xml_parser::write_xml(m_path.c_str(), tree,
          std::locale(), settings);
   }
}

std::shared_ptr<cv::Mat> Ministeck::GetImage() const
{
    return m_rgbImg;
}

Ministeck::~Ministeck()
{
    SaveFile();
}


std::pair<int ,int> Ministeck::GetBasePlateSize() const
{
    return {m_baseplateWidth,m_baseplateHeight};
}

void Ministeck::SetBasePlateSize(int width,int height)
{
    m_baseplateWidth= width;
    m_baseplateHeight = height;
}

std::pair<int,int> Ministeck::GetImageOffset() const
{
    return {m_imageOffsetX, m_imageOffsetY};
}

void Ministeck::SetImageOffset(int left, int top)
{
    m_imageOffsetX = left;
    m_imageOffsetY = top;
}
