#include <iostream>
#include <opencv2/opencv.hpp>

#include <vector>
#include <string>

#include "image_tools/image_tools.hpp"

std::vector<std::string> getArgs(int argc, char** argv)
{
    std::vector<std::string> command_line_arguments;

    for (int i = 1; i < argc; ++i)
    {
        command_line_arguments.push_back(argv[i]);
    }
    return command_line_arguments;
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
    imshow("Display Image", image);
    cv::waitKey(0);

    ::kerashare::image_tools::ImageManipulator imageManipulator(image);

    cv::Mat smoothedImage = imageManipulator
        .blur(1)
        .get();

    cv::Mat processedImage = imageManipulator
        .translate(0, -10)
        .get();
   
    imshow("Display Image", smoothedImage);
    cv::waitKey(0);
    imshow("Display Image", processedImage);
    cv::waitKey(0);
    imshow("Display Image", 0.9*smoothedImage + 0.1*processedImage);
    cv::waitKey(0);
    return 0;
}