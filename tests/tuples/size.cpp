#include <yu/tuples/size.hpp>
#include <cassert>
#include <tuple>
#include <utility>
#include <array>
#include <string>
#include <vector>

int main() {
    // Basic size tests
    using arr_t = int[10];
    using tup_t = std::tuple<int, float, bool, short[10]>;
    using pair_t = std::pair<int, long>;

    static_assert(yu::tuples::size_v<arr_t> == 10);
    static_assert(yu::tuples::size_v<tup_t> == 4);
    static_assert(yu::tuples::size_v<pair_t> == 2);
    
    // Edge case: empty tuple
    static_assert(yu::tuples::size_v<std::tuple<>> == 0);
    
    // Edge case: single-element tuple
    static_assert(yu::tuples::size_v<std::tuple<int>> == 1);
    
    // Edge case: large tuple
    static_assert(yu::tuples::size_v<std::tuple<int, int, int, int, int, int, int, int, int, int>> == 10);
    
    // Edge case: std::array of various sizes
    static_assert(yu::tuples::size_v<std::array<int, 1>> == 1);
    static_assert(yu::tuples::size_v<std::array<int, 5>> == 5);
    static_assert(yu::tuples::size_v<std::array<double, 100>> == 100);
    
    // Edge case: arrays of various sizes
    static_assert(yu::tuples::size_v<int[1]> == 1);
    static_assert(yu::tuples::size_v<double[50]> == 50);
    static_assert(yu::tuples::size_v<char[256]> == 256);
    
    // Edge case: const-qualified types
    static_assert(yu::tuples::size_v<const std::tuple<int, double>> == 2);
    static_assert(yu::tuples::size_v<const int[10]> == 10);
    static_assert(yu::tuples::size_v<const std::array<int, 5>> == 5);
    
    // Edge case: volatile-qualified types
    static_assert(yu::tuples::size_v<volatile std::tuple<int, double>> == 2);
    
    // Edge case: const volatile-qualified types
    static_assert(yu::tuples::size_v<const volatile std::tuple<int, double>> == 2);
    
    // Edge case: reference-qualified types
    static_assert(yu::tuples::size_v<std::tuple<int, double>&> == 2);
    static_assert(yu::tuples::size_v<const std::tuple<int, double>&> == 2);
    static_assert(yu::tuples::size_v<std::tuple<int, double>&&> == 2);
    
    // Edge case: complex element types
    static_assert(yu::tuples::size_v<std::tuple<std::string, std::vector<int>, std::array<double, 5>>> == 3);

    return 0;
}