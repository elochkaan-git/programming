#include <opencv2/opencv.hpp>
 
int main( int argc, char** argv ) {
    // Read image 
    cv::Mat src = cv::imread("..\\threshold.png", cv::IMREAD_GRAYSCALE); 
    cv::Mat dst; 
    
    // Basic threhold example 
    cv::threshold(src,dst,0, 255, cv::THRESH_BINARY); 
    cv::imwrite("..\\opencv-threshold-example.jpg", dst); 
    
    // Thresholding with maxval set to 128
    cv::threshold(src, dst, 0, 128, cv::THRESH_BINARY); 
    cv::imwrite("..\\opencv-thresh-binary-maxval.jpg", dst); 
    
    // Thresholding with threshold value set 127 
    cv::threshold(src,dst,127,255, cv::THRESH_BINARY); 
    cv::imwrite("..\\opencv-thresh-binary.jpg", dst); 
    
    // Thresholding using THRESH_BINARY_INV 
    cv::threshold(src,dst,127,255, cv::THRESH_BINARY_INV); 
    cv::imwrite("..\\opencv-thresh-binary-inv.jpg", dst); 
    
    // Thresholding using THRESH_TRUNC 
    cv::threshold(src,dst,127,255, cv::THRESH_TRUNC); 
    cv::imwrite("..\\opencv-thresh-trunc.jpg", dst); 
    
    // Thresholding using THRESH_TOZERO 
    cv::threshold(src,dst,127,255, cv::THRESH_TOZERO); 
    cv::imwrite("..\\opencv-thresh-tozero.jpg", dst); 
    
    // Thresholding using THRESH_TOZERO_INV 
    cv::threshold(src,dst,127,255, cv::THRESH_TOZERO_INV); 
    cv::imwrite("..\\opencv-thresh-to-zero-inv.jpg", dst); 
} 