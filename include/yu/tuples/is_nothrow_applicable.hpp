#ifndef YU_TUPLES_IS_NOTHROW_APPLICABLE_HPP_
#define YU_TUPLES_IS_NOTHROW_APPLICABLE_HPP_

#include "_detail/application_trait_base.hpp"
#include "tuple.hpp"
#include <type_traits>

namespace yu::tuples {

template <typename F, typename T>
struct is_nothrow_applicable : std::false_type {};

template <typename F, typename T>
requires tuple<T>
struct is_nothrow_applicable<F, T> : _detail::application_trait_base<std::is_nothrow_invocable, T, F> {};

template <typename F, typename T>
inline constexpr bool is_nothrow_applicable_v = is_nothrow_applicable<F, T>::value;

} // namespace yu::tuples

#endif