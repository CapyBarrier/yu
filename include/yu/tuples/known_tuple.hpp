#ifndef YU_TUPLES_KNOWN_TUPLE_HPP_
#define YU_TUPLES_KNOWN_TUPLE_HPP_

#include <array>
#include <cstddef>
#include <ranges>
#include <tuple>

namespace yu::tuples {

template <typename T>
inline constexpr bool known_tuple = false;

template <typename T, std::size_t N>
inline constexpr bool known_tuple<T[N]> = true;

template <typename... Ts>
inline constexpr bool known_tuple<std::tuple<Ts...>> = true;

template <typename T, std::size_t N>
inline constexpr bool known_tuple<std::array<T, N>> = true;

template <typename T1, typename T2>
inline constexpr bool known_tuple<std::pair<T1, T2>> = true;

template <typename I, typename S, std::ranges::subrange_kind K>
inline constexpr bool known_tuple<std::ranges::subrange<I, S, K>> = true;

} // namespace yu::tuples

#endif