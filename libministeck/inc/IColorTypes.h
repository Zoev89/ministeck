#pragma once

#include <cstdint>
#include <string>

struct Rgb
{
    Rgb()
        :Rgb(0,0,0)
    {};
    Rgb(uint8_t _r, uint8_t _g, uint8_t _b)
        : r(_r)
        , g(_g)
        , b(_b)
    {};
    uint8_t r;
    uint8_t g;
    uint8_t b;
    bool operator==(const Rgb &lhs) const
    {
        return (r==lhs.r)
                && (g==lhs.g)
                && (b==lhs.b);
    };
};

struct Lab
{
    Lab()
        :Lab(0,0,0)
    {};
    Lab(uint8_t _l, uint8_t _a, uint8_t _b)
        : l(_l)
        , a(_a)
        , b(_b)
    {};
    uint8_t l=0;
    uint8_t a=0;
    uint8_t b=0;
    bool operator==(const Lab &lhs) const
    {
        return (l==lhs.l)
                && (a==lhs.a)
                && (b==lhs.b);
    };
};

struct Color
{
    int colorNummer;
    std::string naam;
    Rgb rgb;
    Lab lab;
    bool operator==(const Color &lhs) const
    {
        return (colorNummer == lhs.colorNummer)
                && (naam == lhs.naam)
                && (rgb == lhs.rgb)
                && lab == lhs.lab;
    };
};
