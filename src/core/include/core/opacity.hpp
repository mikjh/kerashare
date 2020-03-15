#pragma once

#include <opencv2/core/mat.hpp>

namespace kerashare::core
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