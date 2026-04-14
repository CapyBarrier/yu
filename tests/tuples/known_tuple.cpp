#include <yu/tuples/known_tuple.hpp>
#include <tuple>
#include <array>
#include <utility>
#include <ranges>
#include <vector>
#include <map>
#include <string>

int main() {
    // Test known_tuple with built-in arrays
    static_assert(yu::tuples::known_tuple<int[5]>);
    static_assert(yu::tuples::known_tuple<double[3]>);
    static_assert(yu::tuples::known_tuple<char[10]>);
    
    // Test known_tuple with std::tuple
    static_assert(yu::tuples::known_tuple<std::tuple<int>>);
    static_assert(yu::tuples::known_tuple<std::tuple<int, double>>);
    static_assert(yu::tuples::known_tuple<std::tuple<int, double, char>>);
    static_assert(yu::tuples::known_tuple<std::tuple<>>);  // empty tuple
    
    // Test known_tuple with std::array
    static_assert(yu::tuples::known_tuple<std::array<int, 5>>);
    static_assert(yu::tuples::known_tuple<std::array<double, 3>>);
    static_assert(yu::tuples::known_tuple<std::array<char, 1>>);
    
    // Test known_tuple with std::pair
    static_assert(yu::tuples::known_tuple<std::pair<int, double>>);
    static_assert(yu::tuples::known_tuple<std::pair<int, int>>);
    static_assert(yu::tuples::known_tuple<std::pair<double, char>>);
    
    // Test known_tuple with std::ranges::subrange
    {
        std::vector<int> vec = {1, 2, 3};
        auto range = std::ranges::subrange(vec.begin(), vec.end());
        static_assert(yu::tuples::known_tuple<decltype(range)>);
        
        // Test with different subrange kinds
        static_assert(yu::tuples::known_tuple<std::ranges::subrange<std::vector<int>::iterator>>);
    }
    
    // Test known_tuple with various template configurations
    static_assert(yu::tuples::known_tuple<std::tuple<int, int, int, int, int>>);
    static_assert(yu::tuples::known_tuple<std::array<double, 100>>);
    static_assert(yu::tuples::known_tuple<float[2]>);
    
    // Negative tests: non-known types
    static_assert(!yu::tuples::known_tuple<int>);
    static_assert(!yu::tuples::known_tuple<double>);
    static_assert(!yu::tuples::known_tuple<char>);
    static_assert(!yu::tuples::known_tuple<std::vector<int>>);
    static_assert(!yu::tuples::known_tuple<std::string>);
    static_assert(!yu::tuples::known_tuple<std::map<int, int>>);
    
    // Negative tests: pointers
    static_assert(!yu::tuples::known_tuple<int*>);
    static_assert(!yu::tuples::known_tuple<double*>);
    
    // Negative tests: references
    static_assert(!yu::tuples::known_tuple<int&>);
    static_assert(!yu::tuples::known_tuple<double&>);
}
