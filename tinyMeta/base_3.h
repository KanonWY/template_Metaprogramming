#ifndef __BASE_3_H__
#define __BASE_3_H__

#include <type_traits>

// ques： 如何获取函数的返回值，和参数值

/**
 *      
 *        可调用对象：
 *        函数类型：R(Arg...)
 *        函数指针类型： 
 *        仿函数
 *        lambda类型
 *        函数对象类型
 *        成员函数类型
 * */

namespace kanon
{

template <typename T>
struct getRet
{
private:
    using DT = std::decay_t<T>;

public:
    // 如果内部有operator就获取它的类型
    using type = typename getRet<decltype(&DT::operator())>::type;
};

// 函数类型
template <typename R, typename... Args>
struct getRet<R(Args...)>
{
    using type = R;
};

// 函数指针类型
template <typename R, typename... Args>
struct getRet<R (*)(Args...)>
{
    using type = R;
};

// lambda类型
// 仿函数类型

//静态非成员函数类型
template <typename T, typename R, typename... Args>
struct getRet<R (T::*)(Args...)>
{
    using type = R;
};

template <typename T, typename R, typename... Args>
struct getRet<R (T::*)(Args...) const>
{
    using type = R;
};

template <typename T>
using getRet_t = typename getRet<T>::type;

// 使用declval 来避开构造检测而生成一个纯类型的对象，这样对象如果没有无参构造函数也可以避开这个构造检测

/**
 *  下面有一个XXX元函数，接收一个类型，然后使用decltype来获取某一个类型的method方法，
 *  但是由于由于TestC结构体没有无参构造函数，因此X{}构造失败
 *  有以下几个方法解决该问题：
 *  1、指定0参数
 *  2、指针转换，避开构造检测机制
 *  3、使用std::declval<T>()来构造, 此模板函数避开检测生成一个纯对象
 *
 */
struct TestC
{
    TestC(int);
    int method();
};

template <typename X>
struct XXX
{
    // using type = decltype(X{}.method());
    // 1.
    // using type = decltype(X{0}.method());
    // 2.
    // using type = decltype(static_cast<X *>(nullptr)->method());
    // 3.
    using type = decltype(std::declval<X>().method());
};
// XXX<TestC>::type a;

/**
 *  采用declval生成纯对象，然后使用decltype推导其返回类型即可。
 */
template <typename T>
struct GetRet
{
    using type = decltype(std::declval<std::decay<T>>()());
};

/*
 * @brief   如何获取函数的参数
 *          假设需要获取函数的第二个参数类型
 *
*/

template <typename T>
struct Get2ndArg
{
private:
    using DT = std::decay_t<T>;

public:
    using type = typename Get2ndArg<decltype(&DT::operator())>::type;
};

template <typename R, typename Arg1, typename Arg2, typename... Args>
struct Get2ndArg<R(Arg1, Arg2, Args...)>
{
    using type = Arg2;
};

template <typename R, typename Arg1, typename Arg2, typename... Args>
struct Get2ndArg<R (*)(Arg1, Arg2, Args...)>
{
    using type = Arg2;
};

template <typename T, typename R, typename Arg1, typename Arg2, typename... Args>
struct Get2ndArg<R (T::*)(Arg1, Arg2, Args...)>
{
    using type = Arg2;
};

template <typename T, typename R, typename Arg1, typename Arg2, typename... Args>
struct Get2ndArg<R (T::*)(Arg1, Arg2, Args...) const>
{
    using type = Arg2;
};

template <typename T>
using Get2ndArg_t = typename Get2ndArg<T>::type;

}; // namespace kanon

#endif
