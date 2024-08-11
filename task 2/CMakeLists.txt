# 设置可以使用的最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(apple_detection)

# 设置 OpenCV 的路径
set(OpenCV_DIR /home/zlh/opencv-4.9.0/include/opencv2)

# 查找 OpenCV 包
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")#打印 OpenCV 头文件所在的目录，验证 CMake 是否正确找到 OpenCV 的包含目录
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")#打印将在项目中链接的库，确保链接的 OpenCV 库正确

# 包含 OpenCV 头文件目录
include_directories(${OpenCV_INCLUDE_DIRS})

# 添加源文件
add_executable(apple_detection main.cpp)

# 链接 OpenCV 库
target_link_libraries(apple_detection ${OpenCV_LIBS})
