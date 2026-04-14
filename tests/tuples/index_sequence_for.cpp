#include "yu/tuples/get.hpp"
#include "yu/tuples/size.hpp"
#include <yu/tuples/index_sequence_for.hpp>
#include <cassert>
#include <string>
#include <tuple>
#include <utility>
#include <array>


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
    // Basic test with 3-element tuple
    assert(g(std::make_tuple(1, 'a', std::string{"Hello"})) == std::make_tuple(std::string{"Hello"}, 'a', 1));
    
    // Edge case: single-element tuple
    {
        auto result = g(std::make_tuple(42));
        assert(result == std::make_tuple(42));
    }
    
    // Edge case: two-element tuple
    {
        auto result = g(std::make_tuple(1, 2));
        assert(result == std::make_tuple(2, 1));
    }
    
    // Edge case: larger tuple (5 elements)
    {
        auto result = g(std::make_tuple(1, 2, 3, 4, 5));
        assert(result == std::make_tuple(5, 4, 3, 2, 1));
    }
    
    // Test index_sequence_for with std::array
    {
        std::array<int, 3> arr{10, 20, 30};
        auto seq = yu::tuples::index_sequence_for<decltype(arr)>{};
        static_assert(std::is_same_v<decltype(seq), std::index_sequence<0, 1, 2>>);
    }
    
    // Test index_sequence_for with built-in array
    {
        int arr[5] = {1, 2, 3, 4, 5};
        auto seq = yu::tuples::index_sequence_for<decltype(arr)>{};
        static_assert(std::is_same_v<decltype(seq), std::index_sequence<0, 1, 2, 3, 4>>);
    }
    
    // Test index_sequence_for with std::pair
    {
        std::pair<int, double> p(1, 2.5);
        auto seq = yu::tuples::index_sequence_for<decltype(p)>{};
        static_assert(std::is_same_v<decltype(seq), std::index_sequence<0, 1>>);
    }
    
    // Static checks: verify the generated sequences are correct
    // Note: std::index_sequence is not a tuple, so we test it via type equality instead
    static_assert(std::is_same_v<
        yu::tuples::index_sequence_for<std::tuple<int, int, int>>,
        std::index_sequence<0, 1, 2>
    >);
    
    static_assert(std::is_same_v<
        yu::tuples::index_sequence_for<std::tuple<int>>,
        std::index_sequence<0>
    >);
    
    static_assert(std::is_same_v<
        yu::tuples::index_sequence_for<std::tuple<>>,
        std::index_sequence<>
    >);
    
    static_assert(std::is_same_v<
        yu::tuples::index_sequence_for<std::array<int, 10>>,
        std::index_sequence<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>
    >);
    
    return 0;
}
