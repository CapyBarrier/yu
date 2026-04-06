#ifndef YU_TUPLES_ELEMENT_TYPE_HPP_
#define YU_TUPLES_ELEMENT_TYPE_HPP_

#include "get.hpp"
#include <cstddef>
#include <utility>

namespace yu::tuples {

template <std::size_t Idx, typename T>
using element_t = decltype(yu::tuples::get<Idx>(std::declval<T>()));

} // namespace yu::tuples

#endif