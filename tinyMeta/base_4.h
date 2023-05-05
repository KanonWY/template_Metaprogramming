#ifndef __BASE_4_H__
#define __BASE_4_H__

#include <type_traits>

/**
 *   判断一个类中是否存在某一个int类型的成员变量
 *
 *
 *
 */

namespace kanon
{

/**
 * 判断T中是否有静态成员变量f
 */
template <typename T, typename V = int>
struct HasStaticMemberF : std::false_type
{
};

// 只有静态成员变量 f才是合法的
template <typename T>
struct HasStaticMemberF<T, decltype(T::f)> : std::true_type
{
};

template <typename T>
constexpr inline bool HasStaticMemberF_v = HasStaticMemberF<T>::value;

/**
 *    判断T中是否有成员变量f，可以是静态成员或者非静态成员
 */
template <typename T, typename V = int>
struct HasMemberF : std::false_type
{
};

/**
 *    由于非静态成员无法使用T::f直接获取，因此需要使用declval来获取一个纯类值
 */
template <typename T>
struct HasMemberF<T, decltype(std::declval<T>().f)> : std::true_type
{
};

template <typename T>
constexpr inline bool HasMemberF_v = HasMemberF<T>::value;

/**
 *   只想判断T中是否有非静态成员变量f,不想判断静态成员变量
 */
template <typename T, typename V = int T::*> // care 这里现在为指针类型
struct HasNoStaticMemberF : std::false_type
{
};

template <typename T>
struct HasNoStaticMemberF<T, decltype(&T::f)> : std::true_type
{
};

template <typename T>
constexpr inline bool HasNoStaticMemberF_v = HasNoStaticMemberF<T>::value;

/**
 *
 *    判断T中是否含有成员f,不管f式成员函数，成员变量，是静态还是非静态
 *
 */

struct X
{
};

template <typename T>
using ToX = X;

template <typename T, typename v = X>
struct HasMember : std::false_type
{
};

template <typename T>
struct HasMemberF<T, ToX<decltype(&T::f)>> : std::true_type
{
};

} // namespace kanon

#endif
