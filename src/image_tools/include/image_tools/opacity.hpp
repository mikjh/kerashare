#pragma once

#include <opencv2/core/mat.hpp>

namespace kerashare::image_tools
{

class Opacity
{
public:
    Opacity(float opacity);

    operator float();

private:
    float opacity_;
};

}