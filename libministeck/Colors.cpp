#include "Colors.h"
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/optional.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>
#include "IColorConverter.h"

namespace
{
    const std::string g_ColorXml("\
        <colors>\
            <color>\
                <naam>Zwart</naam>\
                <nummer>1</nummer>\
                <rgb>\
                    <r>0</r>\
                    <g>0</g>\
                    <b>0</b>\
                </rgb>\
            </color>\
            <color>\
                <naam>Wit</naam>\
                <nummer>2</nummer>\
                <rgb>\
                    <r>255</r>\
                    <g>255</g>\
                    <b>255</b>\
                </rgb>\
            </color>\
        </colors>\
    ");
}

Colors::Colors(std::unique_ptr<IColorConverter> colorConverter)
    :m_colorConverter(std::move(colorConverter))
{
    boost::property_tree::ptree tree;
    // create an array stream object without coping data
    boost::iostreams::stream<boost::iostreams::array_source> stream(g_ColorXml.c_str(), g_ColorXml.size());
    boost::property_tree::read_xml(stream, tree);
    for(auto const & it: tree.get_child("colors"))
    {
        Color color;
        color.naam = it.second.get<std::string>("naam");
        color.colorNummer = it.second.get<int>("nummer");
        boost::optional< const boost::property_tree::ptree& > rgb = it.second.get_child_optional("rgb");
        if( rgb )
        {
            color.rgb.r = it.second.get<int>("rgb.r");
            color.rgb.g = it.second.get<int>("rgb.g");
            color.rgb.b = it.second.get<int>("rgb.b");
            color.lab = m_colorConverter->Rgb2Lab(color.rgb);
        }
        m_colors.emplace_back(color);
    }
}
std::vector<Color> Colors::GetColors()
{
    return m_colors;
}
