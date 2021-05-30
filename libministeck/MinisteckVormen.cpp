#include "MinisteckVormen.h"
#include "IBaseplateType.h"
#include <limits>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void MinisteckVormen::CreateMatchTable(const std::vector<Color> &colors, const std::vector<cv::Mat> &randVormen)
{
    if (randVormen.size() != 16)
    {
        throw std::invalid_argument("randVormen moet 16 elementen hebben ipv " + std::to_string(randVormen.size()));
    }

    m_matchTable.clear();
    for (const auto &color: colors)
    {
        MinisteckKleur kleur;
        kleur.color = color;
        kleur.bestMatchError[Vorm::Enkeltje] = 0.0;
        kleur.bestMatchError[Vorm::Tweetje] = 0.0;
        kleur.bestMatchError[Vorm::Drietje] = 0.0;
        kleur.bestMatchError[Vorm::Vierkant] = 0.0;
        kleur.bestMatchError[Vorm::Hoekje] = 0.0;

        kleur.stukjesPerVorm[Vorm::Enkeltje] = 0;
        kleur.stukjesPerVorm[Vorm::Tweetje] = 0;
        kleur.stukjesPerVorm[Vorm::Drietje] = 0;
        kleur.stukjesPerVorm[Vorm::Vierkant] = 0;
        kleur.stukjesPerVorm[Vorm::Hoekje] = 0;

        MinisteckVorm vorm;
        vorm.vorm = Vorm::Enkeltje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,1,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Tweetje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,2,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,1,3,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Tweetje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,4,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,0,5,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Drietje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,2,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,1,6,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,2,3,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Drietje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,4,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,0,7,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(2,0,5,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Vierkant;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,8,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,1,9,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,0,10,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,1,11,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Hoekje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,4,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,0,12,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,1,3,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Hoekje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,13,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,1,3,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,0,5,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Hoekje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,2,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,1,14,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,1,5,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        vorm = MinisteckVorm();
        vorm.vorm = Vorm::Hoekje;
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(0,0,4,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,0,15,randVormen, kleur.color.lab));
        vorm.eenEnkeleOrientatie.emplace_back(FillMatch(1,-1,2,randVormen, kleur.color.lab));
        kleur.matchVormen.emplace_back(vorm);

        m_matchTable.emplace_back(kleur);
    }
}

std::vector<MinisteckKleur> MinisteckVormen::GetMatchTable() const
{
    return m_matchTable;
}

MinisteckMatch MinisteckVormen::FillMatch(int offsetY, int offsetX, int randVormIndex, const std::vector<cv::Mat> &randVorm, const Lab &color)
{
    MinisteckMatch match;
    match.offsetX = offsetX;
    match.offsetY = offsetY;
    match.randVormIndex = randVormIndex;

    match.match = cv::Mat (randVorm[randVormIndex].rows, randVorm[randVormIndex].cols, CV_8UC3);
    cv::Vec3b onaangepast(color.l, color.a, color.b);
    cv::Vec3b aangepast(static_cast<uint8_t>((color.l > 128) ? color.l*0.9:color.l*1.1), color.a, color.b);
    for (int y=0;y<match.match.rows;y++)
        for (int x=0;x<match.match.cols;x++)
        {
            match.match.at<cv::Vec3b>(y,x) = (randVorm[randVormIndex].at<uint8_t>(y,x) == 1) ? aangepast: onaangepast;
        }
    return match;
}


void MinisteckVormen::CalcParts(const cv::Mat& inputImage, cv::Mat& quantizedImage, const IBaseplateType &baseplate,
                                const std::vector<cv::Mat>& randVormen)
{
    int decimation = randVormen[0].rows;

    // first roi the image then downscale it and the do pixel matching
    cv::Rect roi(baseplate.imageOffsetX, baseplate.imageOffsetY, baseplate.baseplateWidth*baseplate.GetDecimation(), baseplate.baseplateHeight*baseplate.GetDecimation());
    //Create the cv::Mat with the ROI you need, where "image" is the cv::Mat you want to extract the ROI from
    cv::Mat image_roi = inputImage(roi);
    cv::Mat scaleImg;
    cv::resize(image_roi,scaleImg,cv::Size(baseplate.baseplateWidth*decimation,baseplate.baseplateHeight*decimation));
    // now I have scaleImg that has the requered decimation and baseplate coordinates are transferable with decimation
    for (int y=0;y<baseplate.baseplateHeight; y++)
        for (int x=0;x<baseplate.baseplateWidth;x++)
        {
            if (quantizedImage.at<cv::Vec2b>(y,x)[1] == 0)
            {
                // pixel is not assigned yet
                int colorIndex = quantizedImage.at<cv::Vec2b>(y,x)[0];
                double bestMatch = std::numeric_limits<double>::max();
                size_t bestMatchIndex = 0; // default naar een enkeltje
                for (size_t i=0;i<m_matchTable[colorIndex].matchVormen.size();i++)
                {
                    // kijk eerst of alle pinnen geplaatst kunnen worden
                    bool past = true;
                    for (size_t offsets = 0; offsets < m_matchTable[colorIndex].matchVormen[i].eenEnkeleOrientatie.size(); offsets++)
                    {
                        int offsetX = x + m_matchTable[colorIndex].matchVormen[i].eenEnkeleOrientatie[offsets].offsetX;
                        if ((offsetX < 0) || (offsetX >= baseplate.baseplateWidth))
                        {
                            past = false;
                            break;
                        }
                        int offsetY = y + m_matchTable[colorIndex].matchVormen[i].eenEnkeleOrientatie[offsets].offsetY;
                        if ((offsetY < 0) || (offsetY >= baseplate.baseplateHeight))
                        {
                            past = false;
                            break;
                        }
                        // check of die nog vrij is
                        if ((quantizedImage.at<cv::Vec2b>(offsetY,offsetX)[0] != colorIndex) || (quantizedImage.at<cv::Vec2b>(offsetY,offsetX)[1] != 0))
                        {
                            past = false;
                            break;
                        }
                    }
                    if (past)
                    {
                        double match = 0;
                        for (const auto& pin:m_matchTable[colorIndex].matchVormen[i].eenEnkeleOrientatie)
                        {
                            int offsetX = (x + pin.offsetX) * decimation;
                            int offsetY = (y + pin.offsetY) * decimation;
                            cv::Rect roi(offsetX, offsetY, decimation, decimation);
                            //Create the cv::Mat with the ROI you need, where "image" is the cv::Mat you want to extract the ROI from
                            cv::Mat matchImg = scaleImg(roi);
                            match+=cv::norm(matchImg,pin.match);
                        }
                        // eerst de match normalizeren
                        match /= m_matchTable[colorIndex].matchVormen[i].eenEnkeleOrientatie.size();
                        if (match <bestMatch)
                        {
                            bestMatch = match;
                            bestMatchIndex = i;
                        }
                    }
                }
                for (const auto& pin:m_matchTable[colorIndex].matchVormen[bestMatchIndex].eenEnkeleOrientatie)
                {
                    int offsetX = x + pin.offsetX;
                    int offsetY = y + pin.offsetY;
                    quantizedImage.at<cv::Vec2b>(offsetY,offsetX)[1] = pin.randVormIndex;
                }
                // nu nog de boekhouding
            }
        }

}

