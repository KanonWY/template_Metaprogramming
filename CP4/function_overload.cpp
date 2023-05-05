#include <iostream>

/**
 *  优先在normal function中查找，
 *  然后在模板中查找
 *  模板中不行，尝试在normal function中类型转换匹配
*/

void foo(int a, int b = 200)
{
    std::cout << "foo(int a, int b = 200)" << std::endl;
}

void foo(int a)
{
    std::cout << "foo(int a)" << std::endl;
}

template <typename T>
void foo(T a)
{
    std::cout << "foo(T a)" << std::endl;
}

template <typename T, typename S>
void foo(T a, S b)
{
    std::cout << "foo(T a, S b)" << std::endl;
}

int main()
{
    foo(30, 20);
    return 0;
}