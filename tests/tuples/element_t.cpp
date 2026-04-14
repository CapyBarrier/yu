#include <yu/tuples/element_t.hpp>
#include <array>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>


int main() {
    // std::tuple - basic test
    {
        using T = std::tuple<int, char, double>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, char&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<2, T>, double&&>);
    }

    // 組み込み配列
    {
        using T = double[1];

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, double&&>);
    }

    // Edge case: std::array
    {
        using T = std::array<int, 5>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<4, T>, int&&>);
    }

    // Edge case: std::pair
    {
        using T = std::pair<int, double>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, double&&>);
    }

    // Edge case: built-in arrays with different types
    {
        using T = int[10];
        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<5, T>, int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<9, T>, int&&>);
    }

    // Edge case: const-qualified tuple
    {
        using T = const std::tuple<int, char, double>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, const int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, const char&&>);
    }

    // Edge case: lvalue reference
    {
        using T = std::tuple<int, char, double>&;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, char&>);
    }

    // Edge case: const lvalue reference
    {
        using T = const std::tuple<int, char, double>&;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, const int&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, const char&>);
    }

    // Edge case: rvalue reference
    {
        using T = std::tuple<int, char, double>&&;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, char&&>);
    }

    // Edge case: single-element tuple
    {
        using T = std::tuple<int>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, int&&>);
    }

    // Edge case: complex element types
    {
        using T = std::tuple<std::string, std::vector<int>, std::array<double, 5>>;

        static_assert(std::is_same_v<yu::tuples::element_t<0, T>, std::string&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<1, T>, std::vector<int>&&>);
        static_assert(std::is_same_v<yu::tuples::element_t<2, T>, std::array<double, 5>&&>);
    }
}