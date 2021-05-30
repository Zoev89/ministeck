#pragma once


#include <vector>
#include <string>
#include <ostream>
#include <map>
#include "IColorTypes.h"
#include <opencv2/core.hpp>

class IBaseplateType;

enum class Vorm
{
    Enkeltje = 0,
    Tweetje,
    Drietje,
    Vierkant,
    Hoekje,
};

namespace
{
std::map<Vorm,std::string> gPrintVorm {
        {Vorm::Enkeltje, "Enkeltje"},
        {Vorm::Tweetje, "Tweetje"},
        {Vorm::Drietje, "Drietje"},
        {Vorm::Vierkant, "Vierkant"},
        {Vorm::Hoekje, "Hoekje"}
        };
}

inline std::string ToString(const Vorm& vorm)
{
    return (gPrintVorm.contains(vorm)) ? gPrintVorm[vorm]: std::string("Unknown " + std::to_string(static_cast<int>(vorm)));
}

// Google test framework to print Vorm
// twee mogelijkheden via de PrintTo voor het gevaldat de operator << al bezet is
// opertor<< implementeren
// de laatste is het flexibelst want dan werkt ook EXPECT(...) << Vorm
//void PrintTo(const Vorm& vorm, std::ostream* os)
//{
//  *os << ToString(vorm);
//}
inline std::ostream& operator<<(std::ostream& os, const Vorm& vorm)
{
  return os << ToString(vorm);
}

struct MinisteckMatch
{
    int offsetX = 0;
    int offsetY = 0;
    cv::Mat match;
    int randVormIndex;
    bool operator==(const MinisteckMatch &lhs) const
    {
        return    ((offsetX == lhs.offsetX)
                && (offsetY == lhs.offsetY)
                && (0.0== cv::norm(match, lhs.match,cv::NORM_L1))
                && (randVormIndex == lhs.randVormIndex));
    };

};

struct MinisteckVorm
{
    Vorm vorm = Vorm::Enkeltje;
    std::vector<MinisteckMatch> eenEnkeleOrientatie;
    double accumulatedError = 0;
    int    aantalTests = 0;
    bool operator==(const MinisteckVorm &lhs) const
    {
        return ((vorm == lhs.vorm)
             && (eenEnkeleOrientatie == lhs.eenEnkeleOrientatie)
             && (accumulatedError == lhs.accumulatedError)
             && (aantalTests == lhs.aantalTests));
    };
};

struct MinisteckKleur
{
    Color color;
    std::vector<MinisteckVorm> matchVormen;
    std::map<Vorm, double> bestMatchError;
    std::map<Vorm, int> stukjesPerVorm;;
};

class IMinisteckVormen
{
public:
    virtual ~IMinisteckVormen() = default;
    virtual void CreateMatchTable(const std::vector<Color> &colors, const std::vector<cv::Mat>& randVormen) = 0;
    virtual std::vector<MinisteckKleur> GetMatchTable() const = 0;
    virtual void CalcParts(const cv::Mat& inputImage, cv::Mat& quantizedImage, const IBaseplateType &baseplate,
                           const std::vector<cv::Mat>& randVormen) = 0;
protected:
    IMinisteckVormen() = default;
};
