#ifndef YU_TUPLES_ELEMENTWISE_REGULAR_INVOCABLE_HPP_
#define YU_TUPLES_ELEMENTWISE_REGULAR_INVOCABLE_HPP_

#include "element_t.hpp"
#include "index_sequence_for.hpp"
#include "tuple.hpp"
#include <concepts>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _detail {

template <typename F, typename T, std::size_t... Idx>
consteval bool elementwise_regular_invocable_impl(std::index_sequence<Idx...>) {
    return (std::regular_invocable<F, element_t<Idx, T>> && ...);
}

} // namespace _detail

template <typename F, typename T>
concept elementwise_regular_invocable
    = tuple<T> && _detail::elementwise_regular_invocable_impl<F, T>(index_sequence_for<T>{});

} // namespace yu::tuples

#endif