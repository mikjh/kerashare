#pragma once

#include <opencv2/core/mat.hpp>

namespace kerashare::core
{
struct Image
{
    float weight;
    cv::Mat image;

    operator cv::Mat();
};

Image clone(Image image);
}