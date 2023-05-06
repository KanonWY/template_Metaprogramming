#ifndef __KANON_ARRAY_H__
#define __KANON_ARRAY_H__

#include <type_traits>
#include "base.h"

namespace kanon
{

/**
 *  is_array
*/

template <typename>
struct is_array : false_type
{
};

template <typename T, std::size_t size>
struct is_array<T[size]>
    : true_type
{
};

template <typename T>
struct is_array<T[]>
    : true_type
{
};

template <typename T>
struct remove_extent
{
    using type = T;
};

template <typename T, std::size_t SIZE>
struct remove_extent<T[SIZE]>
{
    using type = T;
};

template <typename T>
struct remove_extent<T[]>
{
    using type = T;
};

} // namespace kanon

#endif