cmake_minimum_required(VERSION 3.5)

project(hello_library)

############################################################
# 创建一个库
############################################################

# 从库源文件生成静态库
add_library(hello_library STATIC 
    src/Hello.cpp
)

target_include_directories(hello_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)


############################################################
# 创建一个可执行文件
############################################################

# 使用上述源文件添加一个可执行文件
add_executable(hello_binary 
    src/main.cpp
)

# 将新的 hello_library 目标链接到 hello_binary 目标
target_link_libraries( hello_binary
    PRIVATE 
        hello_library
)
