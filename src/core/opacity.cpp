#pragma once

#include "core/opacity.hpp"
#include <iostream>

namespace kerashare::core
{
Opacity::Opacity(float opacity)
{
    if (opacity > 1.0F || opacity < 0.0F)
    {
        std::cout << 
            "opacity above limits, will clamp to edge in range [0,1]\n";
    }

    opacity_ = std::clamp(opacity, 0.0F, 1.0F);
}

Opacity::operator float()
{
    return opacity_;
}
}
