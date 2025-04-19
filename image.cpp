#include "image.hpp"

std::vector<uchar> load_image(cv::Mat& src) {
    std::vector<uchar> buff;
    std::vector<int> params = {};
    cv::imencode(".jpg", src, buff, params);

    return buff;
}

std::string vectohexstr(std::vector<uchar> data) {

    std::map<std::string, unsigned char> num = {
        {"0", '0'},
        {"1", '1'},
        {"2", '2'},
        {"3", '3'},
        {"4", '4'},
        {"5", '5'},
        {"6", '6'},
        {"7", '7'},
        {"8", '8'},
        {"9", '9'},
        {"10", 'a'},
        {"11", 'b'},
        {"12", 'c'},
        {"13", 'd'},
        {"14", 'e'},
        {"15", 'f'},
    };
    std::string result = "";

    for(const uchar& each : data) {
        std::string first = std::to_string(each / 16), second =std::to_string(each % 16);
        result += num[first];
        result += num[second];
    }

    return result;
}

std::string hash_image(cv::Mat& src) {
    std::vector<uchar> image = load_image(src);
    std::vector<uchar> data;

    unsigned char md[SHA256_DIGEST_LENGTH];
    SHA256(&image[0], image.size(), md);
    for(unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++) data.push_back(md[i]);
    
    return vectohexstr(data);
}

void change_pixel(cv::Mat src) {
    src.at<cv::Vec3b>(rand() % src.rows, rand() % src.cols)[rand() % 3] = rand() % 256;
    cv::imwrite(".\\changed_image.jpg", src);
}
