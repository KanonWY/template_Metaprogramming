#include <iostream>

template <typename T>
struct foo
{
    static T value;
};

template <typename T>
T foo<T>::value = 0;

template <>
int foo<int>::value = 200;

int main()
{
    foo<double> a, b;
    foo<int> c;
    std::cout << a.value << std::endl;
    std::cout << c.value << std::endl;
    a.value = 20000;
    std::cout << b.value << std::endl;
    std::cout << c.value << std::endl;
    return 0;
}