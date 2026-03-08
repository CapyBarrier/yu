#ifndef YU_INCLUDE_YU_SELECT_DETAIL_CONCEPTS_ACTION_FOR_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_CONCEPTS_ACTION_FOR_HPP_

#include <concepts>

namespace yu::select::detail::concepts {

template <typename T, typename Subject>
concept action_for = std::invocable<T&&, Subject&&> || std::invocable<T&&>;

} // namespace yu::select::detail::concepts

#endif