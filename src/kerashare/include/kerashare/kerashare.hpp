#pragma once
#include <opencv2/opencv.hpp>

namespace kerashare
{

struct KerashareEvent
{
    int event;
    cv::Point2i position;
    int flags;
};
KerashareEvent createEvent(int event, int x, int y, int flags);

class Kerashare
{
public:
    Kerashare() = default;
    ~Kerashare() = default;

    void registerEvent(KerashareEvent kerashare_event);
    cv::Point2i mouseClickDiff();

private:
    std::list<KerashareEvent> events_;
};
void mouseCallback(int event, int x, int y, int flags, void* userdata);
} // namespace Kerashare
