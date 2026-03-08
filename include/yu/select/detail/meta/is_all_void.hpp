#ifndef YU_INCLUDE_YU_SELECT_DETAIL_META_IS_ALL_VOID_HPP_
#define YU_INCLUDE_YU_SELECT_DETAIL_META_IS_ALL_VOID_HPP_

#include <tuple>
#include <type_traits>

namespace yu::select::detail::meta {

template <typename ResultTuple>
struct is_all_void;

template <typename... Results>
struct is_all_void<std::tuple<Results...>> : std::conjunction<std::is_void<Results>...> {};

template <typename ResultTuple>
inline constexpr bool is_all_void_v = is_all_void<ResultTuple>::value;

} // namespace yu::select::detail::meta

#endif