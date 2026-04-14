#include <yu/tuples/get.hpp>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <array>
#include <utility>
#include <string>


struct foo {
        template <std::size_t>
        int get() {
            return 42;
        }
};

namespace std {

template <>
struct tuple_size<foo> : std::integral_constant<std::size_t, 3> {};

} // namespace std

int main() {
    {
        // Test get with built-in arrays
        int arr[3] = {1, 2, 3};
        assert(yu::tuples::get<0>(arr) == arr[0]);
        assert(yu::tuples::get<1>(arr) == arr[1]);
        assert(yu::tuples::get<2>(arr) == arr[2]);

        yu::tuples::get<2>(arr) = 4;
        assert(arr[2] == 4);
    }
    {
        // Test get with custom type having member get()
        foo x{};
        assert(yu::tuples::get<0>(x) == x.template get<0>());
        assert(yu::tuples::get<0>(x) == 42);
    }
    {
        // Test get with std::tuple
        std::tuple<int, char, double> tup(1, 'a', 3.14);

        assert(yu::tuples::get<0>(tup) == std::get<0>(tup));
        assert(yu::tuples::get<1>(tup) == std::get<1>(tup));

        yu::tuples::get<2>(tup) = 2.78;
        assert(std::get<2>(tup) == 2.78);
    }
    
    {
        // Test get with std::array
        std::array<int, 3> arr{10, 20, 30};
        assert(yu::tuples::get<0>(arr) == 10);
        assert(yu::tuples::get<1>(arr) == 20);
        assert(yu::tuples::get<2>(arr) == 30);
        
        yu::tuples::get<1>(arr) = 25;
        assert(arr[1] == 25);
    }
    
    {
        // Test get with std::pair
        std::pair<int, double> p(42, 3.14);
        assert(yu::tuples::get<0>(p) == 42);
        assert(yu::tuples::get<1>(p) == 3.14);
        
        yu::tuples::get<0>(p) = 99;
        assert(p.first == 99);
    }
    
    {
        // Test get with const tuple
        const std::tuple<int, char, double> ctup(1, 'a', 3.14);
        assert(yu::tuples::get<0>(ctup) == 1);
        assert(yu::tuples::get<1>(ctup) == 'a');
        assert(yu::tuples::get<2>(ctup) == 3.14);
    }
    
    {
        // Test get with const array
        const int carr[3] = {100, 200, 300};
        assert(yu::tuples::get<0>(carr) == 100);
        assert(yu::tuples::get<1>(carr) == 200);
        assert(yu::tuples::get<2>(carr) == 300);
    }
    
    {
        // Test get with single-element tuple
        std::tuple<int> single(42);
        assert(yu::tuples::get<0>(single) == 42);
        yu::tuples::get<0>(single) = 99;
        assert(std::get<0>(single) == 99);
    }
    
    {
        // Test get with lvalue reference semantics
        std::tuple<int, int, int> t(1, 2, 3);
        int& ref0 = yu::tuples::get<0>(t);
        int& ref1 = yu::tuples::get<1>(t);
        int& ref2 = yu::tuples::get<2>(t);
        
        ref0 = 10;
        ref1 = 20;
        ref2 = 30;
        
        assert(std::get<0>(t) == 10);
        assert(std::get<1>(t) == 20);
        assert(std::get<2>(t) == 30);
    }
    
    {
        // Test get with various element types
        std::tuple<std::string, int, double, char> complex_tup("hello", 42, 3.14, 'x');
        static_assert(std::is_same_v<decltype(yu::tuples::get<0>(complex_tup)), std::string&>);
        static_assert(std::is_same_v<decltype(yu::tuples::get<1>(complex_tup)), int&>);
        assert(yu::tuples::get<0>(complex_tup) == "hello");
        assert(yu::tuples::get<1>(complex_tup) == 42);
    }

    return 0;
}