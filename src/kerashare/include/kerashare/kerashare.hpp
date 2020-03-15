#pragma once
#include <opencv2/opencv.hpp>

#include "core/image.hpp"

namespace kerashare
{

struct KerashareEvent
{
    int event;
    cv::Point2i position;
    int flags;
};
KerashareEvent createEvent(int event, int x, int y, int flags);

std::ostream& operator<<(std::ostream& os, const KerashareEvent& kerashare_event);

class Kerashare
{
public:
    Kerashare(cv::Mat image);
    ~Kerashare() = default;

    void registerEvent(KerashareEvent kerashare_event);
    cv::Mat getProcessedImage();

private:
    cv::Point2i mouseClickDiff();
    cv::Point2i Kerashare::mouseClickDiff(const KerashareEvent& kerashare_event);
    std::list<KerashareEvent> events_;
    cv::Mat image_;
    std::list<core::Image> images_;
    bool l_button_down_ = false;
};
void mouseCallback(int event, int x, int y, int flags, void* userdata);
} // namespace kerashare
