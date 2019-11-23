#pragma once

#include <opencv2/core/mat.hpp>

namespace image_tools
{
// simple function to translate a function with a two dim offset
cv::Mat translate_image(const cv::Mat& image, int offsetx, int offsety);
}