#include "IColors.h"
#include <memory>

class IColorConverter;

class Colors: public IColors
{
public:
    explicit Colors(std::unique_ptr<IColorConverter> colorConverter) ;
    virtual ~Colors()=default;
    virtual std::vector<Color> GetColors() override;
private:
    std::vector<Color> m_colors;
    std::unique_ptr<IColorConverter> m_colorConverter;
};
