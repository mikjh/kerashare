#include "processing/manipulator.hpp"
#include <opencv2/imgproc.hpp>
#include <exception>

#include <iostream>

namespace kerashare::processing
{
ImageManipulator& ImageManipulator::translate(int offsetx, int offsety) 
{
    const cv::Mat translation_mat = (cv::Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);

    cv::warpAffine(image_.image, image_.image, translation_mat, image_.image.size());
    return *this;
}

ImageManipulator& ImageManipulator::blur(float sigma)
{
    try
    {
        cv::GaussianBlur(image_.image, image_.image, cv::Size{3,3}, sigma);
    }
    catch (const std::exception& err)
    {
        std::cout << err.what();
        throw;
    }

    return *this;
}

ImageManipulator& ImageManipulator::setOpacity(core::Opacity opacity)
{
    image_.weight = opacity;
    return *this;
}

core::Image ImageManipulator::get()
{
    return core::clone(image_);
}
}
