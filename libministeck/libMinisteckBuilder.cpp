#include "inc/libMinisteckBuilder.h"
#include "Colors.h"
#include "ColorConverter.h"
#include "Ministeck.h"

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
    return std::make_unique<Ministeck>(path, hasImageFile);
}
