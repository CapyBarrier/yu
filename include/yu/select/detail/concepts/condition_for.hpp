#ifndef YU_INCLUDE_YU_SELECT_DETAIL_CONCEPTS_CONDITION_FOR_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_CONCEPTS_CONDITION_FOR_HPP_

#include <concepts>

namespace yu::select::detail::concepts {

template <typename T, typename Subject>
concept condition_for = std::predicate<T&, Subject&> || std::equality_comparable_with<T&, Subject&>;

} // namespace yu::select::detail::concepts

#endif