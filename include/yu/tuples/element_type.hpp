#ifndef YU_TUPLES_ELEMENT_TYPE_HPP_
#define YU_TUPLES_ELEMENT_TYPE_HPP_

#include "_detail/bounded_array.hpp"
#include "_detail/sized.hpp"
#include "yu/tuples/_detail/bounded_array.hpp"
#include <cstddef>
#include <type_traits>

namespace yu::tuples {

template <std::size_t Idx, typename T>
struct element_type {};

template <std::size_t Idx, typename T>
requires _detail::sized<T> && _detail::bounded_array<T>
struct element_type<Idx, T> : std::remove_extent<std::remove_cvref_t<T>> {};

template <std::size_t Idx, typename T>
requires _detail::sized<T> && (!_detail::bounded_array<T>)
struct element_type<Idx, T> : std::remove_extent<std::remove_cvref_t<T>> {};



std::template <std::size_t Idx, typename T>
using element_type_t = element_type<Idx, T>::type;

} // namespace yu::tuples

#endif