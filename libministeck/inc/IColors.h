#include <vector>
#include <string>

struct Color
{
    int colorNummer;
    std::string naam;
    int r;
    int g;
    int b;
};

class IColors
{
public:
    virtual ~IColors() = default;
    virtual std::vector<Color> GetColors() = 0;
protected:
    IColors() = default;
};
