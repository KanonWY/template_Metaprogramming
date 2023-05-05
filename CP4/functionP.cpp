#include <iostream>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <map>

//模板类型推导，值传递，引用传递。

//值传递类型会衰变，数组会变成指针，并且删除CV限定符。

template <typename T>
std::enable_if_t<std::is_same_v<std::string, T>, void>
func(const T &value)
{
    std::cout << "string" << std::endl;
}

template <typename T>
std::enable_if_t<std::is_pointer_v<T>, void>
func(T value)
{
    std::cout << "pinter" << std::endl;
};

template <typename T>
std::enable_if_t<std::is_array_v<T>, void>
func(T value)
{
    std::cout << "arr" << std::endl;
};
//无法推导，因为值传递，const char[11]退化为了const char*满足enable_if的条件。
//func("99dkoakdoa");

//引用传递不会衰减
//（1） 传递常引用T const&
//（2） T &  当通过传递的参数作为返回值时 (例如，使用 out 或 inout 参数时)，必须使用非常量引用 (除非通过指针传递)

template <typename T>
void outR(T &arg)
{
    static_assert(!std::is_const<T>::value, "T is const!");
    static_assert(!std::is_reference_v<T>);
}

int outRTest()
{
    std::string a = "lplp";
    outR(a); //T reduce-> std::string
    return 0;
}

//此函数将永远无法被调用，因为，在模板类型推导时，有引用的实参会被视为无引用，他们的引用会被忽略。
//只有万能引用存在的时候，T才有可能被推导有引用。
template <typename T, typename = std::enable_if_t<std::is_reference_v<T>>>
void printT(T x)
{
    std::cout << "T reduce as ref" << std::endl;
};

//for Func是一个万能引用
// 1.对于左值，T会被推导为左值引用，参数的类型也会被推导值左值引用。
// 2.对于右值，T会被推导

//此函数只接收左值
template <typename T, typename = std::enable_if_t<std::is_reference_v<T>>>
void forFunc(T &&x)
{
    std::cout << "forFunc" << std::endl;
}

template <typename T, typename = std::enable_if_t<!std::is_reference_v<T>>>
void forFunc2(T &&x)
{
    std::cout << "forFunc2" << std::endl;
}

//  值传递,会衰退！
// 1. 和之前一样，如果expr的类型是一个引用，忽略这个引用部分
// 2. 如果忽略expr的引用性（reference-ness）之后，expr是一个const，那就再忽略const。如果它是volatile，也忽略volatile
// 3. 在模板类型推导时，数组名或者函数名实参会退化为指针，除非它们被用于初始化引用

template <typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept
{
    return N;
}

template <typename T>
void fun(T &p)
{
    //默认是移除cv
    static_assert(std::is_integral_v<T>, "test");
}

int main()
{
    int const x = 200;

    return 0;
}