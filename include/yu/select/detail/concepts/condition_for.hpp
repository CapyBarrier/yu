#ifndef YU_INCLUDE_YU_SELECT_DETAIL_CONCEPTS_CONDITION_FOR_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_CONCEPTS_CONDITION_FOR_HPP_

#include <concepts>
#include <functional>

namespace yu::select::detail::concepts {

template <typename T, typename Subject>
concept condition_for = requires(T& x, Subject& subject) {
    { std::invoke(x, subject) } -> std::convertible_to<bool>;
};

} // namespace yu::select::detail::concepts

#endif