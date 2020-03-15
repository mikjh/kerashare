#pragma once
#include <algorithm>
#include <numeric>
#include <type_traits>

#include <opencv2/opencv.hpp>
#include <core/image.hpp>

namespace kerashare::processing
{

template<typename Iterator>
cv::Mat superimpose(Iterator begin, Iterator end)
{
    const float total_weight = std::accumulate(begin, end, 0.F, 
        [](float accumulated, const core::Image& image) {
            return accumulated + image.weight;
        }
    );

    cv::Mat superimposed_image = std::accumulate(begin, end, cv::Mat{},
        [total_weight](cv::Mat accumulated, const core::Image& image) {
            return accumulated + image.weight * image.image / total_weight;
        }
    );

    return superimposed_image;
}

}