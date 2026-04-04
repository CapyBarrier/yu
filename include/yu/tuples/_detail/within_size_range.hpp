#ifndef YU_TUPLES__DETAIL_WITHIN_SIZE_RANGE_HPP_
#define YU_TUPLES__DETAIL_WITHIN_SIZE_RANGE_HPP_

#include "sized.hpp"
#include <yu/tuples/size.hpp>
#include <cstddef>

namespace yu::tuples::_detail {

template <std::size_t Idx, typename T>
concept within_size_range = sized<T> && (Idx < size_v<T>);

} // namespace yu::tuples::_detail

#endif