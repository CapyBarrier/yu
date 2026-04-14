#include <yu/tuples/apply.hpp>
#include <yu/tuples/apply_result.hpp>
#include <yu/tuples/is_applicable.hpp>
#include <cassert>
#include <tuple>
#include <array>
#include <utility>
#include <type_traits>
#include <string>
#include <functional>

// Test function objects and free functions for apply tests
struct plus_op {
    int operator()(int a, int b) const { return a + b; }
};

struct multiplier {
    int operator()(int a, int b, int c) const { return a * b * c; }
};

struct string_concat {
    std::string operator()(const std::string& a, const std::string& b) const { 
        return a + b; 
    }
};

struct doubler {
    int operator()(int x) const { return x * 2; }
};

// Free function for apply tests
int free_add(int a, int b) {
    return a + b;
}

double free_divide(double a, double b) {
    return a / b;
}

int main() {
    // Test 1: apply with std::tuple and binary function
    {
        std::tuple<int, int> tup(3, 4);
        int result = yu::tuples::apply(plus_op{}, tup);
        assert(result == 7);
    }

    // Test 2: apply with std::tuple and ternary function
    {
        std::tuple<int, int, int> tup(2, 3, 4);
        int result = yu::tuples::apply(multiplier{}, tup);
        assert(result == 24);
    }

    // Test 3: apply with std::array
    {
        std::array<int, 2> arr{5, 6};
        int result = yu::tuples::apply(plus_op{}, arr);
        assert(result == 11);
    }

    // Test 4: apply with built-in array
    {
        int arr[2] = {7, 8};
        int result = yu::tuples::apply(plus_op{}, arr);
        assert(result == 15);
    }

    // Test 5: apply with std::pair
    {
        std::pair<int, int> p(10, 20);
        int result = yu::tuples::apply(plus_op{}, p);
        assert(result == 30);
    }

    // Test 6: apply with single-element tuple
    {
        std::tuple<int> tup(42);
        int result = yu::tuples::apply(doubler{}, tup);
        assert(result == 84);
    }

    // Test 7: apply with empty tuple and nullary function
    {
        struct nullary_op {
            int operator()() const { return 100; }
        };
        std::tuple<> empty_tup;
        int result = yu::tuples::apply(nullary_op{}, empty_tup);
        assert(result == 100);
    }

    // Test 8: apply with const tuple
    {
        const std::tuple<int, int> ctup(11, 22);
        int result = yu::tuples::apply(plus_op{}, ctup);
        assert(result == 33);
    }

    // Test 9: apply with string types
    {
        std::tuple<std::string, std::string> str_tup("Hello, ", "World!");
        std::string result = yu::tuples::apply(string_concat{}, str_tup);
        assert(result == "Hello, World!");
    }

    // Test 10: apply with free function pointer
    {
        std::tuple<int, int> tup(15, 25);
        int result = yu::tuples::apply(free_add, tup);
        assert(result == 40);
    }

    // Test 11: apply with std::function
    {
        std::function<int(int, int)> f = plus_op{};
        std::tuple<int, int> tup(100, 200);
        int result = yu::tuples::apply(f, tup);
        assert(result == 300);
    }

    // Test 12: apply with floating point types and free function
    {
        std::tuple<double, double> tup(10.0, 2.0);
        double result = yu::tuples::apply(free_divide, tup);
        assert(result == 5.0);
    }

    // Test 13: apply with lvalue reference tuple
    {
        std::tuple<int, int> tup(3, 7);
        std::tuple<int, int>& ref = tup;
        int result = yu::tuples::apply(plus_op{}, ref);
        assert(result == 10);
    }

    // Test 14: apply with rvalue tuple
    {
        int result = yu::tuples::apply(plus_op{}, std::tuple<int, int>(50, 50));
        assert(result == 100);
    }

    // Test 15: apply with lambda
    {
        auto lambda = [](int a, int b) { return a - b; };
        std::tuple<int, int> tup(100, 30);
        int result = yu::tuples::apply(lambda, tup);
        assert(result == 70);
    }

    // Static assertion tests
    // Test 16: apply_result_t with std::tuple
    {
        using result_type = yu::tuples::apply_result_t<plus_op, std::tuple<int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test 17: apply_result_t with std::array
    {
        using result_type = yu::tuples::apply_result_t<plus_op, std::array<int, 2>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test 18: apply_result_t with built-in array
    {
        using result_type = yu::tuples::apply_result_t<plus_op, int[2]>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test 19: apply_result_t with std::pair
    {
        using result_type = yu::tuples::apply_result_t<plus_op, std::pair<int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test 20: is_applicable_v checks
    static_assert(yu::tuples::is_applicable_v<plus_op, std::tuple<int, int>>);
    static_assert(yu::tuples::is_applicable_v<plus_op, std::array<int, 2>>);
    static_assert(yu::tuples::is_applicable_v<plus_op, int[2]>);
    static_assert(yu::tuples::is_applicable_v<plus_op, std::pair<int, int>>);
    static_assert(yu::tuples::is_applicable_v<multiplier, std::tuple<int, int, int>>);
    static_assert(yu::tuples::is_applicable_v<doubler, std::tuple<int>>);

    // Test 21: apply_result_t with ternary function
    {
        using result_type = yu::tuples::apply_result_t<multiplier, std::tuple<int, int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test 22: apply_result_t with unary function
    {
        using result_type = yu::tuples::apply_result_t<doubler, std::tuple<int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test 23: apply_result_t with free function
    {
        using result_type = yu::tuples::apply_result_t<decltype(free_add), std::tuple<int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test 24: is_applicable with free function
    static_assert(yu::tuples::is_applicable_v<decltype(free_add), std::tuple<int, int>>);
    static_assert(yu::tuples::is_applicable_v<decltype(free_divide), std::tuple<double, double>>);

    // Test 25: Negative cases - is_applicable_v should be false for wrong signatures
    static_assert(!yu::tuples::is_applicable_v<plus_op, std::tuple<int>>);  // not enough args
    static_assert(!yu::tuples::is_applicable_v<plus_op, std::tuple<int, int, int>>);  // too many args
    static_assert(!yu::tuples::is_applicable_v<doubler, std::tuple<int, int>>);  // too many args

    // Test 26: apply with mutable reference semantics
    {
        struct increment_op {
            void operator()(int& x) const { x++; }
        };
        std::tuple<int> tup(5);
        yu::tuples::apply(increment_op{}, tup);
        assert(std::get<0>(tup) == 6);
    }

    // Test 27: apply with complex types in tuple
    {
        struct concat_strings {
            std::string operator()(const std::string& a, const std::string& b, const std::string& c) const {
                return a + b + c;
            }
        };
        std::tuple<std::string, std::string, std::string> tup("a", "b", "c");
        std::string result = yu::tuples::apply(concat_strings{}, tup);
        assert(result == "abc");
    }

    // Test 28: apply with const reference in function
    {
        struct sum_refs {
            int operator()(const int& a, const int& b) const { return a + b; }
        };
        std::tuple<int, int> tup(123, 456);
        int result = yu::tuples::apply(sum_refs{}, tup);
        assert(result == 579);
    }

    // Test 29: apply returning void
    {
        struct void_op {
            void operator()(int, int) const {}
        };
        std::tuple<int, int> tup(1, 2);
        yu::tuples::apply(void_op{}, tup);  // Should not crash
    }

    // Test 30: apply with heterogeneous tuple types
    {
        struct mixed_op {
            std::string operator()(int a, double b, char c) const {
                return std::to_string(a) + std::to_string(b) + std::string(1, c);
            }
        };
        std::tuple<int, double, char> tup(42, 3.14, 'X');
        std::string result = yu::tuples::apply(mixed_op{}, tup);
        // Just verify it compiles and runs
        assert(!result.empty());
    }

    return 0;
}
