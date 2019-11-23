#pragma once

#include <opencv2/core/mat.hpp>
#include "image_tools/opacity.hpp"

namespace kerashare::image_tools
{
class Opacitity
{
    Opacitity(float opacity);
};

class ImageManipulator
{
public:
    ImageManipulator(const cv::Mat& image) : image_(image.clone()) {}

    ImageManipulator& translate(int offsetx, int offsety);
    ImageManipulator& blur(float sigma);
    ImageManipulator& setOpacity(Opacity opacity);

    cv::Mat get();

private:
    cv::Mat image_;
};



}