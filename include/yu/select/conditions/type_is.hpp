#ifndef YU_SELECT_CONDITIONS_TYPE_IS_HPP_
#define YU_SELECT_CONDITIONS_TYPE_IS_HPP_

#include "detail/type_is_t.hpp"

namespace yu::select::conditions {

template <typename T>
inline constexpr detail::type_is_t<T> type_is;

} // namespace yu::select::conditions

#endif