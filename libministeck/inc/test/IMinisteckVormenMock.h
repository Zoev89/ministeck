#pragma once


#include "gmock/gmock.h"
#include "IMinisteckVormen.h"


class IMinisteckVormenMock: public IMinisteckVormen
{
public:
    MOCK_METHOD(void, CreateMatchTable, (const std::vector<Color> &colors, const std::vector<cv::Mat>& randVormen), (override));
    MOCK_METHOD(std::vector<MinisteckKleur>, GetMatchTable, (), (const, override));
    MOCK_METHOD(void, CalcParts, (const cv::Mat& inputImage, cv::Mat& quantizedImage, const IBaseplateType &baseplate,
                           const std::vector<cv::Mat>& randVormen), (override));
};
