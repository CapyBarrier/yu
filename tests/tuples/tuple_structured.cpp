#include <yu/tuples/tuple_structured.hpp>
#include <tuple>
#include <array>
#include <utility>
#include <string>
#include <vector>

int main() {
    // Test tuple_structured with std::tuple
    static_assert(yu::tuples::tuple_structured<std::tuple<int, double>>);
    static_assert(yu::tuples::tuple_structured<std::tuple<int>>);
    static_assert(yu::tuples::tuple_structured<std::tuple<>>);  // empty tuple
    
    // Test tuple_structured with std::array
    static_assert(yu::tuples::tuple_structured<std::array<int, 5>>);
    static_assert(yu::tuples::tuple_structured<std::array<double, 3>>);
    static_assert(yu::tuples::tuple_structured<std::array<int, 1>>);
    
    // Test tuple_structured with built-in arrays
    static_assert(yu::tuples::tuple_structured<int[5]>);
    static_assert(yu::tuples::tuple_structured<double[3]>);
    static_assert(yu::tuples::tuple_structured<char[10]>);
    
    // Test tuple_structured with std::pair
    static_assert(yu::tuples::tuple_structured<std::pair<int, double>>);
    static_assert(yu::tuples::tuple_structured<std::pair<int, int>>);
    
    // Test tuple_structured with more complex element types
    static_assert(yu::tuples::tuple_structured<std::tuple<std::string, int, double>>);
    static_assert(yu::tuples::tuple_structured<std::array<std::string, 2>>);
    
    // Test tuple_structured with const references
    static_assert(yu::tuples::tuple_structured<std::tuple<int, double> const &>);
    static_assert(yu::tuples::tuple_structured<std::array<int, 5> const &>);
    
    // Test tuple_structured with lvalue references
    static_assert(yu::tuples::tuple_structured<std::tuple<int, double> &>);
    static_assert(yu::tuples::tuple_structured<std::array<int, 5> &>);
    
    // Test tuple_structured with rvalue references
    static_assert(yu::tuples::tuple_structured<std::tuple<int, double> &&>);
    static_assert(yu::tuples::tuple_structured<std::array<int, 5> &&>);
    
    // Negative tests: non-tuple types
    static_assert(!yu::tuples::tuple_structured<int>);
    static_assert(!yu::tuples::tuple_structured<double>);
    static_assert(!yu::tuples::tuple_structured<std::string>);
    static_assert(!yu::tuples::tuple_structured<std::vector<int>>);
}
