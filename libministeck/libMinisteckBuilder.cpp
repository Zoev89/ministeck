#include "inc/libMinisteckBuilder.h"
#include "Colors.h"

LibMiniSteckBuilder::LibMiniSteckBuilder()
{

}

std::unique_ptr<IColors> LibMiniSteckBuilder::CreateIColors()
{
    return std::make_unique<Colors>();

}
