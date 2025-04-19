#include "image.hpp"

int main() {
    cv::Mat image = cv::imread(".\\paladine.jpg");
    std::string hash_before = hash_image(image);
    std::cout << "Hash before changes: " << hash_before << '\n';
    change_pixel(image);
    std::string hash_after = hash_image(image);
    std::cout << "Hash after changes:  " << hash_after << "\n\n";

    if(hash_before != hash_after) std::cout << "Image has been changed";
    else std::cout << "Image hasn't been changed";

    return 0;
}