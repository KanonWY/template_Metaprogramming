#include <iostream>

template <typename T, typename S>
struct MainTemp
{
};

template <typename T>
struct MainTemp<T, int>
{
};

//default template arguments may not be used in partial specializations
// template <typename T = int>          // T不能有默认模板参数
// struct MainTemp<T, double>
// {
// };

// template <typename T, typename S>
// struct MainTemp<int, S>
// {
// };

/**
 *  函数模板支持重载和全特化。但是不支持部分特化？
 *  TODO: 函数模板为什么不支持部分特化？
*/
// template <typename T, typename U>
// void func(T t, U u)
// {
//     std::cout << "Primary template called" << std::endl;
// }

// template <typename T>
// void func<T, int>(T t, int i)
// {
//     std::cout << "Partial specialization with int called" << std::endl;
// }

int main()
{
    return 0;
}