#include "Ministeck.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>
#include <iostream>

#include "IColors.h"
#include "IQuantize.h"
#include "IScaledOutputImage.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

Ministeck::Ministeck(const std::filesystem::path &path, std::function<void(const IMinisteck &,bool)> hasImageFile
                     , std::unique_ptr<IColors> colors
                     , std::unique_ptr<IQuantize> quantize
                     , std::unique_ptr<IScaledOutputImage> scaledOuputImage)
    : m_colors(std::move(colors))
    , m_quantize(std::move(quantize))
    , m_scaledOuputImage(std::move(scaledOuputImage))
    , m_path(path)
    , m_hasImageFile(hasImageFile)
{
    m_colorVec = m_colors->GetColors();
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
                m_baseplate.imageOffsetX = value.get();
            }
            value = tree.get_optional<int>("doc.offsetY");
            if(value)
            {
                m_baseplate.imageOffsetY = value.get();
            }
            value = tree.get_optional<int>("doc.baseplateWidth");
            if(value)
            {
                m_baseplate.baseplateWidth = value.get();
            }
            value = tree.get_optional<int>("doc.baseplateHeight");
            if(value)
            {
                m_baseplate.baseplateHeight = value.get();
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

        cv::cvtColor(m_img, m_labImg,cv::COLOR_BGR2Lab);
        m_baseplate.imageWidth = m_rgbImg->cols;
        m_baseplate.imageHeight = m_rgbImg->rows;
        //imshow("test", m_labImg);
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
           tree.put("doc.offsetX", m_baseplate.imageOffsetX);
           tree.put("doc.offsetY", m_baseplate.imageOffsetY);
           tree.put("doc.baseplateWidth", m_baseplate.baseplateWidth);
           tree.put("doc.baseplateHeight", m_baseplate.baseplateHeight);
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
    return {m_baseplate.baseplateWidth,m_baseplate.baseplateHeight};
}

void Ministeck::SetBasePlateSize(int width,int height)
{
    m_baseplate.baseplateWidth= width;
    m_baseplate.baseplateHeight = height;
}

std::pair<int,int> Ministeck::GetImageOffset() const
{
    return {m_baseplate.imageOffsetX, m_baseplate.imageOffsetY};
}

void Ministeck::SetImageOffset(int left, int top)
{
    m_baseplate.imageOffsetX = left;
    m_baseplate.imageOffsetY = top;
}

std::shared_ptr<cv::Mat> Ministeck::QuantizeImage()
{
    m_quantImg = m_quantize->QuantizeImage(m_labImg, m_baseplate, m_colorVec);
    auto scaledImage = m_scaledOuputImage->ScaleImage(m_quantImg, m_baseplate, m_colorVec);
    return scaledImage;
}

std::string Ministeck::GetStatus(int x,int y)
{
    std::string string;
    if (!m_quantImg.empty())
    {
        x = std::min(x, m_quantImg.cols-1);
        y = std::min(y, m_quantImg.rows-1);
        auto index = m_quantImg.at<cv::Vec2b>(y,x)[0];
        if (index < m_colorVec.size())
        {
            string = m_colorVec[index].naam + "(" + std::to_string(m_colorVec[index].colorNummer) + ")";
        }
    }
    return string;
}

std::shared_ptr<cv::Mat> Ministeck::PartCalculation()
{
    IBaseplateType baseplate = m_baseplate;
    baseplate.imageWidth = baseplate.baseplateWidth*8;
    baseplate.imageHeight = baseplate.baseplateHeight*8;
    baseplate.imageOffsetX = 0;
    baseplate.imageOffsetY = 0;
    auto scaledImage = m_scaledOuputImage->RenderImage(m_quantImg, baseplate, m_colorVec);
    return scaledImage;

}
