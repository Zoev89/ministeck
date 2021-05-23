#ifndef MINISTECK_H
#define MINISTECK_H

#include "IMinisteck.h"
#include <filesystem>
#include <functional>
#include <memory>
#include "IBaseplateType.h"
#include "IColorTypes.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

class IColors;
class IQuantize;
class IScaledOutputImage;


class Ministeck : public IMinisteck
{
public:
    Ministeck(const std::filesystem::path &path, std::function<void(const IMinisteck &, bool)> hasImageFile
              , std::unique_ptr<IColors> colors
              , std::unique_ptr<IQuantize> quantize
              , std::unique_ptr<IScaledOutputImage> scaledOuputImage
              );
    ~Ministeck();
    virtual void AddImageFile(const std::filesystem::path &imageFile) override;
    virtual std::shared_ptr<cv::Mat> GetImage() const override;
    virtual std::pair<int ,int> GetBasePlateSize() const override; // return width height
    virtual void SetBasePlateSize(int width,int height) override;
    virtual std::pair<int,int> GetImageOffset() const override; // return leftCoordx,topCoordy
    virtual void SetImageOffset(int left, int top) override;
    virtual std::shared_ptr<cv::Mat> QuantizeImage() override;
    virtual std::string GetStatus(int x,int y) override;


private:
    void SaveFile();
    void AddImageFileLocal(const std::filesystem::path &imageFile);

    std::unique_ptr<IColors> m_colors;
    std::unique_ptr<IQuantize> m_quantize;
    std::unique_ptr<IScaledOutputImage> m_scaledOuputImage;

    std::filesystem::path m_path;
    std::filesystem::path m_imageFileName;
    std::vector<Color> m_colorVec;
    std::function<void(const IMinisteck &, bool)> m_hasImageFile; // use the this if the caller wants to acces the interface again
    cv::Mat m_img;
    cv::Mat m_labImg;
    cv::Mat m_quantImg;
    std::shared_ptr<cv::Mat> m_rgbImg;
    IBaseplateType m_baseplate;
};

#endif // MINISTECK_H
