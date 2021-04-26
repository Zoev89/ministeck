#ifndef LIBMINISTECKBUILDER_H
#define LIBMINISTECKBUILDER_H
#include <memory>

class IColors;

class LibMiniSteckBuilder
{
public:
    LibMiniSteckBuilder();
    static std::unique_ptr<IColors> CreateIColors();
};

#endif // LIBMINISTECKBUILDER_H
