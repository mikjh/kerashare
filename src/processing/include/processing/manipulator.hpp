#pragma once

#include <opencv2/core/mat.hpp>
#include "core/all.hpp"

namespace kerashare::processing
{

class ImageManipulator
{
public:
    ImageManipulator(const cv::Mat& image) : image_{ 1, image.clone() } {}

    ImageManipulator& translate(int offsetx, int offsety);
    ImageManipulator& blur(float sigma);
    ImageManipulator& setOpacity(core::Opacity opacity);

    core::Image get();

private:
    core::Image image_;
};



}