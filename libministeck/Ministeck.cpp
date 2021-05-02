#include "Ministeck.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

Ministeck::Ministeck(const std::filesystem::path &path, std::function<void(bool)> hasImageFile)
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
        }
    }
    if (m_hasImageFile)
    {
        m_hasImageFile(!m_imageFileName.empty());
    }
}
void Ministeck::AddImageFile(const std::filesystem::path &imageFile)
{
    AddImageFileLocal(imageFile);
    if (m_hasImageFile)
    {
        m_hasImageFile(!m_imageFileName.empty());
    }
}

void Ministeck::AddImageFileLocal(const std::filesystem::path &imageFile)
{
    if (std::filesystem::exists(imageFile))
    {
        m_imageFileName = imageFile;
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
       }
       boost::property_tree::xml_parser::write_xml(m_path.c_str(), tree);
   }
}

Ministeck::~Ministeck()
{
    SaveFile();
}
