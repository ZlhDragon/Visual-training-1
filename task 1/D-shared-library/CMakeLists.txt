cmake_minimum_required(VERSION 3.5)

project(hello_library)

############################################################
# 创建一个库
############################################################

# 从库源文件生成共享库
add_library(hello_library SHARED 
    src/Hello.cpp
)
# 创建一个库的别名
add_library(hello::library ALIAS hello_library)

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
target_link_libraries(hello_binary
    PRIVATE 
        hello::library
)
