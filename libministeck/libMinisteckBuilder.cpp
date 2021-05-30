#include "inc/libMinisteckBuilder.h"
#include "Colors.h"
#include "ColorConverter.h"
#include "Ministeck.h"
#include "Quantize.h"
#include "ScaledOutputImage.h"
#include "RandVorm.h"
#include "MinisteckVormen.h"

LibMiniSteckBuilder::LibMiniSteckBuilder()
{

}

std::unique_ptr<IColors> LibMiniSteckBuilder::CreateIColors()
{
    return CreateIColorsDependencyInjection(CreateIColorConverter());
}

std::unique_ptr<IColors> LibMiniSteckBuilder::CreateIColorsDependencyInjection(std::unique_ptr<IColorConverter> colorConverter)
{
    return std::make_unique<Colors>(std::move(colorConverter));
}

std::unique_ptr<IColorConverter> LibMiniSteckBuilder::CreateIColorConverter()
{
    return std::make_unique<ColorConverter>();
}
std::unique_ptr<IMinisteck> LibMiniSteckBuilder::CreateIMinisteck(const std::filesystem::path &path, std::function<void(const IMinisteck &,bool)> hasImageFile)
{
    return CreateIMinisteckDependencyInjection(path,hasImageFile, CreateIColors(), CreateIQuantize()
                                               , CreateIScaledOutputImage()
                                               , CreateIRandVorm()
                                               , CreateIMinisteckVormen());
}


std::unique_ptr<IMinisteck> LibMiniSteckBuilder::CreateIMinisteckDependencyInjection(const std::filesystem::path &path, std::function<void (const IMinisteck &, bool)> hasImageFile
                                                                  , std::unique_ptr<IColors> colors
                                                                  , std::unique_ptr<IQuantize> quantize
                                                                  , std::unique_ptr<IScaledOutputImage> scaledOuputImage
                                                                  , std::unique_ptr<IRandVorm> randvorm
                                                                  , std::unique_ptr<IMinisteckVormen> ministeckVormen
                                                                  )
{
    return std::make_unique<Ministeck>(path, hasImageFile, std::move(colors), std::move(quantize), std::move(scaledOuputImage), std::move(randvorm),
            std::move(ministeckVormen));
}

std::unique_ptr<IQuantize> LibMiniSteckBuilder::CreateIQuantize()
{
    return std::make_unique<Quantize>();
}

std::unique_ptr<IScaledOutputImage> LibMiniSteckBuilder::CreateIScaledOutputImage()
{
    return std::make_unique<ScaledOutputImage>();
}

std::unique_ptr<IRandVorm> LibMiniSteckBuilder::CreateIRandVorm()
{
    return std::make_unique<RandVorm>();
}

std::unique_ptr<IMinisteckVormen> LibMiniSteckBuilder::CreateIMinisteckVormen()
{
    return std::make_unique<MinisteckVormen>();
}
