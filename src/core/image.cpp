#include "core/image.hpp"

namespace kerashare::core
{
Image::operator cv::Mat()
{
    return image;
}

Image clone(Image image)
{
    return { image.weight, image.image.clone() };
}
}
