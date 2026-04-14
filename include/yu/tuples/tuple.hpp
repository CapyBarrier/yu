#ifndef YU_TUPLES_TUPLE_HPP_
#define YU_TUPLES_TUPLE_HPP_

#include "known_tuple.hpp"
#include "tuple_structured.hpp"
#include <type_traits>

namespace yu::tuples {

template <typename T>
concept tuple = known_tuple<std::remove_cvref_t<T>> || tuple_structured<T>;

} // namespace yu::tuples

#endif