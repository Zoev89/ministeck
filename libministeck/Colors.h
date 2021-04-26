#include "IColors.h"

class Colors: public IColors
{
public:
    Colors();
    virtual ~Colors()=default;
    virtual std::vector<Color> GetColors() override;
private:
    std::vector<Color> m_colors;
};
