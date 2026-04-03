#ifndef YU_TUPLES__DETAIL_BOUNDED_ARRAY_HPP_
#define YU_TUPLES__DETAIL_BOUNDED_ARRAY_HPP_

#include <type_traits>

namespace yu::tuples::_detail {

template <typename T>
concept bounded_array = std::is_bounded_array_v<std::remove_cvref_t<T>>;

} // namespace yu::tuples::_detail

#endif