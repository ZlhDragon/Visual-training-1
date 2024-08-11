# 设置可以使用的最低 CMake 版本
cmake_minimum_required(VERSION 3.5)

# 设置项目名称
project (hello_headers)

# 创建一个源文件变量，包含所有要编译的 cpp 文件
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

# 使用上述源文件创建一个可执行文件
add_executable(hello_headers ${SOURCES})#可执行程序，源文件名

# 设置在构建命令中应包含的目录
# 编译时，这些目录将作为 -I/directory/path/ 选项被包含
target_include_directories(hello_headers
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)
