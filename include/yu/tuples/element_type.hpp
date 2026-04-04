#ifndef YU_TUPLES_ELEMENT_TYPE_HPP_
#define YU_TUPLES_ELEMENT_TYPE_HPP_

#include "_detail/bounded_array.hpp"
#include "_detail/within_size_range.hpp"
#include <cstddef>
#include <type_traits>

namespace yu::tuples {

namespace _detail {

template <std::size_t Idx, typename T>
concept tuple_element_accesible = requires { typename std::tuple_element<Idx, std::remove_cvref_t<T>>::type; };

} // namespace _detail

template <std::size_t Idx, typename T>
struct element_type {};

template <std::size_t Idx, typename T>
requires _detail::within_size_range<Idx, T> && _detail::bounded_array<T>
struct element_type<Idx, T> : std::remove_extent<std::remove_cvref_t<T>> {};

template <std::size_t Idx, typename T>
requires _detail::within_size_range<Idx, T> && (!_detail::bounded_array<T>) && _detail::tuple_element_accesible<Idx, T>
struct element_type<Idx, T> : std::tuple_element<Idx, std::remove_cvref_t<T>> {};

template <std::size_t Idx, typename T>
using element_type_t = element_type<Idx, T>::type;

} // namespace yu::tuples

#endif