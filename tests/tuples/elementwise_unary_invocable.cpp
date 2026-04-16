#include <yu/tuples/elementwise_unary_invocable.hpp>
#include <tuple>
#include <string>
#include <type_traits>

struct printer {
    void operator()(int) const {}
    void operator()(double) const {}
    void operator()(const std::string&) const {}
};

struct int_only {
    void operator()(int) const {}
};

int main() {
    using T = std::tuple<int, double, std::string>;

    static_assert(yu::tuples::elementwise_unary_invocable<printer, T>);
    static_assert(!yu::tuples::elementwise_unary_invocable<int_only, T>);

    using U = std::tuple<int, int, int>;
    static_assert(yu::tuples::elementwise_unary_invocable<int_only, U>);

    return 0;
}
