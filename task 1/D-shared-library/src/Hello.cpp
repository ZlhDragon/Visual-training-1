#include <iostream>  // 包含标准输入输出流库，用于输出信息

#include "shared/Hello.h"  // 包含 Hello 类的声明头文件，路径为 "shared/Hello.h"

void Hello::print()
{
    // 使用 std::cout 输出 "Hello Shared Library!" 字符串，并换行
    std::cout << "Hello Shared Library!" << std::endl;
}
