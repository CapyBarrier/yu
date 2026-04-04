#ifndef YU_TUPLES_TUPLE_HPP_
#define YU_TUPLES_TUPLE_HPP_

#include "known_tuple.hpp"
#include "tuple_structured.hpp"

namespace yu::tuples {

template <typename T>
concept tuple = known_tuple<T> || tuple_structured<T>;

} // namespace yu::tuples

#endif