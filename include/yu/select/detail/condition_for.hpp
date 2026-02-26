#ifndef YU_SELECT_DETAIL_CONDITION_HPP_
#define YU_SELECT_DETAIL_CONDITION_HPP_

#include <concepts>

namespace yu::select::detail {

template <typename T, typename Subject>
concept condition_for = std::predicate<T&, Subject&> || std::equality_comparable_with<T&, Subject&>;

} // namespace yu::select::detail

#endif