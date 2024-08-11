#include "shared/Hello.h"  // 包含 Hello 类的声明头文件，路径为 "shared/Hello.h"

int main(int argc, char *argv[])
{
    // 创建 Hello 类的一个对象 hi
    Hello hi;

    // 调用 hi 对象的 print 方法，打印消息 "Hello Shared Library!"
    hi.print();

    // 返回 0 表示程序成功结束
    return 0;
}
