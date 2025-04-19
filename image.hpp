#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <map>
#include <random>

std::string hash_image(cv::Mat& src);
void change_pixel(cv::Mat src);

#endif