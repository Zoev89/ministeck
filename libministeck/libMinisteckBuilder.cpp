#include "inc/libMinisteckBuilder.h"
#include "Colors.h"
#include "Ministeck.h"

LibMiniSteckBuilder::LibMiniSteckBuilder()
{

}

std::unique_ptr<IColors> LibMiniSteckBuilder::CreateIColors()
{
    return std::make_unique<Colors>();

}

std::unique_ptr<IMinisteck> LibMiniSteckBuilder::CreateIMinisteck(const std::filesystem::path &path, std::function<void(bool)> hasImageFile)
{
    return std::make_unique<Ministeck>(path, hasImageFile);
}
