#ifndef YU_TUPLES_SIZE_HPP_
#define YU_TUPLES_SIZE_HPP_

#include <cstddef>
#include <tuple>
#include <type_traits>

namespace yu::tuples {

namespace _detail {

template <typename T>
concept bounded_array = std::is_bounded_array_v<std::remove_cvref_t<T>>;

template <typename T>
concept tuple_sized = requires {
    typename std::tuple_size<std::remove_cvref_t<T>>;
    std::tuple_size<std::remove_cvref_t<T>>::value;
};

} // namespace _detail

template <typename T>
struct size {};

template <typename T>
requires _detail::bounded_array<T>
struct size<T> : std::extent<std::remove_cvref_t<T>> {};

template <typename T>
requires(!_detail::bounded_array<T>) && _detail::tuple_sized<T>
struct size<T> : std::tuple_size<std::remove_cvref_t<T>> {};

template <typename T>
inline constexpr std::size_t size_v = size<T>::value;

} // namespace yu::tuples

#endif