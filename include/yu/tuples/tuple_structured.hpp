#ifndef YU_TUPLES_TUPLE_STRUCTURED_HPP_
#define YU_TUPLES_TUPLE_STRUCTURED_HPP_

#include "get.hpp"
#include "size.hpp"
#include <concepts>
#include <cstddef>
#include <utility>

namespace yu::tuples {

namespace _exposition {

template <typename T>
concept sized = requires {
    typename tuples::size<std::remove_cvref_t<T>>;
    tuples::size<std::remove_cvref_t<T>>::value;
};

template <typename T, std::size_t Idx>
concept gettable = std::regular_invocable<decltype(tuples::get<Idx>), T&&>;

template <typename T, std::size_t... Idx>
consteval bool all_gettable(std::index_sequence<Idx...>) {
    return (... && gettable<T, Idx>);
}

template <typename T>
concept tuple_structured_impl = sized<T> && all_gettable<T>(std::make_index_sequence<size_v<T>>{});

} // namespace _exposition

template <typename T>
concept tuple_structured = _exposition::tuple_structured_impl<T>;

} // namespace yu::tuples

#endif