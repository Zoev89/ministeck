#ifndef LIBMINISTECKBUILDER_H
#define LIBMINISTECKBUILDER_H
#include <memory>
#include <filesystem>
#include <functional>

class IColors;
class IMinisteck;
class IColorConverter;
class IQuantize;
class IScaledOutputImage;
class IRandVorm;
class IMinisteckVormen;

class LibMiniSteckBuilder
{
public:
    LibMiniSteckBuilder();
    static std::unique_ptr<IColors> CreateIColors();
    static std::unique_ptr<IColors> CreateIColorsDependencyInjection(std::unique_ptr<IColorConverter> colorConverter);
    static std::unique_ptr<IColorConverter> CreateIColorConverter();
    static std::unique_ptr<IMinisteck> CreateIMinisteck(const std::filesystem::path &path, std::function<void(const IMinisteck &, bool)> hasImageFile);
    static std::unique_ptr<IMinisteck> CreateIMinisteckDependencyInjection(const std::filesystem::path &path, std::function<void(const IMinisteck &, bool)> hasImageFile
                                                        , std::unique_ptr<IColors> colors
                                                        , std::unique_ptr<IQuantize> quantize
                                                        , std::unique_ptr<IScaledOutputImage> scaledOuputImage
                                                        , std::unique_ptr<IRandVorm> randvorm
                                                        );
    static std::unique_ptr<IQuantize> CreateIQuantize();
    static std::unique_ptr<IScaledOutputImage> CreateIScaledOutputImage();
    static std::unique_ptr<IRandVorm> CreateIRandVorm();
    static std::unique_ptr<IMinisteckVormen> CreateIMinisteckVormen();
};

#endif // LIBMINISTECKBUILDER_H
