#ifndef YU_TUPLES_INDEX_SEQUENCE_FOR_HPP_
#define YU_TUPLES_INDEX_SEQUENCE_FOR_HPP_

#include "size.hpp"
#include "tuple.hpp"
#include <utility>


namespace yu::tuples {

template <tuple T>
using index_sequence_for = std::make_index_sequence<size_v<T>>;

} // namespace yu::tuples

#endif