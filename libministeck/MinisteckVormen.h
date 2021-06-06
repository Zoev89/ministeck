#pragma once

#include <IMinisteckVormen.h>

class MinisteckVormen : public IMinisteckVormen
{
public:
    MinisteckVormen() = default;
    virtual void CreateMatchTable(const std::vector<Color> &colors, const std::vector<cv::Mat>& randVormen) override;
    virtual std::vector<MinisteckKleur> GetMatchTable() const override;
    virtual void CalcParts(const cv::Mat& inputImage, cv::Mat& quantizedImage, const IBaseplateType &baseplate,
                           const std::vector<cv::Mat>& randVormen) override;


private:
    MinisteckMatch FillMatch(int offsetY, int offsetX, int randVormIndex, const std::vector<cv::Mat> &randVorm, const Lab &color);
    double EnkeltjePenalty(int offsetY, int offsetX, const std::vector<cv::Point> &points, const cv::Mat &quantizedImage);
    std::vector<MinisteckKleur> m_matchTable;
};

