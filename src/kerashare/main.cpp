#include <iostream>
#include <opencv2/opencv.hpp>

#include <vector>
#include <string>

#include "processing/manipulator.hpp"
#include "processing/superimpose.hpp"

std::vector<std::string> getArgs(int argc, char** argv)
{
    std::vector<std::string> command_line_arguments;

    for (int i = 1; i < argc; ++i)
    {
        command_line_arguments.push_back(argv[i]);
    }
    return command_line_arguments;
}

void mouseCallback (int event, int x, int y, int flags, void* userdata)
{
    cv::Point2i* prev_pos = reinterpret_cast<cv::Point2i*>(userdata);
    if (event == cv::EVENT_LBUTTONDOWN)
    {
        std::cout << "down event at: ";
        std::cout << "(" << x << "," << y << ")" << std::endl;
    }
    else if (event == cv::EVENT_LBUTTONUP)
    {
        std::cout << "up event at: ";
        std::cout << "(" << x << "," << y << ")" << std::endl;
        auto diff = *prev_pos - cv::Point2i{ x,y };
        std::cout << "(" << diff.x << "," << diff.y << ")" << std::endl;
    }

    *prev_pos = cv::Point2i{ x,y };
}

int main(int argc, char** argv)
{
    auto args = getArgs(argc, argv);
    auto image_path_it = std::find(args.begin(), args.end(), "--image_path");
    
    if (image_path_it == args.end())
    {
        std::cout << "usage: DisplayImage.out --image_path <Image_Path>\n";
        return -1;
    }

    auto image_path = *(++image_path_it);

    const cv::Mat image = cv::imread(image_path, 1 );

    if (!image.data)
    {
        std::cout << "Failed to load image data, exiting!\n";
        return -1;
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);

    cv::Point2i position{ 0,0 };

    cv::setMouseCallback("Display Image", mouseCallback, &position);

    imshow("Display Image", image);
    cv::waitKey(0);

    ::kerashare::processing::ImageManipulator imageManipulator(image);

    auto smoothedImage = imageManipulator
        .blur(1)
        .setOpacity(0.9)
        .get();

    auto processedImage1 = imageManipulator
        .translate(0, -10)
        .setOpacity(0.1)
        .get();

    auto processedImage2 = imageManipulator
        .translate(0, 20)
        .setOpacity(0.2)
        .get();

    imshow("Display Image", static_cast<cv::Mat>(smoothedImage));
    
    cv::waitKey(0);
    imshow("Display Image2", static_cast<cv::Mat>(processedImage1));
    cv::waitKey(0);
    imshow("Display Image3", static_cast<cv::Mat>(processedImage2));
    cv::waitKey(0);
    imshow("Display Image4", kerashare::processing::superimpose(smoothedImage, processedImage1, processedImage2));
    cv::waitKey(0);
    return 0;
}