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

    // 转换为 HSV 色彩空间
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);

    // // 分离颜色通道
    // vector<Mat> hsv_channels;
    // split(hsv, hsv_channels);

    // // 分离色相、饱和度和亮度通道
    // Mat hue = hsv_channels[0];
    // Mat saturation = hsv_channels[1];
    // Mat value = hsv_channels[2];

    // 定义苹果的颜色范围 (HSV)
    Scalar lower_red1(0, 150, 72);
    Scalar upper_red1(20, 255, 255);
    Scalar lower_red2(90, 65, 0);
    Scalar upper_red2(179, 255, 255);
    // Scalar lower_yellow(20, 100, 100);
    // Scalar upper_yellow(30, 255, 255);

    // // 生成掩码
    // Mat mask_red1, mask_red2, mask_yellow, mask;
    // inRange(hue, lower_red1[0], upper_red1[0], mask_red1);
    // inRange(hue, lower_red2[0], upper_red2[0], mask_red2);
    // // inRange(hue, lower_yellow[0], upper_yellow[0], mask_yellow);

    Mat mask1, mask2, mask;
    inRange(hsv, lower_red1, upper_red1, mask1); // 红色范围1
    inRange(hsv, lower_red2, upper_red2, mask2); // 红色范围2


    // 合并红色和黄色区域的掩码
    mask = (mask1 | mask2);

    // // 在饱和度和亮度通道中应用掩码以减少背景噪声
    // Mat masked_saturation, masked_value;
    // bitwise_and(saturation, saturation, masked_saturation, mask);
    // bitwise_and(value, value, masked_value, mask);

    // 二值化
    Mat binary;
    threshold(mask, binary, 0, 255, THRESH_BINARY);

    // // 自适应二值化
    // Mat adaptive_binary;
    // adaptiveThreshold(mask, adaptive_binary, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

    // 滤波 - 使用高斯滤波器去除噪声
    Mat blurred;
    GaussianBlur(binary, blurred, Size(3, 3), 0);

    // // 边缘检测 (Canny)
    // Mat edges;
    // Canny(blurred, edges, 100, 200); // 100和200为低阈值和高阈值

    // 形态学运算，开运算（去除噪点），闭运算（填补孔洞）
    Mat morph_open, morph_close;
    Mat kernel_open = getStructuringElement(MORPH_ELLIPSE, Size(25, 25));
    morphologyEx(blurred, morph_open, MORPH_OPEN, kernel_open);
    Mat kernel_close = getStructuringElement(MORPH_ELLIPSE, Size(115, 115));
    morphologyEx(morph_open, morph_close, MORPH_CLOSE, kernel_close);

    // // 膨胀操作以增强形状的完整性
    // Mat dilated;
    // Mat dilation_kernel = getStructuringElement(MORPH_ELLIPSE, Size(15, 15)); // 调整核大小以适应你的图像
    // dilate(morph_close, dilated, dilation_kernel);

     // 添加腐蚀操作以去除小的白色区域
    Mat eroded;
    Mat erosion_kernel = getStructuringElement(MORPH_ELLIPSE, Size(10, 10)); // 可以调整内核大小
    erode(morph_close, eroded, erosion_kernel);

    // 查找轮廓
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(eroded, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 使用掩码提取苹果区域
    Mat result;
    bitwise_and(image, image, result, eroded);

    // 轮廓面积筛选
    double min_area = 1000; 
    double max_area = 100000; 

    // 几何约束筛选目标轮廓并绘制外接矩形
    for (size_t i = 0; i < contours.size(); i++) 
    {
        double area = contourArea(contours[i]);
        Rect bounding_rect = boundingRect(contours[i]);
        double aspect_ratio = (double)bounding_rect.width / bounding_rect.height;

        if (area > min_area && area < max_area && aspect_ratio > 0.5 && aspect_ratio < 2.0) 
        {
            rectangle(result, bounding_rect, Scalar(0, 255, 0), 2);
        }
    }

    // 显示结果图像
    imshow("Original Image", image);
    imshow("mask",mask);
    // imshow("binary",binary);
    // imshow("adaptive_binary", adaptive_binary);
    imshow("Blurred", blurred);
    // imshow("edges",edges);
    imshow("Morph Open", morph_open);
    imshow("Morph Close", morph_close);
    imshow("Eroded", eroded);
    imshow("Apple Detection", result);
    waitKey(0);

    return 0;
}