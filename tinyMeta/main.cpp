#include <type_traits>
#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "base.h"

template <typename T, typename R>
void func(T &a, R b)
{
    std::cout << "func(T)" << std::endl;
}

// 属于模板重载吧
template <typename T, typename R>
void func(T const &a, R b)
{
    std::cout << "func(T const)" << std::endl;
}

template <typename T, typename kanon::enable_if_t<std::is_integral<T>::value>>
void foo(T &a)
{
}

template <typename T, typename S,
          typename = typename kanon::enable_if_t<
              kanon::conjunction<kanon::is_same<T, int>, kanon::is_same<S, float>>::value>>
void moo(T a, S b)
{
}

int main()
{
    return 0;
}
