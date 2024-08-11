#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    // 读取图像
    Mat image = imread("/home/zlh/code/Visual Training 1/task 2/apple.png");
    if (image.empty())
    {
        cout << "Error loading image" << endl;// 如果图像未加载，输出错误信息
        return -1;
    }

    // 转换为灰度图像
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // 二值化
    Mat binary;
    threshold(gray, binary, 128, 255, THRESH_BINARY);

    // 自适应二值化
    Mat adaptive_binary;
    adaptiveThreshold(gray, adaptive_binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

    // 基于梯度的边缘检测 (Sobel)：对边缘进行初步检测，速度较快，但对噪声较敏感，精度有限
    Mat sobel_x, sobel_y, sobel;
    Sobel(gray, sobel_x, CV_16S, 1, 0, 3);// CV_16S: 16-bit signed output, 1: x方向梯度, 0: y方向梯度, 3: Sobel核大小
    Sobel(gray, sobel_y, CV_16S, 0, 1, 3);
    // 将 Sobel 计算得到的梯度图像转换为 8-bit 无符号整型图像
    convertScaleAbs(sobel_x, sobel_x);// 转换 x 方向的梯度图像
    convertScaleAbs(sobel_y, sobel_y);
    addWeighted(sobel_x, 0.5, sobel_y, 0.5, 0, sobel);// 将 x 方向和 y 方向的梯度图像合成

    // 基于梯度的边缘检测 (Canny)：高精度边缘检测，提供更好的边缘定位和噪声抑制，但计算复杂度较高。
    Mat canny_edges;
    Canny(gray, canny_edges, 100, 200);

    // 转换为 HSV 色彩空间
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);

    // 定义苹果的颜色范围 (HSV)
    Scalar lower_red1(0, 50, 50);
    Scalar upper_red1(10, 255, 255);
    Scalar lower_red2(160, 50, 50);
    Scalar upper_red2(180, 255, 255);

    // 生成掩码
    Mat mask1, mask2, color_edges;
    inRange(hsv, lower_red1, upper_red1, mask1);
    inRange(hsv, lower_red2, upper_red2, mask2);
    color_edges = mask1 | mask2;// 将两个掩码合并，得到最终的掩码

    // 使用掩码提取苹果区域
    Mat result;
    bitwise_and(image, image, result, color_edges);// 使用掩码从原图像中提取苹果区域

    // 查找轮廓
    vector<vector<Point>> contours;// 用于存储轮廓的向量
    vector<Vec4i> hierarchy;// 用于存储轮廓的层次结构
    findContours(color_edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);// 查找掩码中的轮廓

    // // 画外接矩形
    // for (size_t i = 0; i < contours.size(); i++) 
    // {
    //     Rect bounding_rect = boundingRect(contours[i]); // 获取每个轮廓的外接矩形
    //     rectangle(result, bounding_rect, Scalar(0, 255, 0), 2); // 绘制绿色矩形，框线宽度为 2 像素
    // }

    // 仅保留苹果区域图像
    Mat apple_area = Mat::zeros(image.size(), image.type());
    for (size_t i = 0; i < contours.size(); i++) {
        Rect bounding_rect = boundingRect(contours[i]);
        rectangle(apple_area, bounding_rect, Scalar(0, 255, 0), 2); // 绘制绿色矩形
    }

    // 显示结果图像
    imshow("Original Image", image);
    imshow("Apple Detection", result);
    // 显示图像
    imshow("Original Image", image);
    imshow("Binary Threshold", binary);
    imshow("Adaptive Threshold", adaptive_binary);
    imshow("Sobel Edge Detection", sobel);
    imshow("Canny Edge Detection", canny_edges);
    imshow("Color Edges Detection", color_edges);
    imshow("Apple Area", apple_area);
    waitKey(0);

    return 0;
}
