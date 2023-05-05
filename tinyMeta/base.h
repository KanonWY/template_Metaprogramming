#ifndef __KANON_BASE_H__
#define __KANON_BASE_H__

namespace kanon
{

/**
 *  基本
*/
template <typename T>
struct type_identity
{
    using type = T;
};

template <typename T, T v>
struct value_identity : type_identity<T>
{
    static constexpr T value = v;
};

using true_type = value_identity<bool, true>;
using false_type = value_identity<bool, false>;

/**
 *  比较两个类型是否相等
*/

template <typename T1, typename T2>
struct is_same : false_type
{
};

template <typename T>
struct is_same<T, T> : true_type
{
};

} // namespace kanon

#endif