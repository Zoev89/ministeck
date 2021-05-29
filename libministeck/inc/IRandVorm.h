#pragma once

#include <vector>
#include <opencv2/core.hpp>

class IRandVorm
{
public:
    virtual ~IRandVorm() = default;
    virtual std::vector<cv::Mat> GetRandVormen(int decimation) const = 0;
protected:
    IRandVorm() = default;
};
