#include "image_tools/image_tools.hpp"
#include <opencv2/imgproc.hpp>
#include <exception>

#include <iostream>

namespace kerashare::image_tools
{
ImageManipulator& ImageManipulator::translate(int offsetx, int offsety) 
{
    const cv::Mat translation_mat = (cv::Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);

    cv::warpAffine(image_, image_, translation_mat, image_.size());
    return *this;
}

ImageManipulator& ImageManipulator::blur(float sigma)
{
    try
    {
        cv::GaussianBlur(image_, image_, cv::Size{3,3}, sigma);
    }
    catch (const std::exception& err)
    {
        std::cout << err.what();
        throw;
    }

    return *this;
}

ImageManipulator& ImageManipulator::setOpacity(Opacity opacity)
{
    image_ *= opacity;
    return *this;
}

cv::Mat ImageManipulator::get()
{
    return image_.clone();
}
}
