#include "image_tools/image_tools.hpp"
#include <opencv2/imgproc.hpp>

namespace kerashare::image_tools
{
cv::Mat translate_image(const cv::Mat& image, int offsetx, int offsety) {
    const cv::Mat translation_mat = (cv::Mat_<double>(2, 3) << 1, 0, offsetx, 0, 1, offsety);
    cv::Mat translated_image = image.clone();

    warpAffine(translated_image, translated_image, translation_mat, translated_image.size());
    return translated_image;
}
}
