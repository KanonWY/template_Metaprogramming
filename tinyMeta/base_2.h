#ifndef CP4_BASE_2_H
#define CP4_BASE_2_H

#include "base.h"

namespace kanon
{

/**
 * @brief 实现condition
 */

template <bool Predicate, typename T, typename>
struct _if : type_identity<T>
{
};

template <typename T, typename F>
struct _if<false, T, F>
    : type_identity<F>
{
};

template <bool Predicate, typename T, typename F>
using _if_t = typename _if<Predicate, T, F>::type;

/**
 * @brief  判断一组类型是否式true_type
 *          采用了递归的写法
 */

template <typename... T>
struct conjunction : true_type
{
};

template <typename First, typename... Others>
struct conjunction<First, Others...> : _if<First::value, conjunction<Others...>, false_type>::type
{
};

/**
 * @brief enable 实现
 */

template <bool P, typename T>
struct enable_if
{
};

template <typename T>
struct enable_if<true, T> : type_identity<T>
{
};

template <bool P, typename T>
using enable_if_t = typename enable_if<P, T>::type;

/**
 * @brief  and/or实现
 */

template <typename...>
struct Or
{
};

template <>
struct Or<> : public true_type
{
};

template <typename B1>
struct Or<B1> : public B1
{
};

template <typename _B1, typename _B2>
struct Or<_B1, _B2> : public _if<_B1::value, _B1, _B2>::type
{
};

/** @brief recurse imp
 */
template <typename _B1, typename _B2, typename _B3, typename... _Bn>
struct Or<_B1, _B2, _B3, _Bn...>
    : public _if<_B1::value, _B1, Or<_B2, _B3, _Bn...>>::type
{
};

template <typename...>
struct And
{
};

template <>
struct And<> : public true_type
{
};

template <typename B1>
struct And<B1> : B1
{
};

template <typename _B1, typename _B2>
struct And<_B1, _B2> : public _if<_B1::value, _B2, _B1>::type
{
};

template <typename _B1, typename _B2, typename _B3, typename... _Bn>
struct And<_B1, _B2, _B3, _Bn...>
    : public _if<_B1::value, And<_B2, _B3, _Bn...>, _B1>::type
{
};

} // namespace kanon

#endif //CP4_BASE_2_H
