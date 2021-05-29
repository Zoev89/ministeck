#pragma once
#include "IRandVorm.h"

class RandVorm : public IRandVorm
{
public:
    RandVorm();
    virtual std::vector<cv::Mat> GetRandVormen(int decimation) const override;
};

