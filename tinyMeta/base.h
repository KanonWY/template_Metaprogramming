#ifndef __KANON_BASE_H__
#define __KANON_BASE_H__

#include <type_traits>

namespace kanon
{

/**
 *   基础
*/
template <typename T, T v>
struct interger_const
{
    static constexpr T value = v;
    using value_type = T;
    using type = interger_const<T, v>;
};

using true_type = interger_const<bool, true>;
using false_type = interger_const<bool, false>;

template <bool B>
using bool_constant = interger_const<bool, B>;

/**l
 * 
 *     conditional 实现
 * 
*/

template <bool B, typename T, typename F>
struct Conditional
{
    using type = T;
};

template <typename T, typename F>
struct Conditional<false, T, F>
{
    using type = F;
};

template <bool B, typename T, typename F>
using Conditional_t = typename Conditional<B, T, F>::type;

/**
 *     enable_if
*/
template <bool cond, typename T = void>
struct enable_if
{
};

template <typename T>
struct enable_if<true, T>
{
    using type = T;
};

template <bool cond, typename T = void>
using enable_if_t = typename enable_if<cond, T>::type;
/**
 *      
 * 
 *   and 
 * 
 *   or 
 * 
 *   not
*/
template <typename T>
struct NOT : bool_constant<!bool(T::value)>
{
};

template <typename...>
struct AND
{
};

template <>
struct AND<> : true_type
{
};

template <typename _B1>
struct AND<_B1> : _B1
{
};

template <typename _B1, typename _B2>
struct AND<_B1, _B2> : Conditional<_B1::value, _B2, _B1>::type
{
};

template <typename _B1, typename _B2, typename _B3, typename... _Bn>
struct AND<_B1, _B2, _B3, _Bn...>
    : Conditional<_B1::value,
                  AND<_B2, _B3, _Bn...>, _B1>::type
{
};

template <typename...>
struct OR
{
};

template <>
struct OR<> : false_type
{
};

template <typename _B1>
struct OR<_B1> : _B1
{
};

template <typename _B1, typename _B2>
struct OR<_B1, _B2>
    : Conditional<_B1::value, _B1, _B2>::type
{
};

template <typename _B1, typename _B2, typename _B3, typename... _Bn>
struct OR<_B1, _B2, _B3, _Bn...>
    : Conditional<_B1::value,
                  _B1, OR<_B2, _B3, _Bn...>>::type
{
};

template <typename... Args>
using conjunction = AND<Args...>;

template <typename... Args>
using disjunction = OR<Args...>;

/**
 *      对cv的操作
*/

template <typename T>
struct remove_const
{
    using type = T;
};

//偏特化为const
template <typename T>
struct remove_const<T const>
{
    using type = T;
};

template <typename T>
struct remove_volatile
{
    using type = T;
};

template <typename T>
struct remove_volatile<T volatile>
{
    using type = T;
};

template <typename T>
using remove_cv = remove_volatile<remove_const<T>>;

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

template <typename T>
struct add_const
{
    using type = T const;
};

template <typename T>
struct add_volatile
{
    using type = volatile T;
};

template <typename T>
struct add_cv
{
    using type = typename add_volatile<add_const<T>>::type;
};

/**
 *  引用操作
 *  删除引用
 *  添加引用
*/

template <typename T>
struct remove_reference
{
    using type = T;
};

// 特化左值引用
template <typename T>
struct remove_const<T &>
{
    using type = T;
};

// 特化右值引用
template <typename T>
struct remove_reference<T &&>
{
    using type = T;
};

// 是否左值引用
template <typename>
struct is_lvalue_reference : false_type
{
};

template <typename T>
struct is_lvalue_reference<T &>
    : true_type
{
};

// 是否右值引用
template <typename>
struct is_rvalue_reference : false_type
{
};

template <typename T>
struct is_rvalue_reference<T &&> : true_type
{
};

// 判断一个类型是否是引用类型
template <typename T>
struct is_reference : OR<is_lvalue_reference<T>, is_rvalue_reference<T>>::type
{
};

/**
 *  添加左值引用
*/
// __is_referenceable使用了std中的实现： 是否是对象OR是否是左右值引用
template <typename T, bool = std::__is_referenceable<T>::value>
struct add_lvalue_reference_helper
{
    using type = T;
};

template <typename T>
struct add_lvalue_reference_helper<T, true>
{
    using type = T &;
};

template <typename T>
struct add_lvalue_reference : add_lvalue_reference_helper<T>
{
};

/**
 *  添加右值引用
*/

template <typename T, bool = std::__is_referenceable<T>::value>
struct add_rvalue_reference_helper
{
    using type = T;
};

template <typename T>
struct add_rvalue_reference_helper<T, true>
{
    using type = T &&;
};

template <typename T>
struct add_rvalue_reference : add_rvalue_reference_helper<T>
{
};

/**
 *  is_same
*/

template <typename T1, typename T2>
struct is_same : false_type
{
};

template <typename T>
struct is_same<T, T> : true_type
{
};

template <typename T1, typename T2>
using is_same_v = typename is_same<T1, T2>::value;

} // namespace kanon

#endif