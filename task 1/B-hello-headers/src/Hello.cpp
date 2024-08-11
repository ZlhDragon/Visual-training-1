#include <iostream>  // 包含标准输入输出流库，用于输出信息

#include "Hello.h"   // 包含 Hello 类的声明头文件

// 实现 Hello 类的 print 方法
void Hello::print()
{
    // 使用 std::cout 输出 "Hello Headers!" 字符串，并换行
    std::cout << "Hello Headers!" << std::endl;
}
