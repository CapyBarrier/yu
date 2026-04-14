#ifndef YU_TUPLES_APPLY_RESULT_HPP_
#define YU_TUPLES_APPLY_RESULT_HPP_

#include "_detail/application_trait_base.hpp"
#include "tuple.hpp"
#include <type_traits>

namespace yu::tuples {

template <typename F, typename T>
struct apply_result {};

template <typename F, typename T>
requires tuple<T>
struct apply_result<F, T> : _detail::application_trait_base<std::invoke_result, T, F> {};

template <typename F, typename T>
using apply_result_t = apply_result<F, T>::type;

} // namespace yu::tuples

#endif