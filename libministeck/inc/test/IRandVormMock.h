#pragma once

#include "gmock/gmock.h"
#include "IRandVorm.h"


class IRandVormMock: public IRandVorm
{
public:
    MOCK_METHOD(std::vector<cv::Mat>, GetRandVormen, (int decimation), (const override));
};
