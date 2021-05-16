#ifndef IMINISTECK_H
#define IMINISTECK_H

#include <filesystem>
#include <memory>
#include <utility>
#include <opencv2/core.hpp>

class IMinisteck
{
public:
    virtual ~IMinisteck() = default;
    virtual void AddImageFile(const std::filesystem::path &imageFile) = 0;
    virtual std::shared_ptr<cv::Mat> GetImage() const = 0;  // I return a shared pointer because the outside might hold this data longer then the lifetime of this interface
    virtual std::pair<int ,int> GetBasePlateSize() const = 0; // return width height
    virtual void SetBasePlateSize(int width,int height) = 0;
    virtual std::pair<int,int> GetImageOffset() const = 0; // return leftCoordx,topCoordy
    virtual void SetImageOffset(int left, int top) = 0;

protected:
    IMinisteck()= default;
};

#endif // IMINISTECK_H
