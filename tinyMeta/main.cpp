#include <type_traits>
#include <iostream>
#include <vector>
#include <string>
#include "base_2.h"
#include "base_3.h"

struct widget
{
    widget() {}
    widget(int) {}
};

struct Test
{
    Test() = default;
    Test(const Test &rhs) = delete;
};

using namespace kanon;

bool getBool()
{
    return true;
}

int testGetFuncRetType()
{
    auto foo = []() -> double {
        return 200;
    };

    getRet_t<decltype(foo)> a;

    std::cout << std::is_same_v<std::decay_t<decltype(a)>, int> << std::endl;

    return 0;
}

struct Mai
{
    inline static int a{20};
    int b{30};
};

int main()
{
    auto b = &Mai::a;
    auto mm = &Mai::b;

    return 0;
}
