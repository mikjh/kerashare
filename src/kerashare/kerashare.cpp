#include "kerashare/kerashare.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

namespace kerashare
{
KerashareEvent createEvent(int event, int x, int y, int flags)
{
    return { event, cv::Point2i {x,y}, flags };
}

void Kerashare::registerEvent(KerashareEvent kerashare_event)
{
    if (kerashare_event.event != cv::EVENT_MOUSEMOVE)
        events_.push_back(std::move(kerashare_event));
}

cv::Point2i Kerashare::mouseClickDiff()
{
    if (events_.size() <= 1)
        return 0;

    auto it = events_.rbegin();
    auto it_newest_event = it++;

    return it_newest_event->position - it->position;
}

void mouseCallback(int event, int x, int y, int flags, void* userdata)
{
    auto* kerashare_context = reinterpret_cast<Kerashare*>(userdata);

    auto kerashare_event = createEvent(event, x, y, flags);

    kerashare_context->registerEvent(kerashare_event);

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::cout << "down event at: ";
        std::cout << "(" << x << "," << y << ")" << std::endl;
    }
    else if (event == cv::EVENT_LBUTTONUP)
    {
        std::cout << "up event at: ";
        std::cout << "(" << x << "," << y << ")" << std::endl;
        auto diff = kerashare_context->mouseClickDiff();
        std::cout << "(" << diff.x << "," << diff.y << ")" << std::endl;
    }
}
}
