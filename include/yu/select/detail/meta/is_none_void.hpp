#ifndef YU_SELECT_DETAIL_META_IS_NONE_VOID_HPP_
#define YU_SELECT_DETAIL_META_IS_NONE_VOID_HPP_

#include <tuple>
#include <type_traits>

namespace yu::select::detail::meta {

template <typename ResultTuple>
struct is_none_void;

template <typename... Results>
struct is_none_void<std::tuple<Results...>> :
    std::negation<std::disjunction<std::is_void<Results>...>> {};

template <typename ResultTuple>
inline constexpr bool is_none_void_v = is_none_void<ResultTuple>::value;

} // namespace yu::select::detail::meta

#endif