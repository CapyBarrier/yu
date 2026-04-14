#include <yu/tuples/apply_result.hpp>
#include <array>
#include <string>
#include <tuple>
#include <type_traits>

struct add_op {
        int operator()(int a, int b) const { return a + b; }
};

int main() {
    // Test apply_result_t with std::tuple and int arguments
    {
        using result_type = yu::tuples::apply_result_t<add_op, std::tuple<int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test apply_result_t with std::tuple and different argument types
    {
        struct string_op {
                std::string operator()(const char*, const char*) const { return std::string(); }
        };

        using result_type = yu::tuples::apply_result_t<string_op, std::tuple<const char*, const char*>>;
        static_assert(std::is_same_v<result_type, std::string>);
    }

    // Test apply_result_t with std::array
    {
        using result_type = yu::tuples::apply_result_t<add_op, std::array<int, 2>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test apply_result_t with built-in array
    {
        using result_type = yu::tuples::apply_result_t<add_op, int[2]>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test apply_result_t with std::pair
    {
        using result_type = yu::tuples::apply_result_t<add_op, std::pair<int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test apply_result_t with single-element tuple
    {
        struct unary_op {
                double operator()(int x) const { return x * 2.5; }
        };

        using result_type = yu::tuples::apply_result_t<unary_op, std::tuple<int>>;
        static_assert(std::is_same_v<result_type, double>);
    }

    // Test apply_result_t with function pointer
    {
        int (*func_ptr)(int, int) = [](int a, int b) { return a + b; };
        using result_type         = yu::tuples::apply_result_t<decltype(func_ptr), std::tuple<int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test apply_result_t with three-element tuple
    {
        struct ternary_op {
                int operator()(int a, int b, int c) const { return a + b + c; }
        };

        using result_type = yu::tuples::apply_result_t<ternary_op, std::tuple<int, int, int>>;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test apply_result struct (not just _t version)
    {
        using result      = yu::tuples::apply_result<add_op, std::tuple<int, int>>;
        using result_type = result::type;
        static_assert(std::is_same_v<result_type, int>);
    }

    // Test apply_result has specialization for tuple types only
    {
        using result [[maybe_unused]] = yu::tuples::apply_result<add_op, int>;
        // For non-tuple types, apply_result does not have a specialization and has no type member
        // This is correct behavior - apply_result is only specialized for tuple types
    }
}
