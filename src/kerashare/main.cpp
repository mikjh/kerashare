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

    cv::Mat imageTranslated = kerashare::image_tools::translate_image(image, 0, -10);
   
    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    cv::waitKey(0);
    imshow("Display Image", imageTranslated);
    cv::waitKey(0);
    imshow("Display Image", 0.9*image + 0.1*imageTranslated);
    cv::waitKey(0);
    return 0;
}