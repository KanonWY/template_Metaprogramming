#ifndef __BASE_5__H__
#define __BASE_5__H__

#include <tuple>
#include <type_traits>

//https://blog.csdn.net/fl2011sx/article/details/128933496

/**
 *  动态访问tuple
 */

namespace kanon
{

class Base
{
public:
    virtual void f() const = 0;
};

class Ch1 : public Base
{
public:
    void f() const override
    {
    }
};

class Ch2 : public Base
{
public:
    void f() const override
    {
    }
};

template <typename... Args>
std::enable_if_t<std::conjunction_v<std::is_base_of<Base, Args>...>, void>
InvokeF(const std::tuple<Args...> &tup, size_t index)
{
}

} // namespace kanon

#endif
