#ifndef MINISTECK_H
#define MINISTECK_H

#include "IMinisteck.h"
#include <filesystem>
#include <functional>
#include <memory>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

class Ministeck : public IMinisteck
{
public:
    Ministeck(const std::filesystem::path &path, std::function<void(const IMinisteck &, bool)> hasImageFile);
    ~Ministeck();
    virtual void AddImageFile(const std::filesystem::path &imageFile) override;
    virtual std::shared_ptr<cv::Mat> GetImage() const override;
    virtual std::pair<int ,int> GetBasePlateSize() const override; // return width height
    virtual void SetBasePlateSize(int width,int height) override;
    virtual std::pair<int,int> GetImageOffset() const override; // return leftCoordx,topCoordy
    virtual void SetImageOffset(int left, int top) override;


private:
    void SaveFile();
    void AddImageFileLocal(const std::filesystem::path &imageFile);

    std::filesystem::path m_path;
    std::filesystem::path m_imageFileName;
    std::function<void(const IMinisteck &, bool)> m_hasImageFile; // use the this if the caller wants to acces the interface again
    cv::Mat m_img;
    std::shared_ptr<cv::Mat> m_rgbImg;
    int m_baseplateWidth = 0;
    int m_baseplateHeight = 0;
    int m_imageOffsetX = 0;
    int m_imageOffsetY = 0;

};

#endif // MINISTECK_H
