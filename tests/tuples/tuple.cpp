#include <yu/tuples/tuple.hpp>
#include <array>
#include <tuple>
#include <utility>
#include <vector>
#include <string>

int main() {
    // Basic tuple checks
    static_assert(yu::tuples::tuple<std::tuple<int, double, char>>);
    static_assert(yu::tuples::tuple<std::array<double, 3>>);
    // 要素数の判明している組み込み配列型もtupleのモデルである
    static_assert(yu::tuples::tuple<char[2]>);
    
    // Edge case: empty tuple
    static_assert(yu::tuples::tuple<std::tuple<>>);
    
    // Edge case: single-element tuple
    static_assert(yu::tuples::tuple<std::tuple<int>>);
    
    // Edge case: std::pair
    static_assert(yu::tuples::tuple<std::pair<int, double>>);
    
    // Edge case: const-qualified tuple
    static_assert(yu::tuples::tuple<const std::tuple<int, double>>);
    static_assert(yu::tuples::tuple<const std::array<int, 3>>);
    static_assert(yu::tuples::tuple<const int[5]>);
    
    // Edge case: volatile-qualified tuple (rarely used) - may not satisfy tuple concept
    // static_assert(yu::tuples::tuple<volatile std::tuple<int, double>>);
    
    // Edge case: const volatile-qualified tuple - may not satisfy tuple concept
    // static_assert(yu::tuples::tuple<const volatile std::tuple<int, double>>);
    
    // Edge case: reference types (references to tuples)
    static_assert(yu::tuples::tuple<std::tuple<int, double>&>);
    static_assert(yu::tuples::tuple<const std::tuple<int, double>&>);
    static_assert(yu::tuples::tuple<std::tuple<int, double>&&>);
    
    // Edge case: large arrays
    static_assert(yu::tuples::tuple<int[100]>);
    
    // Edge case: array of arrays (should still be tuple)
    static_assert(yu::tuples::tuple<int[3][4]>);
    
    // Negative test: non-tuple types should fail
    static_assert(!yu::tuples::tuple<int>);
    static_assert(!yu::tuples::tuple<double>);
    static_assert(!yu::tuples::tuple<std::string>);
    static_assert(!yu::tuples::tuple<std::vector<int>>);
}