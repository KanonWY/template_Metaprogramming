#include <iostream>

// 1. 函数模板没有偏特化
// 2. 函数模板之间也可以重载

/**
 *    函数模板之间也可以重载
*/
template <typename T>
void foo(T)
{
    std::cout << "foo(T)" << std::endl;
}

template <typename T>
void foo(T *)
{
    std::cout << "foo(T*)" << std::endl;
}

/**
 *  函数模板支持仅支持全特化，不支持偏特化。
*/
template <typename T, typename S>
void func(T t, S s)
{
    std::cout << "template function" << std::endl;
}

/**
 *  特化的函数模板不参与重载？
*/
// a.
template <>
void func(int t, int s)
{
    std::cout << "template function full special version" << std::endl;
}

// b.
void func(int a, int b)
{
    std::cout << "normal function" << std::endl;
}

// func(1, 2);   调用哪个？ b！

//匹配规则： （特化版本的函数为什么不参与重载）
// 在函数模板，函数模板全特化，普通函数都存在的情况下：
// 1. 首先查找普通函数中是否有匹配的。如果有就匹配成功。如果没有就进入2。
// 2. 查找模板中有没有匹配的，并且选取最匹配的版本。可以继续分为下面两步。

// （1）在全特化版本中查找是否有匹配的，如果没有进入（2）
//  (2) 尝试生成一个实例，如果成功则通过，如果失败则报错。

// 特化版本的函数为什么不参与重载？
//http://www.gotw.ca/publications/mill17.htm#:~:text=For%20one%20thing%2C%20you%20can%27t%20partially%20specialize%20them

// 全特化版本的函数和普通函数有什么区别？
// 编译后的符号还是不同的！
// gcc -c xxx.cc
// readelf -s xxx.o
//     可以发现全特化版本的模板函数比普通函数多了一个字符修饰！
//     9: 0000000000000000    63 FUNC    GLOBAL DEFAULT    2 _Z4funcIiiEvT_T0_
//     10: 0000000000000040    63 FUNC    GLOBAL DEFAULT    2 _Z4funcii

// 全特化函数的注意事项：
// 通过全特化得到的函数和常规函数都是类似的。比如，在一个程序中，只能有一份非inline的函数模板的全特化函数存在。

/**
 *   函数模板如何实现偏特化的效果？
 *   1、借助类模板偏特化实现： Functor实现，即重载operator实现。
 *   2、使用标签分发
 *   3、concept
*/

// Functor实现
template <typename A, typename B>
class F
{
public:
    F(A a, B b)
        : a_(a), b_(b)
    {
    }

    void operator()()
    {
        std::cout << "normal function" << std::endl;
    }

private:
    A a_;
    B b_;
};

template <typename A>
class F<A, int>
{
public:
    F(A a, int b)
        : a_(a), b_(b)
    {
    }

    void operator()()
    {
        std::cout << "partical function" << std::endl;
    }

private:
    A a_;
    int b_;
};

// 使用标签分发
struct NormalVersionTag
{
};
struct IntPartialVersionTag
{
};

template <class T>
struct TagDispatchTrait
{
    using Tag = NormalVersionTag;
};

template <>
struct TagDispatchTrait<int>
{
    using Tag = IntPartialVersionTag;
};

template <typename A, typename B>
inline void internal_f(A a, B b, NormalVersionTag)
{
    std::cout << "Normal version." << std::endl;
}

template <typename A, typename B>
inline void internal_f(A a, B b, IntPartialVersionTag)
{
    std::cout << "Partial version." << std::endl;
}

// 根据B的类型，生成不同的标签，然后使用函数重载实现。
template <typename A, typename B>
void Moo(A a, B b)
{
    return internal_f(a, b, typename TagDispatchTrait<B>::Tag{});
}

// TODO: concept

int main()
{

    return 0;
}