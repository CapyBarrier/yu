#ifndef YU_TUPLES__DETAIL_SIZED_HPP_
#define YU_TUPLES__DETAIL_SIZED_HPP_

#include <yu/tuples/size.hpp>
#include <type_traits>

namespace yu::tuples::_detail {

template <typename T>
concept sized = requires {
    typename yu::tuples::size<std::remove_cvref_t<T>>;
    yu::tuples::size<std::remove_cvref_t<T>>::value;
};

} // namespace yu::tuples::_detail

#endif