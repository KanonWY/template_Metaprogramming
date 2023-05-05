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

// Primary template
template <typename T1, typename T2>
struct equals : false_type
{
};

// Specialized template
template <typename T> // 提供模板参数
struct equals<T, T> : true_type
{
};

/**
 * @brief 移除const
 */

template <typename T>
struct remove_const : type_identity<T>
{
};

template <typename T>
struct remove_const<T const> : type_identity<T>
{
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

/**
 * @brief 移除volatile
 * @tparam T
 */

template <typename T>
struct remove_volatile : type_identity<T>
{
};

template <typename T>
struct remove_volatile<T volatile> : type_identity<T>
{
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

/**
 * @brief 移除CV
 */

template <typename T>
using remove_cv = remove_volatile<remove_const_t<T>>;

template <typename T>
using remove_cv_t = typename remove_volatile<remove_const_t<T>>::type;

/**
 * @brief 判断一个类型是否为空
 */

template <typename T>
struct is_void : equals<void, remove_cv_t<T>>
{
};

template <typename T1, typename T2>
inline constexpr bool equals_raw_v = equals<remove_cv_t<T1>, remove_cv_t<T2>>::value;

/**
 * @brief 是否为浮点类型
 */
template <typename T>
using is_floating_point = value_identity<bool,
                                         equals_raw_v<T, float> || equals_raw_v<T, double> || equals_raw_v<T, long double>>;

/**
 * @brief 检测一个类型是否在一个集合中
 */
template <typename T, typename... Us>
struct is_any_of;

template <typename T, typename... U1_to_Un>
struct is_any_of<T, T, U1_to_Un...> : true_type
{
};

template <typename T, typename U0, typename... U1_to_Un>
struct is_any_of<T, U0, U1_to_Un...> : is_any_of<T, U1_to_Un...>
{
};

template <typename T>
struct is_any_of<T> : false_type
{
};

} // namespace kanon

#endif