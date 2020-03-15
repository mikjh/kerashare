#include "kerashare/kerashare.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

#include "processing/manipulator.hpp"
#include "processing/superimpose.hpp"

namespace kerashare
{
KerashareEvent createEvent(int event, int x, int y, int flags)
{
    return { event, cv::Point2i {x,y}, flags };
}

std::ostream& operator<<(std::ostream& os, const KerashareEvent& kerashare_event)
{
    if (kerashare_event.event == cv::EVENT_LBUTTONDOWN)
    {
        os << "down event at: ";
    }
    else if (kerashare_event.event == cv::EVENT_LBUTTONUP)
    {
        os << "up event at: ";
    }
    os << "(" << kerashare_event.position.x << "," << kerashare_event.position.y << ")" << std::endl;
    return os;
}

Kerashare::Kerashare(cv::Mat image) : image_{ image.clone() } { images_.push_back({ 1,image.clone() }); }

void Kerashare::registerEvent(KerashareEvent kerashare_event)
{
    if (kerashare_event.event == cv::EVENT_MOUSEMOVE)
    {
        if (l_button_down_)
        {
            auto diff = mouseClickDiff(kerashare_event);
        
            ::kerashare::processing::ImageManipulator image_manipulator(image_);
            images_.push_back(image_manipulator
                .blur(1)
                .translate(diff.x, diff.y)
                .setOpacity(0.1)
                .get());

            cv::imshow("kerashare_test_image", getProcessedImage());
            images_.pop_back();
        }
        return;
    }

    events_.push_back(std::move(kerashare_event));
    if (kerashare_event.event == cv::EVENT_LBUTTONDOWN)
    {
        l_button_down_ = true;
    }
    if (kerashare_event.event == cv::EVENT_LBUTTONUP)
    {
        l_button_down_ = false;
        auto diff = mouseClickDiff();
        ::kerashare::processing::ImageManipulator image_manipulator(image_);
        images_.push_back(image_manipulator
            .blur(1)
            .translate(diff.x, diff.y)
            .setOpacity(0.1)
            .get());
        cv::imshow("kerashare_test_image", getProcessedImage());
    }
    if (kerashare_event.event == cv::EVENT_MOUSEWHEEL)
    {
        auto diff = mouseClickDiff();
        ::kerashare::processing::ImageManipulator image_manipulator(image_);
        images_.back().weight *= kerashare_event.flags > 0 ? 1.2 : (1.0/1.2);
        cv::imshow("kerashare_test_image", getProcessedImage());
    }
}

cv::Point2i Kerashare::mouseClickDiff(const KerashareEvent& kerashare_event)
{
    if (events_.size() == 0)
        return 0;

    return kerashare_event.position - events_.back().position;
}

cv::Point2i Kerashare::mouseClickDiff()
{
    if (events_.size() <= 1)
        return 0;

    auto it = events_.rbegin();
    auto it_newest_event = it++;

    return it_newest_event->position - it->position;
}

cv::Mat Kerashare::getProcessedImage()
{
    return processing::superimpose(images_.begin(), images_.end());
}

void mouseCallback(int event, int x, int y, int flags, void* userdata)
{
    auto* kerashare_context = reinterpret_cast<Kerashare*>(userdata);

    auto kerashare_event = createEvent(event, x, y, flags);
    
    if(event != cv::EVENT_MOUSEMOVE)
        std::cout << kerashare_event << '\n';

    kerashare_context->registerEvent(kerashare_event);
}
}
