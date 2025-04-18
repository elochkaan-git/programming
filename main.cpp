#include <iostream>
#include <opencv2/opencv.hpp>
 
int main( int argc, char** argv ) {
    // Сообщение для отслеживания работы программы
    std::cout << "Start image processing..." << std::endl;

    // Считываем изображение для обработки 
    cv::Mat src = cv::imread("..\\threshold.png", cv::IMREAD_GRAYSCALE); 
    cv::Mat dst; 
    std::cout << "Read image..." << std::endl;

    // Базовый пример бинарной пороговой обработки 
    cv::threshold(src,dst,0, 255, cv::THRESH_BINARY); 
    cv::imwrite("..\\opencv-threshold-example.jpg", dst); 
    std::cout << "THRESH_BINARY..." << std::endl;
    
    // Пороговая обработка с maxval = 128
    cv::threshold(src, dst, 0, 128, cv::THRESH_BINARY); 
    cv::imwrite("..\\opencv-thresh-binary-maxval.jpg", dst); 
    std::cout << "THRESH_BINARY with maxval = 128..." << std::endl;
    
    // Пороговая обработка с порогом (threshold) = 127
    cv::threshold(src,dst,127,255, cv::THRESH_BINARY); 
    cv::imwrite("..\\opencv-thresh-binary.jpg", dst); 
    std::cout << "THRESH_BINARY with threshold..." << std::endl;
    
    // Обработка с использованием THRESH_BINARY_INV 
    cv::threshold(src,dst,127,255, cv::THRESH_BINARY_INV); 
    cv::imwrite("..\\opencv-thresh-binary-inv.jpg", dst); 
    std::cout << "THRESH_BINARY_INV..." << std::endl;
    
    // Обработка с использованием THRESH_TRUNC 
    cv::threshold(src,dst,127,255, cv::THRESH_TRUNC); 
    cv::imwrite("..\\opencv-thresh-trunc.jpg", dst); 
    std::cout << "THRESH_TRUNC..." << std::endl;
    
    // Обработка с использованием THRESH_TOZERO 
    cv::threshold(src,dst,127,255, cv::THRESH_TOZERO); 
    cv::imwrite("..\\opencv-thresh-tozero.jpg", dst); 
    std::cout << "THRESH_TOZERO..." << std::endl;
    
    // Обработка с использованием THRESH_TOZERO_INV 
    cv::threshold(src,dst,127,255, cv::THRESH_TOZERO_INV); 
    cv::imwrite("..\\opencv-thresh-to-zero-inv.jpg", dst);
    std::cout << "THRESH_TOZERO_INV..." << std::endl;
    
    std::cout << "End..." << std::endl;
} 