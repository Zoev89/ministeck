#pragma once

#include <algorithm>

struct IBaseplateType
{
    IBaseplateType()
        : baseplateWidth(32)
        , baseplateHeight(16)
        , imageWidth(0)
        , imageHeight(0)
        , imageOffsetX(0)
        , imageOffsetY(0)
    {

    }
    int baseplateWidth;
    int baseplateHeight;
    int imageWidth;
    int imageHeight;
    int imageOffsetX;
    int imageOffsetY;
    int GetDecimation() const
    {
        int decimation = ((baseplateWidth > 0) && (baseplateHeight > 0)) ? std::min((imageWidth - imageOffsetX) / baseplateWidth, (imageHeight - imageOffsetY) / baseplateHeight)
                                                                         : 1;
        return (decimation == 0) ? 1: decimation;
    };
    bool operator==(const IBaseplateType& lhs) const
    {
        return (baseplateWidth == lhs.baseplateWidth)
                && (baseplateHeight == lhs.baseplateHeight)
                && (imageWidth == lhs.imageWidth)
                && (imageHeight == lhs.imageHeight)
                && (imageOffsetX == lhs.imageOffsetX)
                && (imageOffsetY == lhs.imageOffsetY);
    }
};
