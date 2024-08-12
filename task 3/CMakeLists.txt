#CMake 最低版本要求：
cmake_minimum_required(VERSION 3.10)

#项目名称
project(license_plate_detection)

#查找 OpenCV 包：
find_package(OpenCV REQUIRED)

#包含 OpenCV 的头文件目录：
include_directories(${OpenCV_INCLUDE_DIRS})

#添加可执行文件：
add_executable(license_plate_detection main.cpp)

#链接 OpenCV 库：
target_link_libraries(license_plate_detection ${OpenCV_LIBS})
