#include "yu/tuples/get.hpp"
#include "yu/tuples/size.hpp"
#include <yu/tuples/index_sequence_for.hpp>
#include <cassert>
#include <string>
#include <tuple>
#include <utility>


template <typename T, std::size_t... Idx>
auto f(T&& tuple, std::index_sequence<Idx...>) {
    return std::make_tuple(yu::tuples::get<yu::tuples::size_v<T> - Idx - 1>(tuple)...);
}

template <typename T>
requires yu::tuples::tuple<T>
auto g(T&& tup) {
    return f(std::forward<T>(tup), yu::tuples::index_sequence_for<T>{});
}

int main() {
    assert(g(std::make_tuple(1, 'a', std::string{"Hello"})) == std::make_tuple(std::string{"Hello"}, 'a', 1));
    return 0;
}