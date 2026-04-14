#ifndef YU_TUPLES_IS_APPLICABLE_R_HPP_
#define YU_TUPLES_IS_APPLICABLE_R_HPP_

#include "_detail/application_trait_base.hpp"
#include "tuple.hpp"
#include <type_traits>

namespace yu::tuples {

template <typename R, typename F, typename T>
struct is_applicable_r : std::false_type {};

template <typename R, typename F, typename T>
requires tuple<T>
struct is_applicable_r<R, F, T> : _detail::application_trait_base<std::is_invocable, T, R, F> {};

template <typename R, typename F, typename T>
inline constexpr bool is_applicable_r_v = is_applicable_r<R, F, T>::value;

} // namespace yu::tuples

#endif