#ifndef MINISTECK_H
#define MINISTECK_H

#include "IMinisteck.h"
#include <filesystem>
#include <functional>

class Ministeck : public IMinisteck
{
public:
    Ministeck(const std::filesystem::path &path, std::function<void(bool)> hasImageFile);
    ~Ministeck();
    virtual void AddImageFile(const std::filesystem::path &imageFile) override;

private:
    void SaveFile();
    void AddImageFileLocal(const std::filesystem::path &imageFile);

    std::filesystem::path m_path;
    std::filesystem::path m_imageFileName;
    std::function<void(bool)> m_hasImageFile;
};

#endif // MINISTECK_H
