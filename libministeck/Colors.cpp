#include "Colors.h"
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/optional.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>

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
                <luv>\
                    <l>1</l>\
                    <u>1</u>\
                    <v>1</v>\
                </luv>\
            </color>\
        </colors>\
    ");
}

Colors::Colors()
{
    boost::property_tree::ptree tree;
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
            color.r = it.second.get<int>("rgb.r");
            color.g = it.second.get<int>("rgb.g");
            color.b = it.second.get<int>("rgb.b");
        }
        boost::optional< const boost::property_tree::ptree& > luv = it.second.get_child_optional("luv");
        if( luv )
        {
             //std::cout << "Luv" << std::endl;
        }
        m_colors.emplace_back(color);
    }
}
std::vector<Color> Colors::GetColors()
{
    return m_colors;
}
