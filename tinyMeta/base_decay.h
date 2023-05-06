#ifndef __KANON_BASE_DECAY_H__
#define __KANON_BASE_DECAY_H__

#include <type_traits>
#include "base_array.h"

namespace kanon
{
template <typename T,
          bool IsArray = kanon::is_array<T>::value,
          bool IsFunction = std::is_function<T>::value>
struct decay_selector
{
};

} // namespace kanon

#endif