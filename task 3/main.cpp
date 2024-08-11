#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// 存储用户点击的四个点
vector<Point2f> points;
const int num_points = 4; // 需要的特征点数量

// 鼠标回调函数，用于标记特征点
void mouseCallback(int event, int x, int y, int, void*) 
{
    if (event == EVENT_LBUTTONDOWN && points.size() < num_points) 
    {
        points.push_back(Point2f(x, y)); // 记录点击的点
        cout << "选中的点: (" << x << ", " << y << ")" << endl;
    }
}

int main() 
{
    // 读取图像
    Mat image = imread("/home/zlh/code/Visual Training 1/task 3/car.png");
    if (image.empty())
    {
        cout << "加载图像出错" << endl;
        return -1;
    }

    // 创建窗口并设置鼠标回调函数
    namedWindow("Image");
    setMouseCallback("Image", mouseCallback);

    // 主循环，等待用户选择点
    while (true) 
    {
        Mat img_copy = image.clone(); // 克隆图像以便绘制标记
        for (size_t i = 0; i < points.size(); i++) 
        {
            circle(img_copy, points[i], 5, Scalar(0, 0, 255), -1); // 在图像上绘制红色圆圈
        }
        imshow("Image", img_copy);
        char key = (char)waitKey(1);
        if (key == 27) // ESC 键退出
            break;
        if (points.size() == num_points) // 如果选择了4个点
            break;
    }

    // 确保选了足够的点
    if (points.size() == num_points) 
    {
        // 定义目标点，定义透视变换后的图像大小和位置
        vector<Point2f> dst_points = { Point2f(0, 0), Point2f(300, 0), Point2f(300, 100), Point2f(0, 100) };

        // 获取透视变换矩阵并应用透视变换
        Mat M = getPerspectiveTransform(points, dst_points);
        Mat warped;
        warpPerspective(image, warped, M, Size(300, 100)); // 应用透视变换

        // 转换到 HSV 色彩空间
        Mat hsv;
        cvtColor(warped, hsv, COLOR_BGR2HSV);

        // 定义车牌的颜色范围 (HSV)
        Scalar lower_plate(0, 0, 0);
        Scalar upper_plate(180, 255, 100);

        // 生成掩码
        Mat mask;
        inRange(hsv, lower_plate, upper_plate, mask);

        // 提取车牌区域
        Mat plate;
        bitwise_and(warped, warped, plate, mask);

        // 转换为灰度图像
        Mat gray_plate;
        cvtColor(plate, gray_plate, COLOR_BGR2GRAY);

        // // 二值化
        // Mat binary_plate;
        // threshold(gray_plate, binary_plate, 0, 255, THRESH_BINARY_INV + THRESH_OTSU);

        Mat adaptive_binary_plate;
        adaptiveThreshold(gray_plate, adaptive_binary_plate, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 25, 2);

        // 显示结果
        imshow("Warped Plate", warped);
        imshow("Plate Mask", mask);
        imshow("Extracted Plate", plate);
        // imshow("Binary Plate", binary_plate);
        imshow("Adaptive Binary Plate", adaptive_binary_plate);
        waitKey(0);
    } else 
    {
        cout << "没有选够四个点。请准确选择4个点。" << endl;
    }

    return 0;
}
