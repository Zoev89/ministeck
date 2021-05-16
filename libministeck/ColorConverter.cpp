#include "ColorConverter.h"
#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

ColorConverter::ColorConverter()
{

}


Lab ColorConverter::Rgb2Lab(Rgb rgb) const
{
    std::vector<cv::Vec3b> vec;
    std::vector<cv::Vec3b> out;
    cv::Vec3b element(rgb.r, rgb.g, rgb.b);
    vec.push_back(element);

    cv::cvtColor(vec, out,cv::COLOR_RGB2Lab);
    Lab lab;
    lab.l = out[0][0];
    lab.a = out[0][1];
    lab.b = out[0][2];
    return lab;
}

Rgb ColorConverter::Lab2Rgb(Lab lab) const
{
    std::vector<cv::Vec3b> vec;
    std::vector<cv::Vec3b> out;
    cv::Vec3b element(lab.l, lab.a, lab.b);
    vec.push_back(element);

    cv::cvtColor(vec, out,cv::COLOR_Lab2RGB);
    Rgb rgb;
    rgb.r = out[0][0];
    rgb.g = out[0][1];
    rgb.b = out[0][2];
    return rgb;
}
