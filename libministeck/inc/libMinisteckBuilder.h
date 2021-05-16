#ifndef LIBMINISTECKBUILDER_H
#define LIBMINISTECKBUILDER_H
#include <memory>
#include <filesystem>
#include <functional>

class IColors;
class IMinisteck;
class IColorConverter;

class LibMiniSteckBuilder
{
public:
    LibMiniSteckBuilder();
    static std::unique_ptr<IColors> CreateIColors();
    static std::unique_ptr<IColors> CreateIColorsDependencyInjection(std::unique_ptr<IColorConverter> colorConverter);
    static std::unique_ptr<IColorConverter> CreateIColorConverter();
    static std::unique_ptr<IMinisteck> CreateIMinisteck(const std::filesystem::path &path, std::function<void(const IMinisteck &, bool)> hasImageFile);
};

#endif // LIBMINISTECKBUILDER_H
