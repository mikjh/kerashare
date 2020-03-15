#pragma once

#include <type_traits>
#include <opencv2/opencv.hpp>

#include <core/image.hpp>

namespace kerashare::processing
{

template<typename... Images>
cv::Mat superimpose(Images&&... images);


// inline implementation
template<typename... Images>
cv::Mat superimpose(Images&&... images)
{
    static_assert((std::is_same_v<std::decay_t<Images>, core::Image> && ...), "Input types need to be core::Image!");

    const float total_weight = (images.weight + ...);
    auto normalize_weight = [total_weight](float& weight) { weight /= total_weight; };
    
    (normalize_weight(images.weight), ...);

    return ((images.weight * images.image) + ...);
}

}