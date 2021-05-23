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
                <nummer>601</nummer>\
                <rgb>\
                    <r>30</r>\
                    <g>30</g>\
                    <b>30</b>\
                </rgb>\
            </color>\
            <color>\
               <naam>Blauw</naam>\
               <nummer>602</nummer>\
               <rgb>\
                   <r>26</r>\
                   <g>60</g>\
                   <b>180</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Blauw lichter</naam>\
               <nummer>603</nummer>\
               <rgb>\
                   <r>24</r>\
                   <g>90</g>\
                   <b>185</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Licht Groen</naam>\
               <nummer>604</nummer>\
               <rgb>\
                   <r>14</r>\
                   <g>138</g>\
                   <b>58</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Donkergroen</naam>\
               <nummer>605</nummer>\
               <rgb>\
                   <r>14</r>\
                   <g>75</g>\
                   <b>35</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Rood</naam>\
               <nummer>606</nummer>\
               <rgb>\
                   <r>170</r>\
                   <g>20</g>\
                   <b>29</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Oranje</naam>\
               <nummer>607</nummer>\
               <rgb>\
                   <r>215</r>\
                   <g>60</g>\
                   <b>8</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Geel</naam>\
               <nummer>608</nummer>\
               <rgb>\
                   <r>218</r>\
                   <g>190</g>\
                   <b>3</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Biege</naam>\
               <nummer>609</nummer>\
               <rgb>\
                   <r>226</r>\
                   <g>200</g>\
                   <b>126</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Lichtbruin</naam>\
               <nummer>610</nummer>\
               <rgb>\
                   <r>209</r>\
                   <g>137</g>\
                   <b>25</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Bruin</naam>\
               <nummer>611</nummer>\
               <rgb>\
                   <r>180</r>\
                   <g>80</g>\
                   <b>32</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Donkerbruin</naam>\
               <nummer>612</nummer>\
               <rgb>\
                   <r>115</r>\
                   <g>40</g>\
                   <b>30</b>\
               </rgb>\
            </color>\
            <color>\
                <naam>Wit</naam>\
                <nummer>613</nummer>\
                <rgb>\
                    <r>228</r>\
                    <g>222</g>\
                    <b>218</b>\
                </rgb>\
            </color>\
            <color>\
               <naam>Lichtgrijs</naam>\
               <nummer>614</nummer>\
               <rgb>\
                   <r>170</r>\
                   <g>165</g>\
                   <b>160</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Roze</naam>\
               <nummer>615</nummer>\
               <rgb>\
                   <r>226</r>\
                   <g>148</g>\
                   <b>148</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Donkergrijs</naam>\
               <nummer>616</nummer>\
               <rgb>\
                   <r>145</r>\
                   <g>133</g>\
                   <b>121</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Olijf</naam>\
               <nummer>617</nummer>\
               <rgb>\
                   <r>61</r>\
                   <g>49</g>\
                   <b>26</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Goud</naam>\
               <nummer>618</nummer>\
               <rgb>\
                   <r>130</r>\
                   <g>100</g>\
                   <b>60</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Vleeskleur</naam>\
               <nummer>619</nummer>\
               <rgb>\
                   <r>230</r>\
                   <g>160</g>\
                   <b>109</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Paars</naam>\
               <nummer>620</nummer>\
               <rgb>\
                   <r>99</r>\
                   <g>42</g>\
                   <b>89</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Middelgroen</naam>\
               <nummer>621</nummer>\
               <rgb>\
                   <r>65</r>\
                   <g>150</g>\
                   <b>10</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Maisgeel</naam>\
               <nummer>622</nummer>\
               <rgb>\
                   <r>230</r>\
                   <g>130</g>\
                   <b>4</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Felroze</naam>\
               <nummer>623</nummer>\
               <rgb>\
                   <r>215</r>\
                   <g>52</g>\
                   <b>100</b>\
               </rgb>\
            </color>\
            <color>\
               <naam>Hemelblauw</naam>\
               <nummer>624</nummer>\
               <rgb>\
                   <r>99</r>\
                   <g>148</g>\
                   <b>223</b>\
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
