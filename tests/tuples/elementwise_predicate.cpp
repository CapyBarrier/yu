#include <yu/tuples/elementwise_predicate.hpp>
#include <tuple>
#include <string>

struct predicate {
    bool operator()(int) const { return true; }
    bool operator()(double) const { return false; }
    bool operator()(const std::string&) const { return true; }
};

struct incomplete_predicate {
    bool operator()(int) const { return true; }
    bool operator()(double) const { return false; }
};

struct non_predicate {
    void operator()(auto) const {}
};

int main() {
    using T = std::tuple<int, double, std::string>;

    static_assert(yu::tuples::elementwise_predicate<predicate, T>);
    static_assert(!yu::tuples::elementwise_predicate<incomplete_predicate, T>);

    using U = std::tuple<int, int, int>;
    static_assert(!yu::tuples::elementwise_predicate<non_predicate, U>);

    return 0;
}
