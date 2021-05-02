#ifndef IMINISTECK_H
#define IMINISTECK_H

#include <filesystem>

class IMinisteck
{
public:
    virtual ~IMinisteck() = default;
    virtual void AddImageFile(const std::filesystem::path &imageFile) = 0;

protected:
    IMinisteck()= default;
};

#endif // IMINISTECK_H
