#include <iostream>

// template<typename T>
// void f(ParamType param);
// f(expr);                        //从expr中推导T和ParamType

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 1. ParamType is a reference or pointer!

// 匹配规则：
// 1. expr的reference-ness将会被忽略
// 2. 然后expr的类型与ParamType进行模式匹配来决定T的类型
template <typename T>
void foo(T &a)
{
}

// expr的reference-ness在类型推导中会被忽略。

void test1()
{
    int x = 29;
    const int y = 20;
    const int &z = 30;
    foo(x); //T  -> int,       paramType ->  int&
    foo(y); //T  -> const int, paramType ->  const int&
    foo(z); //T  -> const int, paramType ->  const int&, z的reference-ness被忽略
}

template <typename T>
void foo2(T const &a)
{
}

void test2()
{
    int x = 29;
    const int y = 20;
    const int &z = 30;
    foo2(x); // T -> int, paramType -> const int&
    foo2(y); // T -> int, paramType -> const int&
    foo2(z); // T -> int, paramType -> const int&
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2. paramType is universal reference

// template <typename T>
// void f(T &&arg);
// f(expr)

// 匹配规则
// 1. 如果expr是左值，T 和 paramType会被推导为左值引用。这是T唯一会被推导为reference的情况。虽然paramType看起来是右值引用的
//    样子，最终还是被推导为左值引用。
// 2. 如果expr是右值，就使用正常的推导规则.

template <typename T>
void koo(T &&a)
{
}

void test3()
{
    int x = 10;
    const int y = 20;
    const int &z = 30;
    koo(x);  // T -> int& ,      paramType -> int&
    koo(y);  // T -> const int&, paramType -> const int&
    koo(z);  // T -> const int&, paramType -> const int&
    koo(39); // T -> int,        paramType -> int &&
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 3. paramType is value

// template<typename T>
// void f(T arg)
// f(expr)

//匹配规则
// 1. 依旧忽略expr的reference-ness
// 2. 如果expr有const性质，它也将被忽略
// 3. 如果expr有volatile性质，它也将被忽略

template <typename T>
void moo(T arg)
{
}

struct Base
{
};

void test4()
{
    int a = 200;
    const int b = 300;
    const int &c = 400;
    volatile int d = 500;
    moo(a); // T -> int, paramType -> int
    moo(b); // T -> int, paramType -> int
    moo(c); // T -> int, paramType -> int
    moo(d); // T -> int, paramType -> int
}

//注意传指针值的时候，是可以传递const的
void test5()
{
    const char *const str = "kodkoakdo";
    moo(str);
    const Base *ptr = new Base;
    moo(ptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 4. 特殊退化机制

// 规则： 数组与函数在模板传参和模板传引用的时候会有不同的表现，在传值的时候会退化为指针

void someFunc(int, double);
template <typename T>
void f1(T a);

template <typename T>
void f2(T &a);

// 数组实参退化
void test6()
{
    const char name[] = "kanon";
    // 传递引用，不会退化，会被推导为真正的值
    f2(name); // T -> const char[5], paramType -> const char(&)[5];
    // 传递值， 会退化为指针
    f1(name); // T -> const char*, paramType -> const char*;
}

// 函数实参退化

void test7()
{
    f1(someFunc); // T -> void(*)(int, double), paramType -> void(*)(int, double)
    f2(someFunc); // T -> void(&)(int, double), paramType -> void(&)(int, double)
}

//TODO: 指向函数的指针和函数的引用有什么区别？

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////// 其他类型的推导

void test8()
{
    auto lam_func = [](int a) -> void {};
    f1(lam_func);
    f2(lam_func);
}

int main()
{
    return 0;
}